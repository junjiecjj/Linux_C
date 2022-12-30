/*************************************************************************
>> File Name: test.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月27日 星期日 00时49分15秒

>> 此程序的功能是：
https://www.runoob.com/w3cnote/cpp-static-const.html
************************************************************************/

#ifndef _TASKFUNC_H_
#define _TASKFUNC_H_

#include "TestDefine.h"

void ChangeStu(Student *student);

void Swap(int *a, int *b);
void Swap(float *a, float *b);
void Swap(char *a, char *b);
void Swap(bool *a, bool *b);
void TestSwap(void);

#endif // _TASKFUNC_H_