#include "utils.h"
#include <unistd.h>

#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

CUtils::CUtils()
{

}
CUtils::~CUtils()
{

}

string CUtils::getPath(string filename/* = ""*/)
{
    string filepath;
    filepath.clear() ;
    char szWorkDir[260] = {0} ;
    if (!getcwd(szWorkDir, 260))
    {
        return "" ;
    }

    filepath = szWorkDir ;
    filepath.append("/") ;
    filepath.append(filename) ;

    return filepath;
}

string CUtils::getCpuid()
{
    FILE * fp;
    char buffer[1024 * 10];
    fp = popen("cat /proc/cpuinfo |grep Serial", "r");

    fgets(buffer, sizeof(buffer), fp);
    printf("%s", buffer + 10);

    pclose(fp);
    char s[20];
    sprintf(s, "%s", buffer + 10); //产生：" 3.142"
    string str = s;
    return str;
}

bool CUtils::isCpuMatch(string cpuid)
{
    string id = CUtils::getCpuid();
    string pi = "000000005cad41fe";     // 000000005cad41fe
    int index = id.find(pi.c_str(), 0); //从pos开始查找字符串s在当前串中的位置
    printf("%d\n", index);


    if (string::npos == id.find(pi.c_str(), 0))
        return false;

    return true;
}


string CUtils::getIpAddress(string type/* = "eth0"*/)
{
    map<string, string> ips;

    struct ifaddrs * ifAddrStruct = NULL;
    void * tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct != NULL)
    {
        if (ifAddrStruct->ifa_addr->sa_family == AF_INET)
        {   // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IPV4 Address %s\n", ifAddrStruct->ifa_name, addressBuffer);

            string strName = ifAddrStruct->ifa_name;
            string strIp = addressBuffer;
            ips.insert(pair<string, string>(strName, strIp));
        }
        else if (ifAddrStruct->ifa_addr->sa_family == AF_INET6)
        {   // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IPV6 Address %s\n", ifAddrStruct->ifa_name, addressBuffer);

            string strName = ifAddrStruct->ifa_name;
            string strIp = addressBuffer;
            ips.insert(pair<string, string>(strName, strIp));
        }


        ifAddrStruct = ifAddrStruct->ifa_next;
    }

    map<string, string>::iterator it = ips.find(type);
    if (it != ips.end())
        return it->second;

    return "";
}


string CUtils::DoubleToString(double Input)
{
    stringstream Oss;
    Oss << Input;
    return Oss.str();
}

double CUtils::StringToDouble(string Input)
{
    double Result;
    stringstream Oss;
    Oss << Input;
    Oss >> Result;
    return Result;
}