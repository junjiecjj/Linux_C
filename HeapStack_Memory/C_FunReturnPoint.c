
/*************************************************************************
>> File Name: C_struct.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月10日 星期日 00时40分10秒
>> 此程序的功能是：
>> Last Modified : 2021年03月10日 星期三 11时10分03秒

*************************************************************************/

#include<stdio.h>
#include<stdlib.h>




int globalA = 347;

int returnA(void)
{
    int a = 123;
    globalA = 999;
    printf("a = %d\n", a);
    return a;
}


char *returnStrStatic()
{
    static char p[]="hello world!";
    return p;
}

char *returnStr()
{
    char p[]="hello world!";
    return p;
}

int main(void)
{
    int aa = 222;
    printf("1 aa = %d\n", aa);
    printf("1 globalA = %d\n", globalA);
    aa = returnA();
    printf("2 aa = %d\n", aa);
    printf("2 globalA = %d\n", globalA);

    // char *str;
    // str=returnStr();
    // printf("%s\n", str);


    char *str;
    str=returnStrStatic();
    printf("%s\n", str);

    return 0;
}
