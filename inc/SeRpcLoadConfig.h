#ifndef _RPC_LOAD_CONFIG_H_
#define _RPC_LOAD_CONFIG_H_

#include "../logger/Logger.h"
#include "../load_config/LoadConfig.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

// 读取配置模块
class SeRpcLoadConfig
{
private:
    LoadConfig lc_;
    std::string file_;
public:
    SeRpcLoadConfig(){}
    void LoadConfigFile(const std::string &file);
    std::string GetValue(const std::string &key);
};

#endif // _RPC_LOAD_CONFIG_H_