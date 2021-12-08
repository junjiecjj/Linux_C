/*************************************************************************
>> File Name: shm_unlink.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时12分46秒

>> 此程序的功能是：
************************************************************************/

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(M)                                                            \
  do {                                                                         \
    perror(M);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0);

int main(void) {
  shm_unlink("/xyz");
  return 0;
}
