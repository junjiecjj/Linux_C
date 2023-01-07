/*************************************************************************
>> File Name: C_static_gloable.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月09日 星期六 22时54分58秒
>> 此程序的功能是：展示static、global、register、const、变量作用域和生存周期等。

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>

extern int roll_count;


int roll_n_dice(int dice, int sides);
static int rollem(int sides);





