#ifndef _SERPCCHANNEL_H_
#define _SERPCCHANNEL_H_

#include "../logger/Logger.h"
#include "../dns_resolver/DnsResolver.h"
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "rpcheader.pb.h"
#include "SeRpcApplication.h"
#include "SeRpcController.h"
#include "ZkClient.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include <iostream>
#include <string>

#define INT_BYTES 4

class SeRpcChannel: public google::protobuf::RpcChannel
{
private:

public:
    // 通过此函数，统一做rpc方法调用的数据序列化和网络发送
    void CallMethod(const google::protobuf::MethodDescriptor *method,
                    google::protobuf::RpcController *controller,
                    const google::protobuf::Message *request,
                    google::protobuf::Message *response,
                    google::protobuf::Closure *done);
};

#endif // _SERPCCHANNEL_H_