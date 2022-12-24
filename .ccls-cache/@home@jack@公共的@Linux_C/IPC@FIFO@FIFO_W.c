/*************************************************************************
>> File Name: FIFO_W.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 17时07分19秒

>> 此程序的功能是：
************************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MYFIFO "myfifo"
#define MAX_BUFFER_SIZE PIPE_BUF

int fd;
char buff[MAX_BUFFER_SIZE];
int nwrite;

void f_write() {
  fd = open(MYFIFO, O_WRONLY);
  write(fd, buff, MAX_BUFFER_SIZE);
  close(fd);
}

int main(int argc, char *argv[]) {
  if (access(MYFIFO, F_OK) == -1) {
    if ((mkfifo(MYFIFO, 0666) < 0) && (errno != EEXIST)) {
      printf("Cannot create fifo file\n");
      exit(1);
    }
  }

  while (gets(buff) != EOF) {
    f_write();
  }
  exit(0);
}
