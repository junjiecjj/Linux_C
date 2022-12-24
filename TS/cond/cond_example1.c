/*************************************************************************
>> File Name: cond_example1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月14日 星期日 13时33分35秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <stdio.h>

int max_buffer = 10;
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;

void *produce(void *args) {
  while (1) {
    pthread_mutex_lock(&mutex);
    while (count == max_buffer) {
      printf("buffer is full, wait...\n");
      pthread_cond_wait(&notfull, &mutex);
    }
    printf("produce ...\n");
    count++;
    sleep(1);
    pthread_cond_signal(&notempty);
    pthread_mutex_unlock(&mutex);
  }
}

void *consumer(void *args) {
  while (1) {
    pthread_mutex_lock(&mutex);
    while (count == 0) {
      printf("buffer is empty, wait...\n");
      pthread_cond_wait(&notempty, &mutex);
    }
    printf("consumer ...\n");
    count--;
    sleep(1);
    pthread_cond_signal(&notfull);
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t t1, t2, t3, t4;
  pthread_create(&t1, NULL, &produce, NULL);
  pthread_create(&t2, NULL, &produce, NULL);

  pthread_create(&t3, NULL, &consumer, NULL);
  pthread_create(&t4, NULL, &consumer, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  return 0;
}
