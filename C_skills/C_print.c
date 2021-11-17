
/*************************************************************************
>> File Name: C_print.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月17日 星期三 15时26分05秒

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

int main(int argc, char *argv[]) {
  printf("abc\bv\n");
  printf("abc\b \n");
  printf("abc\b\n");
  printf("abc\b\b\b   \n");

  printf("def\n");
  printf("\r\033[k");

  printf("def");

  //下面这行并不能直接将某一行直接清除，而是将光标移到本行的开头，这样的话，控制台新的输出就能将之前的覆盖掉。所以才需要加一行printf("DEF")
  printf("\r\033[k");
  printf("DEF");

  printf("\n\n");

  for (int i = 0; i < 10; ++i) {
    printf("这是第%d次输出---------", i);
    for (int j = 0; j < 100000; ++j) {
      //覆盖当前行的所有内容，并回到行首。如果是windows系统,\r\033[k换成\r
      printf("\r\033[k");
    }
  }

  for (int i = 0; i < 10; ++i) {
    printf("这是第%d次输出---------", i);
    for (int j = 0; j < 1000000; ++j) {
      //覆盖当前行的所有内容，并回到行首。如果是windows系统,\r\033[k换成\r
      printf("\b");
    }
  }
  return 0;
}
