/*************************************************************************
>> File Name: Sigaction_examp1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 23时11分26秒

>> 此程序的功能是：
************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  struct sigaction newact, oldact;

  /* 设置信号忽略 */
  newact.sa_handler = SIG_IGN; //这个地方也可以是函数
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  int count = 0;
  pid_t pid = 0;

  sigaction(SIGINT, &newact, &oldact); //原来的备份到oldact里面

  pid = fork();
  if (pid == 0) {
    while (1) {
      printf("I'm child gaga.......\n");
      sleep(1);
    }
    return 0;
  }

  while (1) {
    if (count++ > 3) {
      sigaction(SIGINT, &oldact, NULL); //备份回来
      printf("pid = %d\n", pid);
      kill(pid, SIGKILL); //父进程发信号，来杀死子进程
    }

    printf("I am father .......... hahaha\n");
    sleep(1);
  }

  return 0;
}
