/*************************************************************************
>> File Name: posix_shareMemo_examp1_write.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时04分02秒

>> 此程序的功能是：
下面两个程序演示了如何使用一个共享内存对象将数据从一个进程传输到另一个进程中。
第一个程序将数据写入到共享内存中，第二个程序将数据从共享内存中读出。
使用gcc编译时，末尾加上 -lrt。
https://blog.csdn.net/fengxinlinux/article/details/76598638
************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd;
  char *addr;
  fd = shm_open("test", O_RDWR | O_CREAT, 0777); //创建共享内存对象
  if (fd < 0) {
    printf("shm_open error\n");
  }

  char string[20] = "Hello world";
  if (ftruncate(fd, strlen(string)) == -1) //改变对象大小
  {
    printf("ftruncate error\n");
  }

  addr = mmap(NULL, strlen(string), PROT_READ | PROT_WRITE, MAP_SHARED, fd,
              0); //内存映射
  if (addr == MAP_FAILED) {
    printf("mmap error\n");
  }

  memcpy(addr, string, strlen(string)); //拷贝字符串到共享内存中

  close(fd);

  return 0;
}
