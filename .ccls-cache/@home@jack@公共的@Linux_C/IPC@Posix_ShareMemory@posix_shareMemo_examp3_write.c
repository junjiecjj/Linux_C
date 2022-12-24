/*************************************************************************
>> File Name: posix_shareMemo_examp3_write.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时11分07秒

>> 此程序的功能是：

https://blog.csdn.net/fuyuande/article/details/107123221


default:
        gcc -o shm_read shm_read.c -lrt
        gcc -o shm_write shm_write.c -lrt
clean:
        rm -rf shm_write shm_read
************************************************************************/

#include <error.h>
#include <fcntl.h> /* For O_* constants */
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/types.h>
#include <unistd.h>

#define SHM_NAME "/shm0"
#define SHM_SIZE 4096

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: ./shm_write msg\n");
    return -1;
  }

  // 创建或打开已存在的共享内存
  int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0);
  if (shm_fd == -1) {
    perror("shm_open error");
    return -1;
  }

  // 设置共享内存大小
  if (ftruncate(shm_fd, SHM_SIZE)) {
    perror("ftruncate error");
    return -1;
  }

  // 映射共享内存
  char *buffer = (char *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
                              MAP_SHARED, shm_fd, 0);
  if (buffer == (char *)MAP_FAILED) {
    perror("mmap error");
    return -1;
  }

  // 关闭共享内存文件描述符，并不影响映射
  close(shm_fd);

  // 写共享内存
  strncpy(buffer, argv[1], strlen(argv[1]));

  // 删除共享内存
  // shm_unlink(shm_fd);
  return 0;
}
