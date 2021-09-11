/*************************************************************************
>> File Name: 字符串最后一个单词的长度.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2020年05月30日
>> 此程序的功能是：
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<string.h>
#include<sys/socket.h>
#include<stddef.h>
#include<locale.h>
#include<time.h>
#include<complex.h>

#define  L  5000

int main(int argc, char *argv[])
{
    char *S = (char *) malloc(L*sizeof(char));
    int ch;
    while(scanf("%s", S) == 1)
    {
        if((ch=getchar())=='\n')
            break;
    }
    /* printf("len(S) = %ld\n",strlen(S)); */
    printf("len(S) = %ld\n",strlen(S));
    return 0;
}
