#include "../user.pb.h"
#include "SeRpcApplication.h"
#include "SeRpcChannel.h"
#include "SeRpcController.h"

#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    SeRpcApplication::Init(argc, argv);

    // 通过stub调用远程服务发布的rpc方法
    fixbug::UserServiceRpc_Stub stub(new SeRpcChannel());

    // fixbug::LoginRequest request;
    // request.set_name("sai er");
    // request.set_pwd("123456");

    // fixbug::LoginResponse response;

    // 发起rpc调用
    // stub.Login(nullptr, &request, &response, nullptr);

    // // 调用完成，读取响应
    // if(response.error_msg().errcode() == 0){
    //     bool login_success = response.success();
    //     INFO("login success: ", login_success);
    // }
    // else{
    //     INFO(response.error_msg().errmsg());
    // }

    fixbug::SumRequest request;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8};
    for(const auto &val: nums){
        request.add_nums(val);
    }

    fixbug::SumResponse response;

    SeRpcController controller;

    stub.Sum(&controller, &request, &response, nullptr);

    if(controller.Failed()){
        WARN(controller.ErrorText());
    }
    else{
        if(response.error_msg().errcode() == 0){
            int res = response.res();
            INFO("res: ", res);
        }
        else{
            INFO(response.error_msg().errmsg());
        }
    }

    return 0;
}