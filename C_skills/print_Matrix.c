/*************************************************************************
>> File Name: print_Matrix.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月27日 星期一 18时19分34秒

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

//申明
void showInt2DArray(int m, int n, int (*A)[n]) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5d  ", A[i][j]);
    }
    printf("\n");
  }
}

void showInt2DArray_point(int m, int n, int **A) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5d  ", A[i][j]);
    }
    printf("\n");
  }
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

void Print2DMatrix_1D(int rows, int cols, int *ar)
{
    for(int i=0; i< rows*cols;++i)
    {
        printf("%5d  ", *(ar+i));
    }
    printf("\n");
}



int main(int argc, char *argv[])
{
    int m = 5, n = 10;
    int A[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i * n + j;
        }
    }

    printf("================== A[m][n]的方式申请数组=============================\n");
    printf("打印数组A第一次......\n");
    showInt2DArray(m, n, A);

    printf("打印数组A第二次......\n");
    Print2DMatrix(m, n, A);


    printf("打印数组A第三次......\n");
    // showInt2DArray_point(m, n, A); //不能这么用


    printf("================== int **A的方式申请数组,不连续分配=============================\n");

    int **D;
    //这样分配内存不连续
    D = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        D[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = i * n + j;
        }
    }
    printf("D[1][2] = %d\n", D[1][2]);


    printf("打印数组A第一次......\n");
    showInt2DArray(m, n, D); //这样不会出错，但是结果不对

    printf("打印数组A第二次......\n");
    Print2DMatrix(m, n, D); //这样不会出错，但是结果不对


    printf("打印数组A第三次......\n");
    showInt2DArray_point(m, n, D); //正确的方式


    for(int i=0; i<m; i++)
    {
        free(D[i]);
    }
    free(D);


    printf("================== int **A的方式申请数组,连续分配=============================\n");

    int **E;
    E = (int **)malloc(sizeof(int *) * m);    //分配指针数组
    E[0] = (int *)malloc(sizeof(int) * m * n);//一次性分配所有空间
    for(int i=1; i<m; i++)
    {
        E[i] = E[i-1] + n;
    }//采用如上内存分配方法，意味着将a的值初始化为m*n的二维数组首地址,且这块内存连续

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            E[i][j] = i * n + j;
        }
    }


    printf("E[1][2] = %d\n", E[1][2]);


    printf("打印数组A第一次......\n");
    showInt2DArray(m, n, E); //这样不会出错，但是结果不对

    printf("打印数组A第二次......\n");
    Print2DMatrix(m, n, E); //这样不会出错，但是结果不对


    printf("打印数组A第三次......\n");
    showInt2DArray_point(m, n, E); //正确的方式



    printf("%ld\n", sizeof(E));    //8，指针
    printf("%ld\n", sizeof(E[0])); //8，指针
    free(E[0]);
    free(E);

    return 0;
}
