#include "TickCounter.h"
#include <opencv2/core/core.hpp> 


#define __TC__		1

CTickCounter::CTickCounter(void)
{
#if __TC__
	t_time0 = (double)cvGetTickCount();
#endif
}

CTickCounter::CTickCounter(string strInfo)
{
#if __TC__

	m_strInfo = strInfo;
	t_time0 = (double)cvGetTickCount();
#endif

}
CTickCounter::~CTickCounter(void)
{
#if __TC__

	t_time1 = (double)cvGetTickCount();
	t_timeConsumed = (t_time1-t_time0)/(double)cvGetTickFrequency()/1000;

	printf("%s:\t\t\t%fms\n", m_strInfo.c_str(), t_timeConsumed);
	//TRACE("%s:\t\t\t%fms\n", m_strInfo.c_str(), t_timeConsumed);

#endif

}
