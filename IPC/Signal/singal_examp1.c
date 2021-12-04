/*************************************************************************
>> File Name: singal_examp1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 22时33分54秒

>> 此程序的功能是：
************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

static int alarm_fired = 0;

void ding(int sig) { alarm_fired = 1; }

int main(int argc, char *argv[]) {
  pid_t pid;
  printf("alarm application atarting\n");
  pid = fork();
  switch (pid) {
  case -1:
    perror("fork failed");
    exit(1);
  case 0:
    sleep(5);
    kill(getppid(), SIGALRM);
    exit(0);
  }

  printf("wating for alarm to go off\n");
  (void)signal(SIGALRM, ding);
  pause();
  if (alarm_fired) {
    printf("Ding!\n");
  }
  printf("Done\n");
  exit(0);
}
