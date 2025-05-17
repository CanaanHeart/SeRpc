#include "SeRpcApplication.h"

#include <unistd.h>

#include <iostream>

using namespace std;

SeRpcLoadConfig SeRpcApplication::rlc_;

void SeRpcApplication::Init(int argc, char **argv)
{
    string conf_path;
    if(argc < 2){
        conf_path = "../conf/rpc.conf";
    }
    else{
        int c = 0;
        opterr = 0;
        while((c = getopt(argc, argv, "i:")) != -1){
            switch(c){
            case 'i':
                conf_path = optarg;
                break;
            case '?':
                FATAL("invalid args!");
            case ':':
                FATAL("no agrs!");
            }
        }
    }
    rlc_.LoadConfigFile(conf_path);
}

SeRpcApplication& SeRpcApplication::GetInstance()
{
    static SeRpcApplication rpc_app;
    return rpc_app;
}

string SeRpcApplication::GetValue(const string &key)
{
    return rlc_.GetValue(key);
}