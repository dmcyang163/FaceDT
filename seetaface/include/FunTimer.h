#ifndef _FUNTIMER_H
#define _FUNTIMER_H

#include <iostream>
#include <sys/time.h>
#include <string>
using namespace std;

class FunTimer
{
public:
	FunTimer();
	FunTimer(string funName);
	~FunTimer();

private:
	string funName;
	timeval  _start;
	timeval  _end;

};

/**方法一

#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class FunTimer
{
    public:
        FunTimer();
        FunTimer(string funName);
        ~FunTimer();

    private:
                string funName;
        clock_t _start;
        clock_t _end;

};
*/



#endif