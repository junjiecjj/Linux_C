/*************************************************************************
>> File Name: test.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月14日 星期日 01时53分07秒

>> 此程序的功能是：
************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

//链表插入
#define LIST_INSERT(item, list)                                                \
  do {                                                                         \
    item->prev = NULL;                                                         \
    item->next = list;                                                         \
    if (list != NULL)                                                          \
      list->prev = item;                                                       \
    list = item;                                                               \
  } while (0)

int main(int argc, char *argv[]) {
  printf("sasa");
  return 0;
}
