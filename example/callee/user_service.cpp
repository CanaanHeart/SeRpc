#include <iostream>
#include <string>

#include "../user.pb.h"
#include "SeRpcApplication.h"
#include "SeRpcProvider.h"

using namespace std;

class UserService: public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd)
    {
        cout << "doing local service: Login" << std::endl;
        cout << "name: " << name << endl;
        cout << "pwd: " << pwd << endl;
        return true;
    }

    int Sum(const std::vector<int> &nums)
    {
        int res = 0;
        for(const auto &val: nums)
            res += val;
        return res;
    }

    /*
    重写基类的虚函数
    1. caller --> Login(LoginRequest) --> 网络库 --> callee
    2. callee --> Login(LoginResponse) --> 交到下面的重写方法
    */
    void Login(google::protobuf::RpcController* controller,
                const fixbug::LoginRequest* request,
                fixbug::LoginResponse* response,
                google::protobuf::Closure* done)
    {
        // 从框架中获取调用的参数
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 执行业务
        bool ret = Login(name, pwd);

        // 组织响应数据
        response->mutable_error_msg()->set_errcode(0);
        response->mutable_error_msg()->set_errmsg("调用成功!");
        response->set_success(ret);
        
        // 执行回调，执行响应对象数据的序列化和网络发送
        done->Run();
    }

    void Sum(google::protobuf::RpcController *controller,
                const fixbug::SumRequest* request,
                fixbug::SumResponse* response,
                google::protobuf::Closure* done)
    {
        const google::protobuf::RepeatedField< ::google::protobuf::int32 > req_nums = request->nums();
        const vector<int> nums(req_nums.begin(), req_nums.end());
        int res = Sum(nums);
        response->mutable_error_msg()->set_errcode(0);
        response->mutable_error_msg()->set_errmsg("调用成功!");
        response->set_res(res);

        done->Run();
    }

};

int main(int argc, char **argv)
{
    // us.Login("saier", "123456");

    SeRpcApplication::Init(argc, argv);

    SeRpcProvider provider;

    provider.NotifyService(new UserService());

    provider.Run();

    return 0;
}