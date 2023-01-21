/*************************************************************************
>> File Name: C_struct.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月10日 星期日 00时40分10秒
>> 此程序的功能是：
>> Last Modified : 2021年03月10日 星期三 11时10分03秒

*************************************************************************/

#include "StructMallocFree.h"






void showStruct(const DATASTR *p)
{
    printf("a = %d, b = %.3lf, c = %.3f, \n",p->a,p->b,p->c);
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

DATASTR ReturnStruct(void)
{
    DATASTR tmp;
    tmp.m_age = 12;
    tmp.m_sala  = 11287.32;
    tmp.m_score = 92.65;
    showStruct(&tmp);
    return tmp;
}

void UseReturnStru(void){
    DATASTR stu2;
    DATASTR *p  = ;
    DATASTR *P;


    P = (DATASTR *)malloc(2 * sizeof(DATASTR));

    stu2.m_age = 12;
    stu2.m_sala  = 11287.32;
    stu2.m_score = 92.65;
    showStruct(&stu2);

    free(P); P = NULL;
}

int main(int argc, char *argv[])
{
    TestStruMalloc();
    return 0;
}
