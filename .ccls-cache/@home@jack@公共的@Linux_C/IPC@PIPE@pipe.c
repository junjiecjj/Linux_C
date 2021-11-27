/*************************************************************************
>> File Name: pipe.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月27日 星期六 22时38分18秒

>> 此程序的功能是：
************************************************************************/

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
  int ret = -1;
  int fd[2]; // 用于管理管道的文件描述符
  pid_t pid;
  char buf[512] = {0};
  char *msg = "hello world";

  // 创建一个管理
  ret = pipe(fd);
  if (-1 == ret) {
    printf("failed to create pipe\n");
    return -1;
  }

  pid = fork(); // 创建子进程

  if (0 == pid) {                         // 子进程
    close(fd[0]);                         // 关闭管道的读端
    ret = write(fd[1], msg, strlen(msg)); // 向管道写端写入数据
    exit(0);
  } else {                               // 父进程
    close(fd[1]);                        // 关闭管道的写端
    ret = read(fd[0], buf, sizeof(buf)); // 从管道的读端读取数据
    printf("parent read %d bytes data: %s\n", ret, buf);
  }

  return 0;
}
