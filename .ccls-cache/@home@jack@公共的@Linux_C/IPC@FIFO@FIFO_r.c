/*************************************************************************
>> File Name: FIFO_r.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 17时05分23秒

>> 此程序的功能是：
************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int ret = 0;
  char buf[1024];
  memset(buf, 0, sizeof(buf));

  ret = open("./fifo", O_RDONLY);
  if (0 > ret) {
    printf("%d\n", __LINE__);
    perror("mkfifo"), exit(-1);
  } else {
    read(ret, buf, sizeof(buf));
    printf("read buf is %s\n", buf);
  }
  close(ret);
  return 0;
}
