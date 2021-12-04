/*************************************************************************
>> File Name: singal_examp2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 22时58分04秒

>> 此程序的功能是：
************************************************************************/

#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int count = 1;
void deal_sig(int signum) {
  switch (signum) {
  case 1: // SIGHUP
    printf("signal SIGHUP cached\n");
    break;
  case 2: // SIGINT
    printf("signal SIGINT cached\n");
    break;
  case 3: // SIGQUIT
    printf("signal SIGQUIT cached\n");
    break;
  case 10: // SIGUSR1
    printf("signal SIGUSR1 cached, count = %d\n", count);
    break;
  case 12: // SIGUSR2
    printf("signal SIGUSR2 cached, count = %d\n", count);
    break;
  }
  return;
}

int main(int argc, char **argv) {
  signal(SIGHUP, deal_sig);
  signal(SIGINT, deal_sig);
  signal(SIGQUIT, deal_sig);
  signal(SIGUSR1, deal_sig);
  signal(SIGUSR2, deal_sig);
  signal(SIGKILL, SIG_IGN);
  signal(SIGSEGV, SIG_DFL);
  while (1) {
    count++;
    sleep(1);
  }
  return 0;
}
