/*************************************************************************
>> File Name: C_struct.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月10日 星期日 00时40分10秒
>> 此程序的功能是：
>> Last Modified : 2021年03月10日 星期三 11时10分03秒

*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>
//#include <sys/socket.h>
#include <stddef.h>
#include <locale.h>
#include <time.h>
#include <complex.h>

char *s_gets(char *st, int n);
#define MAXTITL 41
#define MAXAUTL 31
#define MAXBKS 100
#define LEN 20
#define FUNDLEN 50
#define SLEN 81



typedef struct names
{ // first structure
    char first[LEN];
    char last[LEN];
} NAME;



typedef struct STRUCT2
{
    int a ;
    double b;
    float c;

} STR2;

void showstr(STR2 *p)
{
    printf("a = %d, b = %lf, c = %f, \n",p->a,p->b,p->c,);
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // 查找换行符
        if (find)                // 如果地址不是NULL,
            *find = '\0';        // 此处放置一个空字符
        else
            while (getchar() != '\n')
                continue; // dispose of rest of line
    }
    return ret_val;
}

int main(int argc, char *argv[])
{


    return 0;
}
