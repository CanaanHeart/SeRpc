#include "SeRpcLoadConfig.h"

using namespace std;

void SeRpcLoadConfig::LoadConfigFile(const string &file)
{
    lc_.LoadConfigFile(file);
}

string SeRpcLoadConfig::GetValue(const string &key)
{
    return lc_.GetValue(key);
}