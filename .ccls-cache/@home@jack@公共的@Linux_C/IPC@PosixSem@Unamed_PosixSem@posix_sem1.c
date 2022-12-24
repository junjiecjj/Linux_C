/*************************************************************************
>> File Name: posix_sem1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时19分52秒

>> 此程序的功能是：
Linux下进程间通信方式——信号量（Semaphore）
https://www.cnblogs.com/wuyepeng/p/9748552.html
************************************************************************/

#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define total 20
sem_t remain, apple, pear, mutex;
static unsigned int vremain = 20, vapple = 0, vpear = 0;
void *father(void *);
void *mather(void *);
void *son(void *);
void *daughter(void *);
void print_sem();
int main() {
  pthread_t fa, ma, so, da;
  sem_init(&remain, 0, total); //总数初始化为20
  sem_init(&apple, 0, 0);      //盆子中苹果数, 开始为0
  sem_init(&pear, 0, 0);       //盆子中梨子数, 开始为0
  sem_init(&mutex, 0, 1);      //互斥锁, 初始为1
  pthread_create(&fa, NULL, &father, NULL);
  pthread_create(&ma, NULL, &mather, NULL);
  pthread_create(&so, NULL, &son, NULL);
  pthread_create(&da, NULL, &daughter, NULL);
  for (;;)
    ;
}
void *father(void *arg) {
  while (1) {
    sem_wait(&remain);
    sem_wait(&mutex);
    printf("父亲: 放苹果之前, 剩余空间=%u, 苹果数=%u\n", vremain--, vapple++);
    printf("父亲: 放苹果之后, 剩余空间=%u, 苹果数=%u\n", vremain, vapple);
    sem_post(&mutex);
    sem_post(&apple);
    sleep(1);
  }
}
void *mather(void *arg) {
  while (1) {
    sem_wait(&remain);
    sem_wait(&mutex);
    printf("母亲: 放梨子之前, 剩余空间=%u, 梨子数=%u\n", vremain--, vpear++);
    printf("母亲: 放梨子之后, 剩余空间=%u, 梨子数=%u\n", vremain, vpear);
    sem_post(&mutex);
    sem_post(&pear);
    sleep(2);
  }
}
void *son(void *arg) {
  while (1) {
    sem_wait(&pear);
    sem_wait(&mutex);
    printf("儿子: 吃梨子之前, 剩余空间=%u, 梨子数=%u\n", vremain++, vpear--);
    printf("儿子: 吃梨子之后, 剩余空间=%u, 梨子数=%u\n", vremain, vpear);
    sem_post(&mutex);
    sem_post(&remain);
    sleep(3);
  }
}
void *daughter(void *arg) {
  while (1) {
    sem_wait(&apple);
    sem_wait(&mutex);
    printf("女儿: 吃苹果之前, 剩余空间=%u, 苹果数=%u\n", vremain++, vapple--);
    printf("女儿: 吃苹果之前, 剩余空间=%u, 苹果数=%u\n", vremain, vapple);
    sem_post(&mutex);
    sem_post(&remain);
    sleep(3);
  }
}
void print_sem() {
  int val1, val2, val3;
  sem_getvalue(&remain, &val1);
  sem_getvalue(&apple, &val2);
  sem_getvalue(&pear, &val3);
  printf("Semaphore: remain:%d, apple:%d, pear:%d\n", val1, val2, val3);
}
