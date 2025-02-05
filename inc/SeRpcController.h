#ifndef _SERPCCONTROLLER_H_
#define _SERPCCONTROLLER_H_

#include <google/protobuf/service.h>

#include <iostream>
#include <string>

class SeRpcController: public google::protobuf::RpcController
{
private:
    bool failed_;               // rpc方法执行过程中的状态
    std::string err_text_;      // rpc方法执行过程中的错误信息
public:
    SeRpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);
};

#endif // _SERPCCONTROLLER_H_