/*************************************************************************
>> File Name: pipe2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 16时46分30秒

>> 此程序的功能是：
************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "usage: %s parent_sendmsg child_sendmsg\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pipes1[2], pipes2[2];
  if (pipe(pipes1) < 0 || pipe(pipes2) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    close(pipes1[0]);
    close(pipes2[1]);

    char buf[BUFSIZ + 1];
    strcpy(buf, argv[1]);
    write(pipes1[1], buf, strlen(buf));

    int nbuf = read(pipes2[0], buf, BUFSIZ);
    buf[nbuf] = 0;
    printf("parent_proc(%d) recv_msg: %s\n", getpid(), buf);

    close(pipes1[1]);
    close(pipes2[0]);
  } else if (pid == 0) {
    close(pipes1[1]);
    close(pipes2[0]);

    char buf[BUFSIZ + 1];
    int nbuf = read(pipes1[0], buf, BUFSIZ);
    buf[nbuf] = 0;
    printf("child_proc(%d) recv_msg: %s\n", getpid(), buf);

    strcpy(buf, argv[2]);
    write(pipes2[1], buf, strlen(buf));

    close(pipes1[0]);
    close(pipes2[1]);
  }

  return 0;
}
