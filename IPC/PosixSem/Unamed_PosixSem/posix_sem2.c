/*************************************************************************
>> File Name: posix_sem2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月07日 星期二 23时46分30秒


>> 此程序的功能是：
https://blog.csdn.net/fuyuande/article/details/107123193
************************************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// 消费者
void *consumer_worker(void *arg) {
  sem_t *sem = arg;
  while (1) {
    // 消费信号量
    if (sem_wait(sem)) {
      perror("[consumer] sem_wait error, try later\n");
      sleep(1);
      continue;
    }
    printf("[consumer] consume succ\n");
  }
  return 0;
}

// 生产者
void *producer_worker(void *arg) {
  sem_t *sem = arg;
  while (1) {
    // 生成信号量
    if (sem_post(sem)) {
      perror("[producer] sem_post error, try later\n");
      sleep(1);
      continue;
    }
    printf("[producer] produce succ\n");
    sleep(1);
  }
  return 0;
}

int main(int argc, char **argv) {
  pthread_t consumer, producer;
  if (argc < 2) {
    printf("Usage: ./unnamed_sem time\n");
    return -1;
  }

  int tm = atoi(argv[1]);
  if (tm < 1) {
    printf("invalid param\n");
    return -1;
  }

  sem_t sem;
  // 无名信号量初始化
  if (sem_init(&sem, 0, 0)) {
    perror("sem_init error");
    return -1;
  }

  // 创建生产者线程
  if (pthread_create(&producer, NULL, &producer_worker, (void *)&sem)) {
    perror("create producer_worker error");
    sem_destroy(&sem);
    return -1;
  }

  // 创建消费者线程
  if (pthread_create(&consumer, NULL, &consumer_worker, (void *)&sem)) {
    perror("create consumer_worker error");
    sem_destroy(&sem);
    return -1;
  }

  printf("main thread sleep:%d\n", tm);
  sleep(tm);

  // 无名信号量销毁
  sem_destroy(&sem);
  return 0;
}
