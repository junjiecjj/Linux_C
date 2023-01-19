

#ifndef _ArrayPoint_CJJ
#define _ArrayPoint_CJJ

#include <stdio.h>
#include <stdlib.h>

#include "Utility.h"

#define SIZE 4
#define ROWS 3
#define COLS 4
#define safeFree(p)  saferFree((void **)&(p))

#ifdef __cplusplus
extern "C" {
#endif

int pnt_add(void);
void PntAddress(void);

void  TestArrayPoint(void);

void Show1DArrayKindsOfWays(void);
void Show2DArrayKindsOfWaysC(void);

int ptr_ops(void);

void C_stack();
void C_malloc();
// void CXX_stack();
// void CXX_new();

int ptr_ops(void);

void zippo1(void);
void zippo2(void);


void sum_rows(int ar[][COLS], int rows);
void sum_cols(int [][COLS], int );    // ok to omit names
int sum2d(int (*ar)[COLS], int rows); // another syntax
int array2d(void);

int sum2dvar(int rows, int cols, int ar[rows][cols]);

int vararr2d(void);


char *returnStr(void);
int ReturnStr(void);

char *returnStr1(void);
int ReturnStr1(void);

char *returnStr2(void);
int ReturnStr2(void);

char *GetMemory3(int num);
void ReturnHeap(void);
void saferFree(void **pp);
int testSaveFree(void);
#ifdef __cplusplus
};
#endif



#endif  //_ArrayPoint_CJJ