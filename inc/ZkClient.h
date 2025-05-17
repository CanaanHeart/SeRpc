#ifndef _ZKCLIENT_H_
#define _ZKCLIENT_H_

#include "SeRpcApplication.h"

#include <semaphore.h>
#include <zookeeper/zookeeper.h>

#include <string>
#include <functional>
#include <vector>
#include <tuple>
#include <future>

class ZkClient;

// 全局观察器，zk服务端给客户端的通知
void GlobalWathcer(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx);

struct ExistCallBackArgs
{
    ZkClient* client_;
    std::string path_;
    std::string data_;
    int state_;

    ExistCallBackArgs(ZkClient* client, std::string path, std::string data, int state):client_(client), path_(path), data_(data), state_(state){}
};


class ZkClient
{
private:
    // zk客户端句柄
    zhandle_t *zh_;
public:
    ZkClient();
    ~ZkClient();

    // zk客户端启动连接zk服务器
    void Start();

    // 在zk服务器上根据指定的path创建znode，state = 0，永久性节点；
    void Create(std::string &path, std::string &data, int state = 0);

    // 根据指定的节点路径获取节点的值
    std::string GetData(const std::string &path);

    static void ExistCallBack(int rc, const struct Stat* stat, const void* data);
    static void CreateCallBack(int rc, const char* name, const void* data);
};

#endif // _ZKCLIENT_H_