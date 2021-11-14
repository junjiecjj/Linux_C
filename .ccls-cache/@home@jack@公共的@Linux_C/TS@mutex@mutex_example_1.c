/*************************************************************************
>> File Name: mutex_example_1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月14日 星期日 11时06分36秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <stdio.h>

int ticket_num = 10000000;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *sell_ticket(void *arg) {
  while (ticket_num > 0) {
    pthread_mutex_lock(&mutex);
    if (ticket_num > 0) {
      ticket_num--;
    }
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t t1, t2, t3;
  pthread_create(&t1, NULL, &sell_ticket, NULL);
  pthread_create(&t2, NULL, &sell_ticket, NULL);
  pthread_create(&t3, NULL, &sell_ticket, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  printf("ticket_num=%d\n", ticket_num);
  return 0;
}
