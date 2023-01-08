

#ifndef _Utility_CJJ
#define _Utility_CJJ



#include <stdio.h>
#include <stdlib.h>
//  #include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>
//#include <sys/socket.h>
#include <stddef.h>
#include <locale.h>
#include <time.h>
#include <complex.h>


#define PI            3.14159265358979
#define SMALLPROB     1.0e-12
#define DBL_MAX       1.0e+300
#define MONTHS        12
#define SIZE          4



int Sum1DIntArray(const int ar[], int n);
int Sum1DIntArray1(const int ar[], int n);

int Sum1DIntArra2(int *start, int *end);
void Display1DIntArray(const int arr[], int size);

void Display1DIntArray2(const int arr[], int size);

void Display1DIntArray3(const int *arr, int size);

void Display1DIntArray4(const int *arr, int size);

void Display2DIntArray(int m, int n, const int (*A)[n]);

void Display2DIntArray1(int m, int n, const int A[][n]);

//适用于int **A形式申明的二维数组,内存连续或者不连续都行
void Display2DIntArray2DPoint(int row, int col, const int **A);
//适用于A[m][n]形式申明的二维数组
void Display2DIntArrayNorm(int rows, int cols, const int ar[rows][cols]);

//适用于int **A形式申明的二维数组,内存连续,不连续时编译不会出错但是不对
void Display2DIntArrayUse1D(int rows, int cols, const int *ar);














#endif  //  _Utility_CJJ