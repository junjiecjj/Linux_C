/*************************************************************************
>> File Name: posix_sem1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月07日 星期二 23时43分18秒

>> 此程序的功能是：
https://blog.csdn.net/qq_23274715/article/details/110380166
************************************************************************/

#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void process_read(void) {
  sem_t *sem_handled = sem_open("/sem", O_CREAT, 0666, 1);
  if (sem_handled == SEM_FAILED) {
    printf("(%d)sem_open error\n", getpid());
    exit(0);
  }

  for (int i = 0; i < 10; i++) {
    while (1) {
      int res = sem_wait(sem_handled);
      if (res == 0) {
        break;
      }
      if (res == EINTR) {
        continue;
      } else {
        printf("(%d)sem_wait error\n", getpid());
        exit(0);
      }
    }

    printf("(%d)正在持有资源=================================\n", getpid());

    int res = sem_post(sem_handled);
    if (res == -1) {
      printf("(%d)sem_post error\n", getpid());
    }
    usleep(2000);
  }
}

void process_write(void) {
  sem_t *sem_handled = sem_open("/sem", O_CREAT, 0666, 1);
  if (sem_handled == SEM_FAILED) {
    printf("(%d)sem_open error\n", getpid());
    exit(0);
  }

  for (int i = 0; i < 10; i++) {
    while (1) {
      int res = sem_wait(sem_handled);
      if (res == 0) {
        break;
      }
      if (res == EINTR) {
        continue;
      } else {
        printf("(%d)sem_wait error\n", getpid());
        exit(0);
      }
    }

    printf("(%d)正在持有资源..........................\n", getpid());

    int res = sem_post(sem_handled);
    if (res == -1) {
      printf("(%d)sem_post error\n", getpid());
    }

    usleep(1500);
  }

  int res = sem_unlink("/sem");
  if (res == -1) {
    printf("(%d)sem_unlink error\n", getpid());
  }
}

void main(void) {
  pid_t pid = fork();

  if (pid == 0) { //子进程
    printf("child process runing(%d)\n", getpid());
    process_read();
  } else { //父进程
    printf("parent process runing(%d)\n", getpid());
    process_write();
  }
}
