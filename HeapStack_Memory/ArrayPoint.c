

#include "ArrayPoint.h"

//演示数组元素的数组和指针+1的含义
int pnt_addr(void)
{
    short dates [SIZE];
    short * pti;
    short index;
    double bills[SIZE];
    double * ptf;

    pti = dates;    // assign address of array to pointer
    ptf = bills;
    printf("%23s %15s\n", "short", "double");
    for (index = 0; index < SIZE; index ++)
        printf("pointers + %d: %10p %10p\n",  index, pti + index, ptf + index);

    return 0;
}


void Show2DArrayKindsOfWays(void)
{
    int m = 5, n = 10;
    printf("================== A[m][n]的方式申请数组=============================\n");

    int A[m][n]; // 这样的内存是连续的
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i * n + j;
        }
    }
    // printf("打印A[m][n]方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&A[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("打印数组A第一次......\n");
    Display2DIntArray(m, n, A);  //ok

    printf("打印数组A第二次......\n");
    Display2DIntArray1(m, n, A);  //ok


    printf("打印数组A第三次......\n");
    Display2DIntArrayNorm(m, n, A);  //ok


    printf("打印数组A第四次......\n");
    //  Display2DIntArray2DPoint(m, n, &A[0][0]); //不能这么用
    //  Display2DIntArray2DPoint(m, n, A); //不能这么用

    printf("打印数组A第五次......\n");
    Display2DIntArrayUse1D(m, n, &A[0][0]); //ok

    printf("================== int **A的方式申请数组,不连续分配=============================\n");

    int **D;
    //这样分配内存不连续,行内连续，行间不一定连续
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

    // printf("打印**D方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&D[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("打印**D方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&D[i*n+j]);
    //     }
    //     printf("\n");
    // }

    printf("打印数组D第一次......\n");
    Display2DIntArray(m, n,&D[0]); //这样编译不会出错，但是结果不对
    printf("\n");
    Display2DIntArray(m, n, D); //这样编译不会出错，但是结果不对
    printf("\n");
    Display2DIntArray(m, n, D[0]); //这样编译不会出错，但是结果不对

    printf("打印数组D第二次......\n");
    Display2DIntArray1(m, n, D); //这样编译不会出错，但是结果不对

    printf("打印数组D第三次......\n");
    Display2DIntArrayNorm(m, n, D); //这样编译不会出错，但是结果不对

    printf("打印数组D第四次......\n");
    Display2DIntArrayUse1D(m, n, &D[0][0]); //这样编译不会出错，但是结果不对
    Display2DIntArrayUse1D(m, n, D);        //这样编译不会出错，但是结果不对

    printf("打印数组D第五次......\n");
    Display2DIntArray2DPoint(m, n, D); //正确的方式


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
            E[i][j] =  i * n + j;
        }
    }
    // printf("打印**E方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&E[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("E[1][2] = %d\n", E[1][2]);


    printf("打印数组E第一次......\n");
    Display2DIntArray(m, n, E[0]); //这样编译不会出错，但是结果不对

    printf("打印数组E第二次......\n");
    Display2DIntArray1(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第三次......\n");
    Display2DIntArrayNorm(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第四次......\n");
    Display2DIntArrayUse1D(m, n, &E[0][0]); //这样可以，把内存连续分配的二维数组当做一维打印
    printf("\n");
    Display2DIntArrayUse1D(m, n, E[0]); //这样可以，把内存连续分配的二维数组当做一维打印
    printf("\n");
    Display2DIntArrayUse1D(m, n, &E[0]); //这样编译不会出错，但是结果不对
    printf("\n");
    // Display2DIntArrayUse1D(m, n, E[0][0]); //  段错误
    printf("\n");
    Display2DIntArrayUse1D(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第五次......\n");
    Display2DIntArray2DPoint(m, n, E); //正确的方式


    printf("%ld\n", sizeof(E));    //8，指针
    printf("%ld\n", sizeof(E[0])); //8，指针
    free(E[0]);
    free(E);
}



void  TestArrayPoint(void)
{
    pnt_addr();
}