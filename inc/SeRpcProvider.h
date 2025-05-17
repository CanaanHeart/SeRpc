#ifndef _RPC_PROVIDER_H_
#define _RPC_PROVIDER_H_

#include "../logger/Logger.h"
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "SeRpcApplication.h"
#include "../serv/TcpServer.h"
#include "../serv/Connection.h"
#include "../threadpool/ThreadPool.h"
#include "rpcheader.pb.h"
#include "ZkClient.h"

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#define INT_BYTES 4

// 框架提供的专门服务发布rpc服务的网络对象类
class SeRpcProvider
{
private:
    // 服务类型信息
    class ServiceInfo
    {
    public:
        // 服务
        google::protobuf::Service *service_;
        // 方法描述, 
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> method_map_;
    };

    std::unique_ptr<TcpServer> server_;
    std::unique_ptr<ThreadPool> work_tp_;
    std::unordered_map<std::string, ServiceInfo> service_map_;
    
public:
    SeRpcProvider();
    // 框架提供给外部使用，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);
    // 启动rpc服务节点
    void Run();
    // 设置服务器回调函数
    void NewConnection(SP_Connection conn);
    void DeleteConnection(SP_Connection conn);
    void ErrorConnection(SP_Connection conn);
    void OnMessage(SP_Connection conn, Buffer &buf); // 将业务添加到工作线程池
    void SendComplete(SP_Connection conn);

    void Task(SP_Connection conn, Buffer buf);

    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(SP_Connection conn, google::protobuf::Message *msg);
};

#endif // _RPC_PROVIDER_H_