/*************************************************************************
>> File Name: semaphore_example2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 15时33分57秒

>> 此程序的功能是：
************************************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int ticket_num = 10000000;

sem_t sem;

void *sell_ticket(void *arg) {
  while (ticket_num > 0) {
    sem_wait(&sem);
    if (ticket_num > 0) {
      ticket_num--;
    }
    sem_post(&sem);
  }
}

int main(int argc, char *argv[]) {
  sem_init(&sem, 0, 1); // value=1表示最多1个线程同时访问共享资源，与互斥量等价
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
