/****************************************************************************************************************
本程序用于声明基本函数
*****************************************************************************************************************/
#ifndef _EXPMATH_H_
#define _EXPMATH_H_

/*******************************************定义基本函数*********************************/
/*头文件引用*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Variable.h"


/*********************************定义基本常数*********************************************/
#define		VECTER_COMPUT_MAX_LEN				1024		//矢量运算的最大长度



/*基本函数*/
float  float_round(float x, float y);

int    floatint_round(float x, float y);

float  float_min(float x, float y);

float  float_max(float x, float y);

double double_min(double x, double y);

double double_max(double x, double y);

/*实数矢量运算*/
unsigned int vector_min(float *input, unsigned int N);

unsigned int vector_max(double *input, unsigned int N);

float MeanUpdata(float mean_old, float samp_new, unsigned int N);

float StdUpdata(float mean_old, float std_old, float samp_new,  unsigned int N);

void Quick_sort(float *input, unsigned int first,unsigned int end,unsigned int *idx);

void Quick_sort_noidx(float *input, unsigned int first,unsigned int end);

void Quick_sort_int(unsigned int *input,unsigned int first,unsigned int end);

float float_median(float *input,  unsigned int N);

float float_mean(float *input, unsigned int N);

float float_std(float *input,  unsigned int N, float fmean);

float float_robust_mean(float *input, unsigned int N);

float float_robust_std(float *input,  unsigned int N);

float double_robust_mean(double *input, unsigned int N);

float double_robust_std(double *input,  unsigned int N);

float float_vector_min(float *input,  unsigned int N);

float float_vector_max(float *input,  unsigned int N);

double double_vector_min(double *input,  unsigned int N);

double double_vector_max(double *input,  unsigned int N);

float VecMeanUpdata(float mean_old,  unsigned int M, float mean_new,  unsigned int N);

float VecStdUpdata(float mean_old, float std_old, unsigned int M, float mean_new,float std_new,  unsigned int N);

void double_qsort_noidx(double *input,  unsigned int first,  unsigned int end);

double double_median(double *input,  unsigned int N);



/*复数运算*/
COMPLEX complex_adder(COMPLEX xdata, COMPLEX ydata);

COMPLEX complex_diff(COMPLEX xdata, COMPLEX ydata);

COMPLEX complex_multiper(COMPLEX xdata, COMPLEX ydata);

COMPLEX complex_conj_multiper(COMPLEX xdata, COMPLEX ydata);

COMPLEX complex_divider(COMPLEX xdata, COMPLEX ydata);

float	complex_abs(COMPLEX xdata);

float	complex_phase(COMPLEX xdata);


COMPLEX complex_conj(COMPLEX xdata);

COMPLEX complex_float_adder(COMPLEX xdata, float ydata);

COMPLEX complex_float_diff(COMPLEX xdata, float ydata);

COMPLEX complex_float_multiper(COMPLEX xdata, float ydata);

COMPLEX complex_float_divider(COMPLEX xdata, float ydata);

COMPLEX float_complex_divider(float xdata, COMPLEX ydata);


/*复矩阵运算*/
CMATRIX complex_matrix_adder(CMATRIX xdata, CMATRIX ydata);

CMATRIX complex_matrix_diff(CMATRIX xdata,  CMATRIX ydata);

CMATRIX complex_matrix_multiper(CMATRIX xdata, CMATRIX ydata);

CMATRIX complex_matrix_point_multiper(CMATRIX xdata, CMATRIX ydata);

CMATRIX complex_matrix_point_divider(CMATRIX xdata, CMATRIX ydata);


CMATRIX	complex_matrix_constant_adder(CMATRIX xdata, COMPLEX ydata);

CMATRIX complex_matrix_constant_diff(CMATRIX xdata, COMPLEX ydata);

CMATRIX complex_matrix_constant_multiper(CMATRIX xdata, COMPLEX ydata);


/*实数矩阵运算*/
RMATRIX real_matrix_adder(RMATRIX xdata, RMATRIX ydata);

RMATRIX real_matrix_diff(RMATRIX xdata,  RMATRIX ydata);

RMATRIX real_matrix_multiper(RMATRIX xdata, RMATRIX ydata);

RMATRIX real_matrix_point_multiper(RMATRIX xdata, RMATRIX ydata);

RMATRIX real_matrix_point_divider(RMATRIX xdata, RMATRIX ydata);


RMATRIX	real_matrix_constant_adder(RMATRIX xdata, float ydata);

RMATRIX real_matrix_constant_diff(RMATRIX xdata, float ydata);

RMATRIX real_matrix_constant_multiper(RMATRIX xdata, float ydata);


 //Z=X/Y
 RMATRIX real_matrix_constant_divider(RMATRIX xdata, float ydata);


/*
矩阵相关，求行列式 ，逆矩阵 、伴随式、等
*/
//求解矩阵行列式的值
float Matrix_Determinant(RMATRIX arcs,int n);//按第一行展开计算|A|
//求解矩阵的伴随阵
void Matrix_Adjoint(RMATRIX arcs,int n,RMATRIX *ans);//计算每一行每一列的每个元素所对应的余子式，组成A*
//求矩阵的逆
RMATRIX Matrix_Invers(RMATRIX acr,int n);

//求解矩阵列中最大的值
void find_max_ID_In_Matrix(RMATRIX *arcs,int *rMaxId,int *cMaxId);

// 正北角判断
double dCalDeltaAzimuth(double Course1,double Course2);
#ifdef __cplusplus
}


#endif


/*查找索引编号*/
void find_local_comput(float value,float dmax,float dmin, float dstep, unsigned short dlen, unsigned short *local);

unsigned short  find_local_comput_HJ(long value,long dmax,long dmin, double dstep, unsigned short dlen);


#endif
