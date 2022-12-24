/*************************************************************************
>> File Name: mmap1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月09日 星期四 23时39分33秒

>> 此程序的功能是：

https://cloud.tencent.com/developer/article/1486465
************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int num = 7777777;
  int fd = open("/dev/zero", O_RDWR);
  if (-1 == fd) {
    perror("open zero fail");
    exit(1);
  }

  int *p = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (MAP_FAILED == p) {
    perror("mmap fail");
    exit(1);
  }
  close(fd);
  pid_t pid = fork();
  if (0 == pid) {
    num = 233;
    *p = 666;
  }
  if (0 < pid) {
    wait(NULL);
    printf("*p = %d\n", *p);
    printf("num = %d\n", num);
  }
  if (-1 == pid) {
    perror("fork fail");
    exit(1);
  }
  return 0;
}
