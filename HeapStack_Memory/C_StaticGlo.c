/*************************************************************************
>> File Name: C_static_gloable.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月09日 星期六 22时54分58秒
>> 此程序的功能是：展示static、global、register、const、变量作用域和生存周期等。
************************************************************/


#include "C_StaticGlo.h"


//================================== 外部链接 ，静态存储期，文件作用域，所有函数外 ==========================================
int globalA = 347;  /* 外部链接 ，静态存储期，文件作用域*/
int AChangeGlobal(void)
{
    int a = 123;
    globalA = 999;
    printf("[file:%s,fun:%s, Line:%d] a = %d\n", __FILE__, __func__, __LINE__, a);
    return a;
}

void ChangeGlob(void)
{
    int aa = 222;
    printf("[file:%s,fun:%s, Line:%d] aa = %d\n", __FILE__, __func__, __LINE__, aa);
    printf("[file:%s,fun:%s, Line:%d] globalA = %d\n", __FILE__, __func__, __LINE__, globalA);
    aa = AChangeGlobal();
    printf("[file:%s,fun:%s, Line:%d] aa = %d\n", __FILE__, __func__, __LINE__,aa);
    printf("[file:%s,fun:%s, Line:%d] globalA = %d\n", __FILE__, __func__, __LINE__,globalA); // 全局变量先定义，然后在另一个
}

