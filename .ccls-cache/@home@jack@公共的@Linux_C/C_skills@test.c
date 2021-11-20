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

void thread(void *var) {
  int *p = (int *)var;
  printf("In child, a1 = %d\n", *p);
  *p = 2;
  printf("In child, a2 = %d\n", *p);
}

int main() {
  int a = 1;
  printf("a = %d\n", a);
  pthread_t tid;

  pthread_create(&tid, NULL, thread, (void *)&a);
  printf("now a = %d\n", a);
  pthread_join(tid, NULL);
  return 0;
}
