#include "utils.h"
#include <unistd.h>

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