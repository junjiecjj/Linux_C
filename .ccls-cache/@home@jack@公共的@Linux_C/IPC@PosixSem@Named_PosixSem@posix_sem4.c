/*************************************************************************
>> File Name: posix_sem4_1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时39分31秒

>> 此程序的功能是：
https://blog.csdn.net/Z_Stand/article/details/102066654
************************************************************************/

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_NAME "posix_sem_comu"

int main() {
  int i = 0, j = 0, sem_val = 0, ret;
  sem_t *sem;
  sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

  ret = fork();
  if (ret == -1) {
    printf("sem_open failed \n");
    sem_close(sem);
    sem_unlink(SEM_NAME);
    _exit(-1);
  }
  //创建的子进程，执行10次p操作，每次间隔1秒
  else if (ret == 0) {
    while (i++ <= 10) {
      sem_wait(sem);
      if (sem_getvalue(sem, &sem_val) != -1) {
        printf("child process :sem value is %d\n", sem_val);
        sleep(1);
      }
    }
    _exit(1);
  }
  //父进程执行10次v操作，每次间隔两秒
  else {
    while (j++ <= 10) {
      sem_post(sem);
      if (sem_getvalue(sem, &sem_val) != -1) {
        printf("prarent process :sem value is %d\n", sem_val);
        sleep(2);
      }
    }
  }

  //最终删除sem信号量
  sem_close(sem);
  if (sem_unlink(SEM_NAME) != -1) {
    printf("sem_unlink success \n");
  }
  return 0;
}

//编译：gcc sem_comu.c -o comu -lpthread
输出如下,
    可以很明显的看到子即使子进程的p操作频率快于父进程v操作，但是对同一信号量，他们仍然能够有序同步访问。因为子进程p操作频率较快，此时信号量的value会很快减为0，子进程此时再进行p操作会发生阻塞；直到父进程执行v操作将信号量的值变为1子进程才能继续访问
