/*************************************************************************
>> File Name: FIFO_R.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 17时07分06秒

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

#define MYFIFO "myfifo" /* 有名管道文件名*/
#define MAX_BUFFER_SIZE PIPE_BUF
/*常量PIPE_BUF 定义在于limits.h中*/

char buff[MAX_BUFFER_SIZE];
int fd;
int nread;

void f_read() {
  fd = open(MYFIFO, O_RDONLY);
  memset(buff, 0, sizeof(buff));
  nread = read(fd, buff, MAX_BUFFER_SIZE);
  printf("read:'%s' length:%d\n", buff, nread);
  close(fd);
}

int main() {
  if (access(MYFIFO, F_OK) == -1) {
    if ((mkfifo(MYFIFO, 0666) < 0) && (errno != EEXIST)) {
      printf("Cannot create fifo file\n");
      exit(1);
    }
  }
  while (1) {
    f_read();
  }
  exit(0);
}
