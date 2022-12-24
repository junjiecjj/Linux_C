/*************************************************************************
>> File Name: barrier_1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月15日 星期一 00时26分11秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

pthread_barrier_t barr;
void pf(void *arg) {
  int x = (int)(arg);
  x = (x + 2) * 3; // 6 9 12
  printf("%lu run....\n", pthread_self());
  sleep(x);
  printf("%lu weak!\n", pthread_self());
  pthread_barrier_wait(&barr);
  printf("%lu go on...\n", pthread_self());
}

int main() {
  pthread_t ids[3];
  pthread_barrier_init(&barr, NULL, 3);
  int i;
  for (i = 0; i < 3; i++) {
    pthread_create(&ids[i], NULL, pf, (void *)i);
  }

  getchar();
  pthread_barrier_destroy(&barr);
  return 0;
}
