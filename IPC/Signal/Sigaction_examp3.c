/*************************************************************************
>> File Name: Sigaction_examp3.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 23时12分00秒

>> 此程序的功能是：
************************************************************************/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void sig_usr(int signum) {
  if (signum == SIGUSR1) {
    printf("SIGUSR1 received\n");
  } else if (signum == SIGUSR2) {
    printf("SIGUSR2 received\n");
  } else {
    printf("signal %d received\n", signum);
  }
}

int main(void) {
  char buf[512];
  int n;
  struct sigaction sa_usr;
  sa_usr.sa_flags = 0;
  sa_usr.sa_handler = sig_usr; //信号处理函数

  sigaction(SIGUSR1, &sa_usr, NULL);
  sigaction(SIGUSR2, &sa_usr, NULL);

  printf("My PID is %d\n", getpid());

  while (1) {
    if ((n = read(STDIN_FILENO, buf, 511)) == -1) {
      if (errno == EINTR) {
        printf("read is interrupted by signal\n");
      }
    } else {
      buf[n] = '\0';
      printf("%d bytes read: %s\n", n, buf);
    }
  }

  return 0;
}
