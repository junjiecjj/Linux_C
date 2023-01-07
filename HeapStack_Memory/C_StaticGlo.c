/*************************************************************************
>> File Name: C_static_gloable.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月09日 星期六 22时54分58秒
>> 此程序的功能是：展示static、global、register、const、变量作用域和生存周期等。
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "C_StaticGlo.h"




//============================================================================
int globalA = 347;  /* 外部链接 ，静态存储期，文件作用域*/
int AChangeGlobal(void)
{
    int a = 123;
    globalA = 999;
    printf("[file:%s,fun:%s, Line:%d] a = %d\n", __FILE__, __func__, __LINE__, a);
    return a;
}


//============================================================================
int roll_count = 0; /* 外部链接 */



void trystat(void)
{
    int fade = 1;
    static int stay = 1;  // 块作用域的静态变量，无链接

    printf("fade = %d and stay = %d\n", fade++, stay++);
}


//============================================================================
extern int count;       // 外部变量，外部链接

static int total = 0;   //内部链接，文件作用域，静态存储期，




void accumulate(int k)  // k是块作用域，无链接
{
    static int subtotal = 0;  //无链接，块作用域的静态变量，静态存储期，

    if (k <= 0)
    {
        printf("loop cycle: %d\n", count);
        printf("subtotal: %d; total: %d\n", subtotal, total);
        subtotal = 0;
    }
    else
    {
        subtotal += k;
        total += k;
    }
}
