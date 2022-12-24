/*************************************************************************
>> File Name: semaphore_example3.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 15时36分28秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

int g = 0;
sem_t sem;
// 100000000-200000000
void *pf(void *arg) {
  int i;
  for (i = 0; i < 100000000; i++) {
    sem_wait(&sem); //信号量-1
    g = g + 1;      //读内存 加法指令 写内存
    sem_post(&sem); //信号量+1
  }
}

int main(int argc, char *argv[]) {
  pthread_t ids[2];
  int ret = sem_init(&sem, 0, 1);
  if (ret != 0) {
    perror("sem_init");
  }
  int ret1 = pthread_create(&ids[0], NULL, pf, NULL);
  int ret2 = pthread_create(&ids[1], NULL, pf, NULL);
  if (ret1 != 0 || ret2 != 0) {
    printf("pthread_create:%s\n", strerror(ret1 != 0 ? ret1 : ret2));
    return -1;
  }
  int i;
  for (i = 0; i < 2; i++) {
    pthread_join(ids[i], NULL);
  }
  printf("%d\n", g);
  sem_destroy(&sem);
  return 0;
}
