#include "ZkClient.h"

using namespace std;

void GlobalWathcer(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx)
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
    zh_ = zookeeper_init(conn_str.c_str(), GlobalWathcer, 30000, nullptr, nullptr, 0);
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
    ExistCallBackArgs *args = new ExistCallBackArgs(this, path, data, state);
    int flag = zoo_aexists(zh_, path.c_str(), 0, ExistCallBack, args);
    if(flag != ZOK){
        ERROR("zoo aexists failed");
    }
}

string ZkClient::GetData(const string &path)
{
    promise<string> prom;
    future<string> fut = prom.get_future();

    struct GetDataCallBackArgs{
        string path_;
        promise<string> *prom_;

        GetDataCallBackArgs(string path, promise<string> *prom):path_(path), prom_(prom){}
    };

    GetDataCallBackArgs *args = new GetDataCallBackArgs(path, &prom);

    int flag = zoo_aget(zh_, path.c_str(), 0, 
                        [](int rc, const char* value, int value_len, const Stat* stat, const void* data){
                            auto ctx = static_cast<const GetDataCallBackArgs*> (data);
                            
                            if(rc != ZOK){
                                WARN("get data error! path: ", ctx->path_);
                                ctx->prom_->set_value("");
                            }
                            else{
                                string result(value, value_len);
                                ctx->prom_->set_value(result);
                            }

                            delete ctx;
                        }, 
                        args);
    
    if(flag != ZOK){
        WARN("get data: ", path, " fail!");
        delete args;
        return "";
    }
    
    return fut.get();
}

void ZkClient::ExistCallBack(int rc, const struct Stat* stat, const void* data)
{
    auto* args = static_cast<const ExistCallBackArgs*>(data);

    if(rc == ZNONODE){
        int flag = zoo_acreate(args->client_->zh_, args->path_.c_str(), args->data_.c_str(), args->data_.size(), &ZOO_OPEN_ACL_UNSAFE, args->state_, CreateCallBack, nullptr);
    }
    else{
        WARN("znodee already exxist: ", args->path_);
    }
    
    delete args;
}

void ZkClient::CreateCallBack(int rc, const char* name, const void* data)
{
    if(rc == ZOK){
        INFO("create node: ", name);
    }
    else{
        WARN("cerate node: ",name, " fail!");
    }
}