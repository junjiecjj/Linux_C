/*************************************************************************
>> File Name: cond_example3.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月15日 星期一 00时12分27秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER; //不为空的条件
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;  //不为满的条件

#define CAPCITY 20
char stock[CAPCITY];
int size = 0;

void show(const char *who, const char *con, char s) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%c", stock[i]);
  }
  printf("  %s %c(%s)\n", con, s, who);
}

//生产者线程
void *producer(void *arg) {
  const char *who = (char *)arg;
  for (;;) {
    pthread_mutex_lock(&mutex);
    //被唤醒之后 需要重新判断仓库是否满了
    while (size >= CAPCITY) { //仓库满了,不能进行生产
      printf("仓库满了,%s线程不能进行生产!\n", who);
      //释放锁 要等待 仓库不满的信号
      pthread_cond_wait(&notfull, &mutex); //阻塞释放锁
      //被唤醒之后 重新获得锁
      printf("有人进行了消费,%s线程可以进行生产了!\n", who);
    }
    char prod = 'A' + rand() % 26;
    show(who, "<--", prod);
    stock[size++] = prod;
    pthread_cond_signal(&notempty);
    pthread_mutex_unlock(&mutex);
    usleep((rand() % 100) * 1000);
  }
  return NULL;
}
//消费者线程
void *customer(void *arg) {
  const char *who = (const char *)arg;
  for (;;) {
    pthread_mutex_lock(&mutex);
    while (size == 0) {
      printf("仓库空了,%s消费者等待!\n", who);
      pthread_cond_wait(&notempty, &mutex);
      printf("仓库有货物了,%s可以进行消费了!\n", who);
    }

    char prod = stock[--size];
    show(who, "-->", prod);

    pthread_cond_signal(&notfull);
    pthread_mutex_unlock(&mutex);
    usleep((rand() % 100) * 1000);
  }
  return NULL;
}

int main() {
  pthread_t pid[2], cid[2];

  pthread_create(&pid[0], NULL, producer, "生产者1号");
  pthread_create(&pid[1], NULL, producer, "生产者2号");

  pthread_create(&cid[0], NULL, customer, "消费者1号");
  pthread_create(&cid[1], NULL, customer, "消费者2号");

  getchar();
  return 0;
}
