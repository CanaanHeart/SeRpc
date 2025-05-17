#include "DnsResolver.h"

using namespace std;

bool DnsResolver::IsValidIpv4(const string str)
{
    size_t cur_pos = 0, pre_pos = 0;
    while(cur_pos < str.size()){
        cur_pos = str.find('.', pre_pos);
        if(cur_pos != string::npos){
            string sub_str = str.substr(pre_pos, cur_pos - pre_pos);
            if(!IsValidSubstr(sub_str)){
                return false;
            }
            pre_pos = cur_pos + 1;
        }
        else{
            break;
        }
    }

    string sub_str = str.substr(pre_pos);
    if(IsValidSubstr(sub_str)){
        return true;
    }

    return false;
}

bool DnsResolver::Resolve(const std::string &hostname, std::vector<std::string> &ip_list, std::string &err_msg)
{
    struct addrinfo hints, *res = nullptr;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo(hostname.c_str(), nullptr, &hints, &res);

    if(ret != 0){
        err_msg = "getaddrinfo failed: " + string(gai_strerror(ret));
        return false;
    }
    
    for(auto p = res; p != nullptr; p = p->ai_next){
        auto ipv4 = reinterpret_cast<struct sockaddr_in*>(p->ai_addr);
        char ip_str[INET6_ADDRSTRLEN];
        if(inet_ntop(AF_INET, &(ipv4->sin_addr), ip_str, sizeof(ip_str)) != nullptr){
            ip_list.emplace_back(ip_str);
        }
    }

    freeaddrinfo(res);

    if(ip_list.empty()){
        err_msg = "no valid ipv4 address found.";
        return false;
    }
    else{
        return true;
    }
}

bool DnsResolver::IsValidSubstr(const std::string str)
{
    if(str.empty() || str.size() > 3){
        return false;
    }
    if(str.size() > 1 && str[0] == '0'){
        return false;
    }
    for(const auto c: str){
        if(!isdigit(c)){
            return false;
        }
    }
    if(stoi(str) < 0 || stoi(str) > 255){
        return false;
    }

    return true;
}