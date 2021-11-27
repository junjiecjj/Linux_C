/*************************************************************************
>> File Name: key_main1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月28日 星期日 00时06分40秒

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

int main(int argc, char *argv[]) {
  int i;
  unsigned int len;
  int j, r, key_num;
  unsigned int sync = 0;
  unsigned char key[MAX_KEY_REQUEST];

  key_num = 10;

  printf("\n--------------采用默认keygen 同步码=0 产生密文----------------\n");
  reset_keygen();

  memset(key, 0, sizeof(key));
  len = request_key(sync, key_num, key);

  print_array("密钥0-9:", key, len);

  memset(key, 0, sizeof(key));
  len = request_key(sync, key_num, key);

  print_array("密钥10-19:", key, len);

  printf("\n--------------采用keygen=1234 同步码=0 产生密文----------------\n");
  set_keygen(1234);

  memset(key, 0, sizeof(key));
  len = request_key(sync, key_num, key);

  print_array("密钥0-9:", key, len);

  memset(key, 0, sizeof(key));
  len = request_key(sync, key_num, key);

  print_array("密钥10-19:", key, len);
}
