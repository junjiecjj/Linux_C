/*************************************************************************
>> File Name: key_main4.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月28日 星期日 00时07分45秒

>> 此程序的功能是：
************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

// 函数rand() 虽然可以产生随机序列，但是每次产生的序列其实顺序是一样的。
int rand(void);

// 要想每次都产生不一样的随机序列应该怎么办呢？需要借助srand()函数
void srand(unsigned int seed);

void test1() {
  int i = 0;

  for (i = 0; i < 10; i++) {
    printf("%d ", rand());
  }
  putchar('\n');
}

void test2() {
  int i = 0;

  srand(111);
  for (i = 0; i < 10; i++) {
    printf("%d ", rand());
  }
  putchar('\n');
  srand(1111);
  for (i = 0; i < 10; i++) {
    printf("%d ", rand());
  }
  putchar('\n');
}

int main(int argc, char *argv[]) {

  test1();
  test2();
  return 0;
}
