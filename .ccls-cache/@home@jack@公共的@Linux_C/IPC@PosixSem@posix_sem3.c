/*************************************************************************
>> File Name: posix_sem3.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时37分09秒

>> 此程序的功能是：

https://blog.csdn.net/Z_Stand/article/details/102066654
************************************************************************/

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  //创建信号量并初始化信号量的value值为4
  unsigned int sem_value = 4;
  sem_t *sem = sem_open("posix_sem", O_RDWR | O_CREAT, 0777, sem_value);
  if (sem == SEM_FAILED) {
    printf("sem_open failed\n");
    _exit(-1);
  }

  //获取信号量的value值
  if (sem_getvalue(sem, &sem_value) != -1) {
    printf("sem_getvalue is %d\n", sem_value);
  }

  //对信号量进行p(-1)操作
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  // sem_trywait(sem);//并不会发生阻塞，此时sem值已经为0，无法再进行p操作

  if (sem_getvalue(sem, &sem_value) != -1) {
    printf("sem_getvalue after sem_wait is %d\n", sem_value);
  }

  //对信号量进行v(+1)操作
  sem_post(sem);
  sem_post(sem);
  sem_post(sem);
  sem_post(sem);

  if (sem_getvalue(sem, &sem_value) != -1) {
    printf("sem_getvalue after sem_post is %d\n", sem_value);
  }

  if (sem_close(sem) != -1) {
    printf("sem_close success\n");
  }

  printf("wait for unlink sem\n");
  sleep(10);

  //删除名称为posix_sem信号量
  if (sem_unlink("posix_sem") != -1) {
    printf("sem_unlink success \n");
  }

  return 0;
}
