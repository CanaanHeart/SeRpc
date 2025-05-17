#include "SeRpcChannel.h"

using namespace std;

void SeRpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method,
                    google::protobuf::RpcController *controller,
                    const google::protobuf::Message *request,
                    google::protobuf::Message *response,
                    google::protobuf::Closure *done)
{
    const google::protobuf::ServiceDescriptor *service_disc = method->service();
    string service_name = service_disc->name();
    string method_name = method->name();
    
    // 获取参数长度
    int args_size = 0;
    string args_str;
    if(request->SerializeToString(&args_str)){
        args_size = args_str.size();
    }
    else{
        string err_msg = "serialize request error!";
        controller->SetFailed(err_msg);
        return;
        // WARN(err_msg);
    }

    se_rpc::RpcHeader request_header;
    request_header.set_service_name(service_name);
    request_header.set_method_name(method_name);
    request_header.set_agrs_size(args_size);

    string header_str;
    uint32_t header_size;
    if(request_header.SerializeToString(&header_str)){
        header_size = header_str.size();
    }
    else{
        string err_msg = "serialize request error!";
        controller->SetFailed(err_msg);
        return;
        // WARN(err_msg);
    }

    int request_size = INT_BYTES + static_cast<int>(header_size) + args_size;
    // 组织待发送的rpc请求的字符串
    string request_str;
    request_str.insert(0, string(reinterpret_cast<char*>(&request_size), INT_BYTES));
    request_str.insert(INT_BYTES, string(reinterpret_cast<char*>(&header_size), INT_BYTES));
    request_str += header_str;
    request_str += args_str;

    // 通过网络完成rpc方法的远程调用
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1){
        close(cfd);
        string err_msg = "create socket error!";
        controller->SetFailed(err_msg);
        return;
        // ERROR("create socket error: ", errno);
    }
    // 在zookeeper中读取数据
    ZkClient zkc;
    zkc.Start();
    string method_path = "/" + service_name + "/" + method_name;
    string host = zkc.GetData(method_path);
    if(host == ""){
        controller->SetFailed(method_path + " is not exist!");
        return;
    }

    size_t pos = host.find(':');
    if(pos == string::npos){
        controller->SetFailed(method_path + " is invalid!");
        return;
    }
    string server_ip = host.substr(0, pos);
    uint16_t port = static_cast<uint16_t>(stoi(host.substr(pos + 1)));

    if(!DnsResolver::IsValidIpv4(server_ip)){
        vector<string> ip_list;
        string err_msg;
        if(DnsResolver::Resolve(server_ip, ip_list, err_msg)){
            server_ip = *ip_list.begin();
        }
        else{
            WARN(err_msg);
        }
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if(connect(cfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1){
        close(cfd);
        string err_msg = "connect error!";
        controller->SetFailed(err_msg);
        return;
        // ERROR("connect error: ", errno);
    }

    // 发送rpc请求
    if(send(cfd, request_str.c_str(), request_str.size(), 0) == -1){
        // WARN("send error: ", errno);
        close(cfd);
        string err_msg = "send error!";
        controller->SetFailed(err_msg);
        return;
    }

    // 接收rpc请求
    char recv_buf[1024] = {0};
    int recv_size;
    if((recv_size = recv(cfd, recv_buf, 1024, 0)) == -1){
        // WARN("recv error: ", errno);
        close(cfd);
        string err_msg = "recv error!";
        controller->SetFailed(err_msg);
        return;
    }
    
    // 反序列化rpc调用的响应数据
    if(!response->ParseFromArray(&recv_buf[INT_BYTES], recv_size - INT_BYTES)){
        close(cfd);
        // WARN("parse error! response str: ", recv_buf);
        string err_msg = "parse error!";
        controller->SetFailed(err_msg);
        return;
    }

    close(cfd);
}