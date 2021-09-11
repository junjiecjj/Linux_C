/*************************************************************************
>> File Name: test.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.01.19
************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#define N 10
int *A;

void Init()
{
    A = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
        A[i] = i+1;
}
int main(void)
{
    Init();
    for(int i = 0; i < N; i++)
        printf("%5d",A[i]);
    printf("\n");

    return 0;
}
