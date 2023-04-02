

#ifndef _Utility_CJJ
#define _Utility_CJJ



#include "StdAfx.h"


#define PI            3.14159265358979
#define SMALLPROB     1.0e-12
#define DBL_MAX       1.0e+300
#define MONTHS        12
#define SIZE          4


#ifdef __cplusplus
extern "C" {
#endif

//一维数组求和
int Sum1DIntArray1(const int ar[], int n);
int Sum1DIntArray2(int *start, int *end);

//一维数组打印
void Display1DIntArray(const int arr[], int size);

void Display1DIntArray2(const int arr[], int size);

void Display1DIntArray3(const int *arr, int size);

void Display1DIntArray4(const int *arr, int size);
void mult_array(double ar[], int n, double mult);



// C++中无法使用
void Display2DIntArray(int rows, int cols, int (*A)[cols]);

// C++中无法使用
void Display2DIntArray1(int rows, int cols, int A[][cols]);

//适用于int **A形式申明的二维数组,内存连续或者不连续都行
void Display2DIntArray2DPoint(int row, int col,int **A);

// 适用于A[m][n]形式申明的二维数组, C++中无法使用
void Display2DIntArrayNorm(int rows, int cols, const int ar[rows][cols]);

//适用于int **A形式申明的二维数组,内存连续,不连续时编译不会出错但是不对
void Display2DIntArrayUse1D(int rows, int cols,  int *ar);


void Free2DNotContinueMem(int** pm,int r,int c);





#ifdef __cplusplus
};
#endif



#endif  //  _Utility_CJJ