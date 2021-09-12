/*************************************************************************
>> File Name: callCMD_exec.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年09月12日 星期日 11时32分07秒

>> 此程序的功能是：
************************************************************************/

#include "color.h"
#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

int main(int argc, char *argv[]) {

  printf("使用system调研shell cmd的演示示例......\n");
  printf(DEEPGREEN_YELLOW "-------------------------------------例子1----------"
                          "-------------------------------\n"
                          "\033[0m" COLOR_RESET);
  char *argv_1[] = {"ls", "- al", "/etc/passwd", NULL};

  if (vfork() == 0) {
    execv("/bin/ls", argv_1);
  } else {
    printf("This is the parent process\n");
  }

  printf("-------------------------------------例子1  execv 函数----------"
         "-------------------------------\n");

  int childpid;
  int i;

  if (fork() == 0) {
    // child process
    char *execv_str[] = {"echo", "executed by execv", NULL};
    if (execv("/usr/bin/echo", execv_str) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execv done\n\n");
  }

  printf("-------------------------------------例子2 execvp 函数----------"
         "-------------------------------\n");

  if (fork() == 0) {
    // child process
    char *execvp_str[] = {"echo", "executed by execvp", ">>", "~/abc.txt",
                          NULL};
    if (execvp("echo", execvp_str) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execvp done\n\n");
  }

  printf("-------------------------------------例子3 execve 函数----------"
         "-------------------------------\n");

  if (fork() == 0) {
    // child process
    char *execve_str[] = {"env", NULL};
    char *env[] = {"PATH=/tmp", "USER=lei", "STATUS=testing", NULL};
    if (execve("/usr/bin/env", execve_str, env) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execve done\n\n");
  }

  printf("-------------------------------------例子4 execl 函数----------"
         "-------------------------------\n");

  if (fork() == 0) {
    // child process
    if (execl("/usr/bin/echo", "echo", "executed by execl", NULL) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execv done\n\n");
  }

  printf("-------------------------------------例子5 execlp 函数----------"
         "-------------------------------\n");

  if (fork() == 0) {
    // child process
    if (execlp("echo", "echo", "executed by execlp", NULL) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execlp done\n\n");
  }

  printf("-------------------------------------例子6 execle 函数----------"
         "-------------------------------\n");

  if (fork() == 0) {
    // child process
    char *env[] = {"PATH=/home/gateman", "USER=lei", "STATUS=testing", NULL};
    if (execle("/usr/bin/env", "env", NULL, env) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execle done\n\n");
  }

  printf("-------------------------------------结束----------"
         "-------------------------------\n");

  exit(0);
}
