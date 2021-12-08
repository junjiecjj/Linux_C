/*************************************************************************
>> File Name: posix_shareMemo_examp3_read.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时11分38秒

>> 此程序的功能是：
************************************************************************/

#include <error.h>
#include <fcntl.h> /* For O_* constants */
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_NAME "/shm0"
#define SHM_SIZE 4096

int main() {
  // 创建或打开共享内存
  int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0);
  if (shm_fd == -1) {
    perror("shm_open error");
    return -1;
  }

  // 获取共享内存大小，读取的时候要用
  struct stat stat = {0};
  if (fstat(shm_fd, &stat)) {
    perror("fstat error");
    return -1;
  }

  // 映射共享内存，大小为上一步获取的大小
  char *buffer =
      (char *)mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, shm_fd, 0);
  if (buffer == (char *)MAP_FAILED) {
    perror("mmap error");
    return -1;
  }
  // 关闭文件描述符
  close(shm_fd);

  // 读取共享内存
  printf("Read Msg:%s\n", buffer);

  // 删除共享内存
  shm_unlink(SHM_NAME);
  return 0;
}
