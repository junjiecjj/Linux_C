/*************************************************************************
>> File Name: C_BitField.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年04月29日 星期四 16时01分17秒

>> 此程序的功能是：【问答21】C语言：位域和字节序
https://mp.weixin.qq.com/s?__biz=MzUxMjEyNDgyNw==&mid=2247493481&idx=1&sn=fc7af21e8047fd76e0e23809ea12da0b&chksm=f96b959dce1c1c8bc704fc673ec78c7d33f00fd06f53539860e8f3e28197e153aeafc597d30b&mpshare=1&scene=24&srcid=1120cHL13QwAU0HmFl26eLTX&sharer_sharetime=1637384247264&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd
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

#ifndef BOOL_TYPEDEFINE
#define BOOL_TYPEDEFINE
typedef enum { FALSE = 0, TRUE = 1 } BOOL;
#endif

//判断系统大小端,使用联合体判断
BOOL checkBiglittle();

//判断系统大小端，使用指针判断
BOOL checkBiglittle1();

//判断系统大小端，使用指针判断
BOOL checkBiglittle2();

//判断系统大小端，使用强制类型转换判断
BOOL checkBiglittle3();

//可以将任何数据类型打印为二进制格式,大端小端都有用
void AnyTobites(unsigned char *start, int len) {
  if (checkBiglittle3()) //小端
  {
    // start = start + (len - 1);
    for (int i = 0; i < len; ++i) {
      // start = start - i;
      for (int j = 7; j >= 0; j--) {
        printf("%d", (start[len - 1 - i] >> j) & 0x01);
      }
      printf(" ");
    }
  } else //大端
  {
    for (int i = 0; i < len; ++i) {
      for (int j = 7; j >= 0; j--) {
        printf("%d", (start[i] >> j) & 0x01);
      }
      printf(" ");
    }
  }

  printf("\n");
}

void test1() {
  printf("//******************test1 ***********************//\n");
  struct iphdr {
    unsigned char fin : 1;
    unsigned char rsv : 3;
    unsigned char opcode : 4;
    unsigned char mask : 1;
    unsigned char payload : 7;
    /* unsigned char a; */
    /* unsigned char b; */
  } t;
  unsigned char *s;

  //清空内存，防止有乱码
  memset(&t, 0, 2);
  //用指针指向结构体变量t
  s = (unsigned char *)&t;
  //通过数组访问的方式修改内存的值，因为hexdump解析的值是0x81 83,
  //所以0x81必为最低字节的内存的数据
  s[0] = 0x81;
  s[1] = 0x83;
  AnyTobites(s, sizeof(t));
  printf("sizeof(strct iphdr) = %d\n", sizeof(t));
  //打印出位域成员的值
  printf("fin:%d rsv：%d opcode：%d mask：%d paylod：%d \n", t.fin, t.rsv,
         t.opcode, t.mask, t.payload);

  t.fin = 1;
  t.rsv = 0;
  t.opcode = 8;
  t.mask = 1;
  t.payload = 65;
  AnyTobites(s, sizeof(t));
  printf("s[0] = 0x%x\n", s[0]);
  printf("s[1] = 0x%x\n", s[1]);

  return 0;
}

void test2() {
  printf("//******************test2 ***********************//\n");
  struct iphdr {

    unsigned char fin : 1;
    unsigned char rsv : 3;
    unsigned char opcode : 4;
    unsigned char mask : 1;
    unsigned char payload : 7;
  } t;
  unsigned short *s; //这里必须为short,否则119行:s = (unsigned char *)&t;出错
  memset(&t, 0, 2);

  s = (unsigned char *)&t; //这里可以为char也可为short
  //注意，直接赋值0x8183，因为该常量必然和主机字节序一致，
  //小端：83给低字节，
  //大端：81给低字节
  *s = 0x8183;

  AnyTobites(s, sizeof(t));
  printf("fin:%d rsv：%d opcode：%d mask：%d paylod：%d \n", t.fin, t.rsv,
         t.opcode, t.mask, t.payload);
  t.fin = 1;
  t.rsv = 1;
  t.opcode = 8;
  t.mask = 1;
  t.payload = 64;
  AnyTobites(s, sizeof(t));

  unsigned char *s1 = (unsigned char *)s;

  printf("s[0] = 0x%x\n", s1[0]);
  printf("s[1] = 0x%x\n", s1[1]);
}

void test3() {
  printf("//******************test3 ***********************//\n");
  struct iphdr {
    unsigned char fin : 1;
    unsigned char opcode : 4;
    /* unsigned char a; */
    /* unsigned char b; */
  } t;
  unsigned char *s;

  memset(&t, 0, 1);

  s = (unsigned short *)&t;

  t.fin = 1;
  t.opcode = 0xf;
  AnyTobites(s, sizeof(t));
  printf("s[0] = %x\n", s[0]);

  t.fin = 0;
  t.opcode = 0xf;
  AnyTobites(s, sizeof(t));
  printf("s[0] = %x\n", s[0]);

  t.fin = 1;
  t.opcode = 0x0;
  AnyTobites(s, sizeof(t));
  printf("s[0]= %x\n", s[0]);
}

void test4() {
  printf("//******************test4 ***********************//\n");
  /* struct iphdr2 t; */
  struct iphdr2 {
    unsigned char fin : 2;
    unsigned char opcode : 6;
  } t;

  unsigned char *s;

  memset(&t, 0, 1);

  s = (unsigned char *)&t;

  t.fin = 1;
  t.opcode = 0xf;
  AnyTobites(s, sizeof(t));
  printf("s[0] = 0x%x\n", s[0]);

  t.fin = 0;
  t.opcode = 0xf;
  AnyTobites(s, sizeof(t));
  printf("s[0] = 0x%x\n", s[0]);

  t.fin = 1;
  t.opcode = 0x0;
  AnyTobites(s, sizeof(t));
  printf("s[0] = 0x%x\n", s[0]);
}

void hex() {
  printf("//******************* hex ********************//\n");
  unsigned char a = 14;
  printf("a = 0x%x\n", a);

  a = 25; // 00011001
  printf("a = 0x%x\n", a);

  printf("sizeof(unsigned short) = %d\n", sizeof(unsigned short));
}

//判断系统大小端,使用联合体判断
BOOL checkBiglittle() {
  printf("//********** checkBiglittle *****************//\n");
  BOOL res = 1;
  union u {
    int a;
    char b;
  } c;
  c.a = 1;
  if (c.b == 1) //小端返回true,大端返回false
  {
    printf("Little endian\n");
  } else {
    res = 0;
    printf("Big endian\n");
  }
  return res;
}

//判断系统大小端，使用指针判断
BOOL checkBiglittle1() {

  printf("//********** checkBiglittle1 *****************//\n");

  BOOL res = 1;
  int i = 1;
  unsigned char *p;
  p = (unsigned char *)&i;
  if (*p) //小端返回true,大端返回false
  {
    printf("Little endian\n");
  } else {
    res = 0;
    printf("Big endian\n");
  }
  return res;
}

//判断系统大小端，使用指针判断
BOOL checkBiglittle2() {
  printf("//********** checkBiglittle2 *****************//\n");
  BOOL res = true;
  int num = 0x12345678;
  char *p = &num;
  if (*p == 0x78) {
    printf("Little endian\n");
  } else {
    res = false;
    printf("Big endian\n");
  }
  return res;
}

//判断系统大小端，使用强制类型转换判断
BOOL checkBiglittle3() {
  printf("//********** checkBiglittle3 *****************//\n");
  BOOL res = 1;
  short a = 0x0061;
  if ((char)a == 'a') //小端返回true,大端返回false
  {
    printf("Little endian\n");
  } else {
    res = 0;
    printf("Big endian\n");
  }
  return res;
}

BOOL checkBiglittle4() {
  printf("//********** checkBiglittle4 *****************//\n");
  int a = 0x12345678;
  // printf("%x\n", a);
  // printf("%d\n", a);

  char *p = (char *)&a;

  for (int i = 0; i < sizeof(a); i++) {
    printf("内存地址：%p, 所存数据：%.2x\n", &p[i], p[i]);
  }
  /*
  内存地址：012FF7A4, 所存数据：56
  内存地址：012FF7A5, 所存数据：34
  内存地址：012FF7A6, 所存数据：12
  内存地址：012FF7A7, 所存数据：00
  */
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();

  hex();
  checkBiglittle();
  checkBiglittle1();
  checkBiglittle2();
  checkBiglittle3();
  checkBiglittle4();

  return 0;
}
