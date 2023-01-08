

// 其他实用的小功能函数,都放在这

#include  "Utility.h"




/**************************************************************************************************************************
            常用的打印函数，如打印一维二维数组函数，
***************************************************************************************************************************/
int sum(int ar[], int n) // how big an array?
{
    int i;
    int total = 0;

    for (i = 0; i < n; i++)
        total += ar[i];
    printf("The size of ar is %zd bytes.\n", sizeof(ar));

    return total;
}

int sum1(const int ar[], int n)
{
    int total = 0;
    for (int i; i < n; ++i)
    {
        total += ar[i];
    }
    return total;
}
/*
以上代码中的const告诉编译器，该函数不能修改ar指向的数组中的内容。如果在函数中不小心使用类似ar[i]++的表达式，编译器会捕获这个错误，并生成一条错误信息。

这里一定要理解，这样使用const并不是要求原数组是常量，而是该函数在处理数组时将其视为常量，不可更改。这样使用const可以保护数组的数据不被修改，就像按值传递可以保护基本数据类型的原始值不被改变一样。一般而言，如果编写的函数需要修改数组，在声明数组形参时则不使用const；如果编写的函数不用修改数组，那么在声明数组形参时最好使用const。
*/
int sump(int *start, int *end)
{
    int total = 0;

    while (start < end)
    {
        total += *start; // add value to total
        start++;         // advance pointer to next element
    }

    return total;
}

void print_2D_matrix(int m, int n, int **A)
{
    printf("*********第1种打印二维数组的方法***************\n");
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%8d", A[i][j]);
        }
        printf("\n");
    }
}
void print_2D_matrix1(int m, int n, int (*A)[n])
{
    printf("*********第2种打印二维数组的方法***************\n");
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%8d", A[i][j]);
        }
        printf("\n");
    }
}

void print_2D_matrix2(int m, int n, int A[][n])
{
    printf("*********第3种打印二维数组的方法***************\n");
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%8d", A[i][j]);
        }
        printf("\n");
    }
}
void displayArray(int arr[], int size)
{
    printf("****************  一维数组：传递一维数组 方法1*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

void displayArray1(int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法2*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", arr[i]);
    }
    printf("\n");
}

void displayArray2(int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法3*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", arr[i]);
    }
    printf("\n");
}
void displayArray3(int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法4*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", *(arr + i));
    }
    printf("\n");
}
void displayArray4(int arr[], int size)
{
    printf("****************  一维数组：传递一维数组 方法5*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", *(arr + i));
    }
    printf("\n");
}