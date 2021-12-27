/*************************************************************************
>> File Name: 背包问题.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月27日 星期一 12时16分22秒

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
#include<stdbool.h>


void showInt2DArray(int m, int n, int (*A)[n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d  ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void showInt2DArray_point(int m, int n, int **A)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d  ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Print2DMatrix(int rows, int cols, int ar[rows][cols])
{
    for(int i=0; i< rows;++i)
    {
        for(int j=0; j< cols; ++j)
        {
            printf("%5d  ", ar[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int N = 10,  W=0;
    int bag[10][10] = {0};
    int *wt = NULL;
    int *val = NULL;
    wt = (int *)malloc(10 * sizeof(int));
    val = (int *)malloc(10*sizeof(int));
    for(int i = 0; i<10; ++i)
    {
        wt[i] = 0;
        val[i] = 0;
    }


    /* int **db = NULL; */
    scanf("%d %d", &N, &W);



    for (int i = 0; i< N;++i)
    {
        scanf("%d %d", wt+i, val+i);
    }

    for(int i = 1; i <= N; ++i)
    {
        for(int w = 1; w <= W; ++w)
        {
            if(wt[i-1]> w )
            {
                bag[i][w] = bag[i-1][w];
            }
            else
            {
                bag[i][w] = bag[i-1][w] > bag[i-1][w-wt[i-1]]+val[i-1] ? bag[i-1][w] : (bag[i-1][w-wt[i-1]]+val[i-1]);
            }
        }
    }

    printf("最大价值= %d\n", bag[N][W]);
    Print2DMatrix(10, 10, bag);

    showInt2DArray(10, 10, bag);

    showInt2DArray_point(10, 10, bag);

    return 0;
}
