#include "SeRpcProvider.h"

using namespace std;

SeRpcProvider::SeRpcProvider()
{
    string ip = SeRpcApplication::GetInstance().GetValue("rpc_server_ip");
    uint16_t port = static_cast<uint16_t>(stoi(SeRpcApplication::GetInstance().GetValue("rpc_server_port")));

    string file_io = "../conf/threadpool_io.conf";
    string file_work = "../conf/threadpool_work.conf";

    server_ = make_unique<TcpServer>(port, ip, file_io);
    work_tp_ = make_unique<ThreadPool>(file_work);

    server_->SetNewConnetionCB(std::bind(&SeRpcProvider::NewConnection, this, std::placeholders::_1));
    server_->SetDeleteConnectionCB(std::bind(&SeRpcProvider::DeleteConnection, this, std::placeholders::_1));
    server_->SetErrorConnectionCB(std::bind(&SeRpcProvider::ErrorConnection, this, std::placeholders::_1));
    server_->SetOnMessageCB(std::bind(&SeRpcProvider::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
    server_->SetSendCompleteCB(std::bind(&SeRpcProvider::SendComplete, this, std::placeholders::_1));
}

void SeRpcProvider::NotifyService(google::protobuf::Service *service)
{
    ServiceInfo service_info;
    // 获取服务对象的描述信息
    const google::protobuf::ServiceDescriptor *service_desc = service->GetDescriptor();
    // 获取服务名字
    string service_name = service_desc->name();
    // 获取服务对象的方法数量
    int method_count = service_desc->method_count();

    for(int i = 0; i < method_count; ++i){
        // 获取服务对象中的指定方法的描述
        const google::protobuf::MethodDescriptor *method_desc = service_desc->method(i);
        string method_name = method_desc->name();
        service_info.method_map_.insert({method_name, method_desc});
    }

    service_info.service_ = service;
    service_map_.insert({service_name, service_info});
}

void SeRpcProvider::Run()
{
    // 将当前rpc节点上要发布的服务注册到zk上，让rpc client可以从zk上发现将服务
    ZkClient zkc;
    zkc.Start();
    // service_name为永久性节点，method_name为临时性节点
    for(auto &sv: service_map_){
        string service_path = "/" + sv.first;
        string data = "";
        zkc.Create(service_path, data);
        for(auto &me: sv.second.method_map_){
            string method_path = service_path + "/" + me.first;
            string ip = SeRpcApplication::GetInstance().GetValue("rpc_server_ip");
            string port = SeRpcApplication::GetInstance().GetValue("rpc_server_port");
            string conn_str = ip + ":" + port;
            zkc.Create(method_path, conn_str, ZOO_EPHEMERAL);
        }
    }

    server_->Start();
}

void SeRpcProvider::NewConnection(SP_Connection conn)
{
    INFO(conn->GetFd(), " ", conn->GetIp(), " ", conn->GetPort());
}

void SeRpcProvider::DeleteConnection(SP_Connection conn)
{
    INFO(conn->GetFd(), " disconnected!");
}

void SeRpcProvider::ErrorConnection(SP_Connection conn)
{
    INFO(conn->GetFd(), " error!");
}

void SeRpcProvider::OnMessage(SP_Connection conn, Buffer &buf)
{
    if(work_tp_->GetThreadNums() == 0){
        // 没有工作线程
        Task(conn, buf);
    }
    else{   
        work_tp_->AddTask(std::bind(&SeRpcProvider::Task, this, conn, buf));
    }
}

void SeRpcProvider::SendComplete(SP_Connection conn)
{

}

/*
网络传输的数据格式:
total_size(4字节) + header_size(4字节) + header_str + args_str
经过网络框架的拆包后得到header_size(4字节) + header_str + args_str

header_str:
    service_name + method_name + args_size
*/
void SeRpcProvider::Task(SP_Connection conn, Buffer buf)
{
    std::string recv_msg = buf.Str();

    // 获取数据头长度
    uint32_t header_size = 0;
    recv_msg.copy(reinterpret_cast<char*>(&header_size), INT_BYTES, 0);

    // 反序列化
    string head_str = recv_msg.substr(INT_BYTES, header_size);
    se_rpc::RpcHeader rpc_header;
    string service_name, method_name;
    uint32_t args_size;
    if(rpc_header.ParseFromString(head_str)){
        // 成功反序列化数据头
        service_name = rpc_header.service_name();
        method_name = rpc_header.method_name();
        args_size =  rpc_header.agrs_size();

    }
    else{
        WARN(head_str, " 反序列化失败!");
        return;
    }

    string args_str = recv_msg.substr(INT_BYTES + header_size, args_size);

    // 获取service和method对象
    auto service_it = service_map_.find(service_name);
    if(service_it == service_map_.end()){
        WARN("service is not exist!");
        return;
    }
    google::protobuf::Service *service = service_it->second.service_;

    auto method_it = service_it->second.method_map_.find(method_name);
    if(method_it == service_it->second.method_map_.end()){
        WARN("method is not exist!");
        return;
    }
    const google::protobuf::MethodDescriptor *method = method_it->second;

    // cout << "===============================================" << endl;
    // cout << "header size: " << header_size << endl;
    // cout << "service name: " << service_name << endl;
    // cout << "method name: " << method_name << endl;
    // cout << "args str: " << args_str << endl;
    // cout << "===============================================" << endl;

    // 生成rpc方法的请求和响应参数
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str)){
        WARN("args parse error!");
        return;
    }
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 给method方法调用绑定一个Closure回调函数
    google::protobuf::Closure *done = google::protobuf::NewCallback(this, &SeRpcProvider::SendRpcResponse, conn, response);

    service->CallMethod(method, nullptr, request, response, done);
}

void SeRpcProvider::SendRpcResponse(SP_Connection conn, google::protobuf::Message *msg)
{
    string response_str;
    if(!msg->SerializeToString(&response_str)){
        ERROR("serialize response str error!");
    }
    Buffer send_buf;
    send_buf.Append(response_str.c_str(), response_str.size());
    conn->SetSendBuffer(send_buf);
}