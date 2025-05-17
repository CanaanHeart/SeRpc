#ifndef _DNSRESOLVER_H_
#define _DNSRESOLVER_H_

#include "../logger/Logger.h"

#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

#include <string>
#include <vector>

class DnsResolver{
public:
    static bool IsValidIpv4(const std::string str);

    static bool Resolve(const std::string &hostname, std::vector<std::string> &ip_list, std::string &err_msg);
private:
    static bool IsValidSubstr(const std::string str);
};

#endif // _DNSRESOLVER_H_