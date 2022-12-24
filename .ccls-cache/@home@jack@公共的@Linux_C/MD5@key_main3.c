/*************************************************************************
>> File Name: key_main3.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月28日 星期日 00时07分22秒

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
  char buf[120] = {0};
  unsigned int mykeygen;

  if (argc != 4) {
    fprintf(stderr, "Usage: %s <seed> <key num> <keygen>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  sync = atoi(argv[1]);
  key_num = atoi(argv[2]);
  mykeygen = atoi(argv[3]);

  printf(
      "\n--------------采用自定义的keygen、同步码开始加密----------------\n");
  set_keygen(mykeygen);
  print_array("\n明文:", data0, key_num);

  memset(key, 0, sizeof(key));
  len = request_key(sync, key_num, key);
  print_array("密钥:", key, len);

  for (i = 0; i < len; i++) {
    buf[i] = data0[i] ^ key[i];
  }
  print_array("\n密文:", buf, len);

  printf("\n--------------------开始解密--------------------\n");
  set_keygen(mykeygen);

  memset(key, 0, sizeof(key));
  len = request_key(sync, key_num, key);
  for (i = 0; i < len; i++) {
    buf[i] = buf[i] ^ key[i];
  }
  print_array("\n明文:", buf, len);
  exit(EXIT_SUCCESS);
}
