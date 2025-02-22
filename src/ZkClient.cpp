#include "ZkClient.h"

using namespace std;

void global_wathcer(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx)
{
    if(type == ZOO_SESSION_EVENT){  // 回调的消息类型，和会话相关
        if(state == ZOO_CONNECTED_STATE){   // zk客户端和服务端连接成功
            sem_t *sem = (sem_t*)zoo_get_context(zh);
            sem_post(sem);
        }
    }
}

ZkClient::ZkClient():zh_(nullptr)
{

}

ZkClient::~ZkClient()
{
    if(zh_ != nullptr){
        // 关闭句柄，释放资源
        zookeeper_close(zh_);
    }
}

void ZkClient::Start()
{
    string ip = SeRpcApplication::GetInstance().GetValue("zookeeper_ip");
    string port = SeRpcApplication::GetInstance().GetValue("zookeeper_port");

    string conn_str = ip + ":" + port;

    /*
    zookeeper_mt: 多线程版本
    zookeeper的API客户端提供了3个线程，API调用线程，网络I/O线程，watcher回调线程
    */
    zh_ = zookeeper_init(conn_str.c_str(), global_wathcer, 30000, nullptr, nullptr, 0);
    if(zh_ == nullptr){
        ERROR("zookeeper init error!");
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(zh_, &sem);

    sem_wait(&sem);

    INFO("zookeeper init success!");
}

void ZkClient::Create(string &path, string &data, int state)
{
    char path_buf[128];
    int buf_len = sizeof(path_buf);
    int flag;
    tuple<ZkClient*, string, string, int> args;
    args = make_tuple(this, path, data, state);
    flag = zoo_exists(zh_, path.c_str(), 0, nullptr);
    if(flag == ZNONODE){
        flag = zoo_create(zh_, path.c_str(), data.c_str(), data.size(),
                            &ZOO_OPEN_ACL_UNSAFE, state, path_buf, buf_len);
        if(flag == ZOK){
            INFO("znode create success! path:", path);
        }
        else{
            ERROR("znode create error! path:", path);
        }
    }
    else{
        INFO("znode has existed: ", path);
    }
}

string ZkClient::GetData(const string &path)
{
    char buf[128];
    int buf_len = sizeof(buf);

    int flag = zoo_get(zh_, path.c_str(), 0, buf, &buf_len, nullptr);
    if(flag != ZOK){
        WARN("get data error! path:", path);
        return "";
    }
    else{
        return string(buf);
    }
}
