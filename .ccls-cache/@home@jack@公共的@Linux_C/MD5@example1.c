/*************************************************************************
>> File Name: example1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月27日 星期六 22时43分35秒

>> 此程序的功能是：
************************************************************************/

#include "md5.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void main(void) {
  int read_len;
  int i;
  char temp[8] = {0};
  unsigned char digest[16]; //存放结果
  char hexbuf[128] = "12334567";
  unsigned char decrypt[16] = {0};
  unsigned char decrypt32[64] = {0};

  MD5_CTX md5c;

  MD5Init(&md5c); //初始化
  read_len = strlen(hexbuf);
  MD5Update(&md5c, (unsigned char *)hexbuf, read_len);

  MD5Final(&md5c, decrypt);
  strcpy((char *)decrypt32, "");

  for (i = 0; i < 16; i++) {
    sprintf(temp, "%02x", decrypt[i]);
    strcat((char *)decrypt32, temp);
  }
  printf("md5:%s\n", decrypt32);

  return;
}
