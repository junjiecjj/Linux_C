/*************************************************************************
>> File Name: test.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月25日 星期五 19时15分58秒

>> 此程序的功能是：
************************************************************************/

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int x = 10;      //   没问题，10是常量
int y = 3+20 ;   //   没问题，用于初始化的是常量表达式

int x2 = 2*x; //不行，x是变量


int main(int argc, char *argv[]){

  printf("x2  = %d\n",x2);


  return 0;
}