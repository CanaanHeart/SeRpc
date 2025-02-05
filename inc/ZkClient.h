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

// 全局观察器，zk服务端给客户端的通知
void global_wathcer(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx);

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
};

#endif // _ZKCLIENT_H_