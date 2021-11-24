/*************************************************************************
>> File Name: ByteSequence.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月21日 星期日 23时12分45秒

>> 此程序的功能是：
************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#define MAGIC 0x12345678

void ByteSequence1() {
  FILE *fp;
  int n = MAGIC;
  char *p = (char *)&n;

  printf("n: 0x%08x, ", n);
  printf("%x %x %x %x\n", p[0], p[1], p[2], p[3]);

  fp = fopen("data", "w");
  fwrite(&n, sizeof(int), 1, fp);
  fclose(fp);

  n = 0;
  fp = fopen("data", "r");
  fread(&n, sizeof(int), 1, fp);
  fclose(fp);

  p = (char *)&n;
  printf("n: 0x%08x, ", n);
  printf("%x %x %x %x\n", p[0], p[1], p[2], p[3]);
}

int main(int argc, char *argv[]) {
  ByteSequence1();
  return 0;
}
