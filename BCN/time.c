#include<stdio.h>
#include "Time.h"


extern char Time[255];

char * GetTimeOfNow()
{
    char *Wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    time_t Timep;
    struct tm *P;
    //char Time[255];
    time(&Timep);
    P = localtime(&Timep);
    sprintf(Time, "%d/%d/%d %s %d:%d:%d\n",(1900+P->tm_year), (1+P->tm_mon), P->tm_mday, Wday[P->tm_wday], P->tm_hour, P->tm_min, P->tm_sec);
    return Time;
}
