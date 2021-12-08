/*************************************************************************
>> File Name: shm_open.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时12分15秒

>> 此程序的功能是：

https://blog.csdn.net/weixin_40039738/article/details/81135445
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

typedef struct stu {
  char name[32];
  int age;
} STU;

int main(void) {
  int shmid;
  //用来创建或打开一个共享内存对象
  shmid = shm_open("/xyz", O_CREAT | O_RDWR, 0666);
  if (shmid == -1)
    ERR_EXIT("shm_open err");
  printf("shm_open success\n");
  if (ftruncate(shmid, sizeof(STU)) == -1) //修改共享内存对象大小
    ERR_EXIT("ftruncate");

  struct stat buf;
  if (fstat(shmid, &buf) == -1) /// get file status
    ERR_EXIT("fstat err");
  printf("size=%ld mode=%o\n", buf.st_size, buf.st_mode & 0777);

  close(shmid); // 仅仅需要一个close就可以关闭
  return 0;
}
