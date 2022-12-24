/*************************************************************************
>> File Name: shm_write.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时13分04秒

>> 此程序的功能是：
************************************************************************/

#include <fcntl.h>
#include <string.h>
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
  shmid = shm_open("/xyz", O_RDWR, 0); // 这里必须是O_RDWR才能映射成功
  if (shmid == -1)
    ERR_EXIT("shm_open err");
  printf("shm_open succ\n");
  struct stat buf;
  if (fstat(shmid, &buf) == -1)
    ERR_EXIT("fstat err");
  STU *p;
  //将共享内存对象映射到进程地址空间.
  p = mmap(NULL, buf.st_size, PROT_WRITE, MAP_SHARED, shmid, 0);
  if (p == MAP_FAILED)
    ERR_EXIT("mmap err");
  strcpy(p->name, "cjl"); // 根据映射的地址,写入数据
  p->age = 20;

  close(shmid); // 仅仅需要一个close就可以关闭
  return 0;
}
