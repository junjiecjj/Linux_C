/*************************************************************************
>> File Name: posix_sem6_2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月07日 星期二 23时46分01秒

>> 此程序的功能是：
************************************************************************/

// 消费者
#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> /* For mode constants */
#include <unistd.h>

#define SEM_NAME "/sem0"

int main() {
  sem_t *sem_id;

  // 创建信号量并初始化值为0
  sem_id = sem_open(SEM_NAME, O_CREAT, O_RDWR, 0);
  if (sem_id == SEM_FAILED) {
    perror("sem_open error");
    return -1;
  }

  while (1) {
    // 消费信号量
    if (sem_wait(sem_id)) {
      perror("sem_wait fail, try later\n");
      sleep(1);
      continue;
    }
    printf("consuming succ\n");
  }

  // 关闭信号量
  sem_close(sem_id);
  return 0;
}
