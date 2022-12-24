/*************************************************************************
>> File Name: FIFO_w.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 17时05分39秒

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
  char WtoR[] = "frist execute W,next execute R";

  ret = mkfifo("./fifo", 0666);
  if (0 != ret) {
    perror("mkfifo"), exit(-1);
  }
  printf("%d\n", __LINE__);
  ret = open("./fifo", O_WRONLY);
  if (0 >= ret) {
    perror("open"), exit(-1);
  } else {
    write(ret, WtoR, sizeof(WtoR));
  }
  return 0;
}
