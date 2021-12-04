/*************************************************************************
>> File Name: Sigaction_examp5.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 23时13分25秒

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
  /*
      sigset_t mask;
      sigfillset(&mask); //将参数 mask
     信号集初始化，然后把所有的信号加入到此信号集里，在这里表示屏蔽所有信号
      sigdelset(&mask, SIGUSR1); //删除set中的SIGUSR1信号，即——不屏蔽SIGUSR1信号
      sigdelset(&mask, SIGUSR2); //不屏蔽SIGUSR2信号
      sigprocmask(SIG_SETMASK, &mask, NULL);
     //参数SIG_SETMASK指定屏蔽mask中包含的信号集
  */
  struct sigaction sa_usr;
  sa_usr.sa_flags = 0;
  // sa_usr.sa_flags = SA_RESTART;
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
