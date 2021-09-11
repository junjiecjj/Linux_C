/*************************************************************************
>> File Name: MatrixMultipl.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.07
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define Width 64
#define Block_width 32
//Host code
int main(int argc, char *argv[])
{

    size_t size = Width * Width;

    int *h_M = (int*)malloc(size);
    int *h_N = (int*)malloc(size);
    int *h_P = (int *)malloc(size);
    //初始化h_M, h_N;
    for(int i = 0; i< size; ++i)
    {
        h_M[i] = 1;
        h_N[i] = 1;
        h_P[i] = 0;
    }
    printf("h_M, h_N,h_P分配成功\n");
    return 0;
}
