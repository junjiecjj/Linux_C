/*************************************************************************
>> File Name: FIFO_read.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 16时06分54秒

>> 此程序的功能是：
************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH "./myfifo"
#define SIZE 200

int main() {
  int fd = open(PATH, O_RDONLY);
  if (fd < 0) {
    printf("open file error!\n");
    return 0;
  }
  char buffer[SIZE];
  memset(buffer, '\0', sizeof(buffer));
  while (1) {
    int a = read(fd, buffer, sizeof(buffer));
    if (a <= 0) {
      printf("read end or error!\n");
      break;
    }
    printf("%s\n", buffer);
    if (strncmp(buffer, "end", 3) == 0) {
      break;
    }
  }
  close(fd);
  return 0;
}
