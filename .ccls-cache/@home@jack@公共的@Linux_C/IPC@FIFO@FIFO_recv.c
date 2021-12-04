/*************************************************************************
>> File Name: FIFO_recv.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 16时53分28秒

>> 此程序的功能是：
************************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "usage: %s fifo_file filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fifo = open(argv[1], O_RDONLY);
  if (fifo < 0) {
    perror("fifo");
    exit(EXIT_FAILURE);
  }

  FILE *fp = fopen(argv[2], "wb");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  char buf[BUFSIZ];
  int nbuf;
  while ((nbuf = read(fifo, buf, BUFSIZ)) > 0) {
    fwrite(buf, nbuf, 1, fp);
  }

  close(fifo);
  fclose(fp);
  return 0;
}
