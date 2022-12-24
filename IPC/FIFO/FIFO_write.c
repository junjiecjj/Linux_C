/*************************************************************************
>> File Name: FIFO_write.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 16时06分30秒

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

int main(int argc, char *argv[]) {
  int a = mkfifo(PATH, 0666 | S_IFIFO);
  if (a == -1) {
    perror("mkfifo error!");
    exit(0);
  }
  int fd = open(PATH, O_WRONLY);
  if (fd < 0) {
    printf("open file error!\n");
    return 0;
  }
  char buffer[SIZE];
  memset(buffer, '\0', sizeof(buffer));
  while (1) {
    read(0, buffer, sizeof(buffer));
    int b = write(fd, buffer, strlen(buffer) - 1);
    buffer[b] = '\0';
    if (b < 0) {
      printf("wirte error!\n");
      break;
    }
    if (strncmp(buffer, "end", 3) == 0) {
      break;
    }
  }
  close(fd);
  return 0;
}
