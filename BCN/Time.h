#ifndef _TIME_CJJ
#define _TIME_CJJ

#include<locale.h>
#include<time.h>


/*
struct timeval{
    long tv_sec; 	// 秒
    long tv_usec;  	// 微秒
};

struct timezone{
    int tz_minuteswest;    // 和greenwich时间差了多少分钟
    int tz_dsttime;        // 日光节约时间的状态
};

*/

//返回北京时间
char * GetTimeOfNow();

#endif // _TIME_CJJ



