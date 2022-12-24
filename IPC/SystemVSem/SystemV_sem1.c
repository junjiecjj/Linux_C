/*************************************************************************
>> File Name: sem_example1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时12分38秒

>> 此程序的功能是：
https://cloud.tencent.com/developer/article/1696916
************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <linux/sem.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#define NUMS 10

int get_sem_val(int sid, int semnum) //取得当前信号量
{
  return (semctl(sid, semnum, GETVAL, 0));
}

int main(int argc, char *argv[]) {
  /* int I; */
  int sem_id;
  int pid;
  int ret;
  struct sembuf sem_op; //信号集结构
  union semun sem_val;  //信号量数值

  //建立信号量集，其中只有一个信号量
  sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
  // IPC_PRIVATE私有，只有本用户使用，如果为正整数，则为公共的；1为信号集的数量；
  if (sem_id == -1) {
    printf("create sem error!\n");
    exit(1);
  }
  printf("create %d sem success!\n", sem_id);
  //信号量初始化
  sem_val.val = 1;
  //设置信号量,0为第一个信号量，1为第二个信号量,...以此类推；SETVAL表示设置
  ret = semctl(sem_id, 0, SETVAL, sem_val);
  if (ret < 0) {
    printf("initlize sem error!\n");
    exit(1);
  }
  //创建进程
  pid = fork();
  if (pid < 0) {
    printf("fork error!\n");
    exit(1);
  } else if (pid == 0) {
    //一个子进程，使用者
    for (int i = 0; i < NUMS; i++) {
      sem_op.sem_num = 0;
      sem_op.sem_op = -1;
      sem_op.sem_flg = 0;
      semop(sem_id, &sem_op, 1); //操作信号量，每次-1
      printf("%d 使用者: %d\n", i, get_sem_val(sem_id, 0));
    }
  } else {
    //父进程，制造者
    for (int i = 0; i < NUMS; i++) {
      sem_op.sem_num = 0;
      sem_op.sem_op = 1;
      sem_op.sem_flg = 0;
      semop(sem_id, &sem_op, 1); //操作信号量，每次+1
      printf("%d 制造者: %d\n", i, get_sem_val(sem_id, 0));
    }
  }
  exit(0);
}
