#ifndef _RPC_APPLICATION_H_
#define _RPC_APPLICATION_H_

#include "../logger/Logger.h"
#include "SeRpcLoadConfig.h"

// 框架基础类，负责框架的初始化操作
class SeRpcApplication
{
private:
    static SeRpcLoadConfig rlc_;
private:
    SeRpcApplication(){};
    SeRpcApplication(const SeRpcApplication&) = delete;
    SeRpcApplication(SeRpcApplication &&) = delete;
public:
    static void Init(int argc, char **argv);
    static SeRpcApplication& GetInstance();
    static std::string GetValue(const std::string &key);
};

#endif // _RPC_APPLICATION_H_