/*************************************************************************
>> File Name: example2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月27日 星期六 22时44分27秒

>> 此程序的功能是：
************************************************************************/

#include "md5.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FORWORD_FW "123.c"

int calc_md5(char *filename, char *dest) {
  int i;
  int filelen = 0;
  int read_len;
  char temp[8] = {0};
  char hexbuf[128] = {0};
  unsigned char decrypt[16] = {0};
  unsigned char decrypt32[64] = {0};
  MD5_CTX md5;
  char fw_path[128];

  int fdf;

  fdf = open(filename, O_RDWR);
  if (fdf < 0) {
    printf("%s not exist\n", FORWORD_FW);
    return -1;
  }

  MD5Init(&md5);
  while (1) {
    read_len = read(fdf, hexbuf, sizeof(hexbuf));
    if (read_len < 0) {
      close(fdf);
      return -1;
    }
    if (read_len == 0) {
      break;
    }
    filelen += read_len;
    MD5Update(&md5, (unsigned char *)hexbuf, read_len);
  }

  MD5Final(&md5, decrypt);
  strcpy((char *)decrypt32, "");

  for (i = 0; i < 16; i++) {
    sprintf(temp, "%02x", decrypt[i]);
    strcat((char *)decrypt32, temp);
  }
  strcpy(dest, decrypt32);

  printf("md5:%s len=%d\n", dest, filelen);
  close(fdf);

  return filelen;
}

int main(int argc, char *argv[]) {
  int ret;
  int filelen;
  char md5_str[64] = {0};
  char cmd[256] = {0};

  filelen = calc_md5(FORWORD_FW, md5_str);
  if (filelen < 0) {
    printf("calc_md5 fail\n");
    return -1;
  }

  return 0;
}
