/*************************************************************************
>> File Name: posix_sem5_2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时41分23秒

>> 此程序的功能是：
https://blog.csdn.net/Z_Stand/article/details/102066654
************************************************************************/

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char *name = "/posix_sem";
  int j = 0, sem_value = 4;
  sem_t *sem;
  sem = sem_open(name, O_CREAT, 0666, sem_value);
  if (sem == SEM_FAILED) {
    printf("sem open failed \n");
    _exit(-1);
  }
  printf("sem_open %s success \n", name);

  //对信号量进行p操作，每次间隔5秒，总共进行10次
  while (j++ <= 10) {
    if (sem_post(sem) == -1) {
      printf("sem _posd failed\n");
      _exit(-1);
    }
    if (sem_getvalue(sem, &sem_value) != -1) {
      printf("sem post success %d\n", sem_value);
    }
    sleep(5);
  }

  //执行结束后关闭信号量，并删除信名称为name的信号量
  sleep(10);
  if (sem_close(sem) != -1) {
    printf("sem_close success \n");
  }
  if (sem_unlink(name) != -1) {
    printf("sem_unlink success \n");
  }
  return 0;
}
