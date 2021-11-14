/*************************************************************************
>> File Name: barrier_2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月15日 星期一 00时26分22秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <stdio.h>

pthread_barrier_t barrier;

void *go(void *arg) {
  sleep(rand() % 10);
  printf("%lu is arrived.\n", pthread_self());
  pthread_barrier_wait(&barrier);
  printf("%lu go shopping...\n", pthread_self());
}

int main() {
  pthread_barrier_init(&barrier, NULL, 3);

  pthread_t t1, t2, t3;
  pthread_create(&t1, NULL, &go, NULL);
  pthread_create(&t2, NULL, &go, NULL);
  pthread_create(&t3, NULL, &go, NULL);

  pthread_join(t1, NULL);
  return 0;
}
