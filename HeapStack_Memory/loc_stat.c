


#include "loc_stat.h"

//=================================== 静态存储期，无连接，块内，块作用域，函数内 =========================================

void trystat(void)
{
    int fade = 1;
    static int stay = 1;  // 块作用域的静态变量，无链接

    printf("fade = %d and stay = %d\n", fade++, stay++);
}


void Trystat(void)
{
    for (int count = 1; count <= 3; count++)
    {
        printf("Here comes iteration %d:\n", count);
        trystat();
    }
}