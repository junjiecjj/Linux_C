/*************************************************************************
>> File Name: posix_sem2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时31分27秒

>> 此程序的功能是：
https://blog.csdn.net/tonglin12138/article/details/93751861
************************************************************************/

//有名信号量要指定一个名字somename，打开成功后
//将以sem.somename的形式存在于/dev/shm/目录下。
//书中用二值信号量做互斥同步，这里我直接用mutex。

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define MAXSIZE 10
void *produce(void *);
void *consume(void *);

typedef void *(*handler_t)(void *); //线程函数指针

struct _shared {
  int buff[MAXSIZE];

  sem_t *nempty;
  sem_t *nstored;
}; //共享缓冲
typedef struct _shared shared;
shared shared_;
pthread_mutex_t mutex; //互斥锁
int nitems;            //生产和消费的数目

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage:namedsem <#items>\r\n");
    exit(-1);
  }
  nitems = atoi(argv[1]);
  const char *const SEM_NEMPTY = "nempty";   //信号量的“名字”
  const char *const SEM_NSTORED = "nstored"; //信号量的“名字”
  pthread_t tid_produce;                     //生产者线程 id
  pthread_t tid_consume;                     //消费者线程 id
  //初始化信号量和互斥锁
  pthread_mutex_init(&mutex, NULL);
  shared_.nstored = sem_open(SEM_NSTORED, O_CREAT | O_EXCL, 0644, 0);
  shared_.nempty = sem_open(SEM_NEMPTY, O_CREAT | O_EXCL, 0644, MAXSIZE);
  memset(shared_.buff, 0x00, MAXSIZE);

  //线程创建
  handler_t handler = produce;
  pthread_setconcurrency(2);
  if ((pthread_create(&tid_produce, NULL, handler, NULL)) < 0) {
    printf("pthread_create error\r\n");
    exit(-1);
  }
  //    sleep(5);
  handler = consume;
  if ((pthread_create(&tid_consume, NULL, handler, NULL)) < 0) {
    printf("pthread_create error\r\n");
    exit(-1);
  }

  //线程回收
  pthread_join(tid_produce, NULL);
  pthread_join(tid_consume, NULL);

  //信号量锁销毁
  sem_unlink(SEM_NEMPTY);
  sem_unlink(SEM_NSTORED);
  pthread_mutex_destroy(&mutex);
  exit(0);
}

void *produce(void *args) {
  int i;
  for (i = 0; i < nitems; i++) {
    sem_wait(shared_.nempty);
    pthread_mutex_lock(&mutex);
    shared_.buff[i % MAXSIZE] = i;
    printf("add an item\r\n");
    pthread_mutex_unlock(&mutex);
    sem_post(shared_.nstored);
  }
  return NULL;
}

void *consume(void *args) {
  int i;
  for (i = 0; i < nitems; i++) {
    sem_wait(shared_.nstored);
    pthread_mutex_lock(&mutex);
    printf("consume an item\r\n");
    if (shared_.buff[i % MAXSIZE] != i)
      printf("buff[%d]=%d\r\n", i, shared_.buff[i % MAXSIZE]);
    pthread_mutex_unlock(&mutex);
    sem_post(shared_.nempty);
  }
  return NULL;
}
