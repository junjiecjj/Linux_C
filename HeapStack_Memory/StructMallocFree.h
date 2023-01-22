/*************************************************************************
>> File Name: C_struct.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月10日 星期日 00时40分10秒
>> 此程序的功能是：
>> Last Modified : 2021年03月10日 星期三 11时10分03秒

*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>



#define SLEN 20





typedef struct names
{ // first structure
    char first[SLEN];
    char last[SLEN];
} NAME;



typedef struct _DATASTRUCT
{
    int m_age ;
    double m_sala;
    float m_score;

} DATASTR;

void showStruct(const DATASTR *p);
// char *s_gets(char *st, int n);

DATASTR ReturnStruct(void);
void UseReturnStru(void);
int TestStruct(void);