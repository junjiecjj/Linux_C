

// 其他实用的小功能函数,都放在这

#include  "Utility.h"

#define LEN 10


/**************************************************************************************************************************
            常用的打印函数，如打印一维二维数组函数，
***************************************************************************************************************************/
int Sum1DIntArray(const int ar[], int n) // how big an array?
{
    int i;
    int total = 0;

    for (i = 0; i < n; i++)
        total += ar[i];
    printf("The size of ar is %zd bytes.\n", sizeof(ar));

    return total;
}

int Sum1DIntArray1(const int ar[], int n)
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
int Sum1DIntArra2(int *start, int *end)
{
    int total = 0;

    while (start < end)
    {
        total += *start; // add value to total
        start++;         // advance pointer to next element
    }

    return total;
}

/*************************************************************************************************************
 * 打印一维Int数组
*************************************************************************************************************/

void Display1DIntArray(const int arr[], int size)
{
    printf("****************  一维数组：传递一维数组 方法1*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}


void Display1DIntArray2(const int arr[], int size)
{
    printf("****************  一维数组：传递一维数组 方法5*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", *(arr + i));
    }
    printf("\n");
}


void Display1DIntArray3(const int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法2*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", arr[i]);
    }
    printf("\n");
}


void Display1DIntArray4(const int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法4*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", *(arr + i));
    }
    printf("\n");
}


/*************************************************************************************************************
 * 打印二维Int数组
*************************************************************************************************************/


//适用于A[m][n]形式申明的二维数组
void Display2DIntArray(int rows, int cols, const int (*A)[cols])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d  ", A[i][j]);
        }
    printf("\n");
    }
}

void Display2DIntArray1(int rows, int cols, const int A[][cols])
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%8d", A[i][j]);
        }
        printf("\n");
    }
}

//适用于int **A形式申明的二维数组,内存连续或者不连续都行
void Display2DIntArray2DPoint(int rows, int cols, const int **A)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d  ", A[i][j]);
            //printf("%5d  ", A[i*cols+j]);  //错误的做法
        }
    printf("\n");
    }
}



//适用于A[m][n]形式申明的二维数组
void Display2DIntArrayNorm(int rows, int cols, const int ar[rows][cols])
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


//适用于int **A形式申明的二维数组,内存连续,不连续时编译不会出错但是不对;
// A[m][n]形式声明的数组也行
void Display2DIntArrayUse1D(int rows, int cols, const int *ar)
{
    for(int i=0; i< rows;++i)
    {
        for(int j=0; j<cols;++j)
        {
            // printf("%5d  ", *(ar+i*cols+j));
            printf("%5d  ", ar[i*cols+j]);
        }
        printf("\n");
    }

    printf("\n");
}




/*************************************************************************************************************
 * 打印二维Int数组
*************************************************************************************************************/

