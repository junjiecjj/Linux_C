/*************************************************************************
>> File Name: callCMD_exec.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年09月12日 星期日 11时32分07秒

>> 此程序的功能是：C程序中exec系列函数调用shell CMD示例；
************************************************************************/

#include "color.h"
#include <complex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

  printf("使用system调研shell cmd的演示示例......\n");
  printf(DEEPGREEN_YELLOW "-------------------------------------例子1-----------------------------------------\n""\033[0m" COLOR_RESET);
  char *argv_1[] = {"ls", "-al", "/etc/passwd", NULL};

  if (vfork() == 0) {
    execv("/bin/ls", argv_1);
  } else {
    printf("This is the parent process\n");
  }

  char *const ps_argv[] = {"ps", "ax", 0};
  char *const ps_envp = {"PATH=/bin:/usr/bin", "TERM=console", 0};

  printf("-------------------------------------例子1  execv 函数--------------------------------------------\n");

  int childpid;
  int res = 0;
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

  printf("----------------------------------------------------------------------------\n");
  // res = execv("/bin/ps", ps_argv); //此后的程序不会在运行
  printf("[File:%s, Function:%s, Line:%d, Time:%s, %s], res = %d \n", __FILE__,
         __func__, __LINE__, __DATE__, __TIME__, res);

  printf("-------------------------------------例子2 execvp 函数-----------------------------------------\n");

  if (fork() == 0) {
    // child process
    char *execvp_str[] = {"echo", "executed by execvp", ">>", "abc.txt", NULL};
    if (execvp("echo", execvp_str) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execvp done\n\n");
  }

  printf("---------------------------------------------------------------------------------------------------\n");
  // res = execvp("ps", ps_argv); //此后的程序不会在运行
  printf("[File:%s, Function:%s, Line:%d, Time:%s, %s], res = %d \n\n\n",
         __FILE__, __func__, __LINE__, __DATE__, __TIME__, res);

  printf("-------------------------------------例子3 execve 函数--------------------------------------------\n");

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

  printf("------------------------------------------------------------------------------------------------\n");

  // res = execve("/bin/ps", ps_argv, ps_envp); //此后的程序不会在运行
  printf("[File:%s, Function:%s, Line:%d, Time:%s, %s], res = %d \n\n\n",
         __FILE__, __func__, __LINE__, __DATE__, __TIME__, res);
  printf("-------------------------------------例子4 execl 函数-------------------------------------------\n");

  if (fork() == 0) {
    // child process
    if (execl("/usr/bin/echo", "echo", "executed by execl", NULL) < 0) {
      perror("error on exec");
      exit(0);
    }
  } else {
    // parent process
    wait(&childpid);
    printf("execl done\n\n");
  }

  printf("-----------------------------------------------------------------------------------------------\n");

  // res = execl("/bin/ps", "ps", "ax", 0); //此后的程序不会在运行
  printf("[File:%s, Function:%s, Line:%d, Time:%s, %s], res = %d \n", __FILE__,
         __func__, __LINE__, __DATE__, __TIME__, res);
  printf("-------------------------------------例子5 execlp 函数-----------------------------------------\n");

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

  printf("-----------------------------------------------------------------------------------------------\n");

  // res = execlp("ps", "ps", "ax", 0); //此后的程序不会在运行
  printf("[File:%s, Function:%s, Line:%d, Time:%s, %s], res = %d \n\n\n",
         __FILE__, __func__, __LINE__, __DATE__, __TIME__, res);
  printf("-------------------------------------例子6 execle 函数-----------------------------------------\n");

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

  printf("-----------------------------------------------------------------------------------------------\n");

  res = execle("/bin/ps", "ps", "ax", 0, ps_envp); //此后的程序不会在运行
  printf("[File:%s, Function:%s, Line:%d, Time:%s, %s], res = %d \n\n\n",
         __FILE__, __func__, __LINE__, __DATE__, __TIME__, res);

  printf("-------------------------------------结束-----------------------------------------------------\n");

  exit(0);
}
