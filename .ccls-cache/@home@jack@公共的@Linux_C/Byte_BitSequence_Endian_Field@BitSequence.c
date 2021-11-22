/*************************************************************************
>> File Name: BitSequence.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月21日 星期日 23时13分00秒

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

//判断系统大小端,使用联合体判断
BOOL checkBiglittle();

//判断系统大小端，使用指针判断
BOOL checkBiglittle1();

//判断系统大小端，使用指针判断
BOOL checkBiglittle2();

//判断系统大小端，使用强制类型转换判断
BOOL checkBiglittle3();

//判断系统大小端,使用联合体判断
BOOL checkBiglittle() {
  BOOL res = 1;
  union u {
    int a;
    char b;
  } c;
  c.a = 1;
  if (c.b == 1) //小端返回true,大端返回false
  {
    // printf("Little endian\n");
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
  内存地址：012FF7A4, 所存数据：78
  内存地址：012FF7A5, 所存数据：56
  内存地址：012FF7A6, 所存数据：34
  内存地址：012FF7A7, 所存数据：12
  */
}

//可以将任何数据类型打印为二进制格式,大端小端都适用,以人类习惯打印，抛开底层大小端，打出方便转化为十进制的数字
//如果为小端，则先打印高地址，如果为大端，则先打印低地址
void vAnyToBites_IgnoreBigLittle_HumanRead(unsigned char *start, int len) {
  printf("按照实际表示的数的方式二进制打印:\n");
  if (checkBiglittle()) //小端
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

//可以将任何数据类型打印为二进制格式,大端小端都有用
//不区分大小端，按内存从低到高打印出来
void vAnyToBites_FromLowAddrToHigh(unsigned char *start, int len) {
  printf("按照地从低地址到高地址的二进制打印:\n");
  for (int i = 0; i < len; ++i) {
    for (int j = 7; j >= 0; j--) {
      printf("%d", (start[i] >> j) & 0x01);
    }
    printf(" ");
  }
  printf("\n");
}

//输出p指向的数据(可以为任何类型)的从地址低到高的每个字节的地址和每个字节的16进制表示
void dump(void *p, int L) {
  printf("十六进制打印\n");
  unsigned char *s = (unsigned char *)p;
  int i;
  for (int i = 0; i < L; ++i, s++) {
    printf("地址%p:0x%x\n", s, *s);
  }

  //以想表示的数的形式打印十六进制，如想表示0x123456,则打印12 34
  // 56而自动考虑大小端问题
  printf("以实际表示的数的字节序列的十六进制打印:\n0x: ");
  if (checkBiglittle()) { //小端
    s--;
    for (int i = 0; i < L; ++i, s--) {
      printf("%x ", *s);
    }
    printf("\n");

  } else {
    s = (unsigned char *)p;
    for (int i = 0; i < L; ++i, s++) {
      printf("%x ", *s);
    }
    printf("\n");
  }

  //按照内存地址从低到高的字节序列打印，自动考虑大小端问题
  printf("按照内存地址从低到高的字节序列十六进制打印:\n0x: ");
  s = (unsigned char *)p;
  for (int i = 0; i < L; ++i, s++) {
    printf("%x ", *s);
  }
  printf("\n");
}

/*
 * test1-5出自：【问答21】C语言：位域和字节序
 *https://mp.weixin.qq.com/s?__biz=MzUxMjEyNDgyNw==&mid=2247493481&idx=1&sn=fc7af21e8047fd76e0e23809ea12da0b&chksm=f96b959dce1c1c8bc704fc673ec78c7d33f00fd06f53539860e8f3e28197e153aeafc597d30b&mpshare=1&scene=24&srcid=1120cHL13QwAU0HmFl26eLTX&sharer_sharetime=1637384247264&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd
 * */

void test1() {
  //每个字节分别赋值
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
  //这里是对每个内存地址赋值，而数组的内存地址一定是从低到高
  s[0] = 0x81;
  s[1] = 0x83;
  printf("sizeof(strct iphdr) = %d\n", sizeof(t));
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  //打印出位域成员的值
  printf("fin:%d rsv：%d opcode：%d mask：%d paylod：%d \n\n", t.fin, t.rsv,
         t.opcode, t.mask, t.payload);

  t.fin = 1;
  t.rsv = 0;
  t.opcode = 8;
  t.mask = 1;
  t.payload = 65;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n", s[0]);
  printf("s[1] = 0x%x\n", s[1]);

  return 0;
}

void test2() {
  //整个结构体一次性赋值
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

  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("fin:%d rsv：%d opcode：%d mask：%d paylod：%d \n", t.fin, t.rsv,
         t.opcode, t.mask, t.payload);
  t.fin = 1;
  t.rsv = 1;
  t.opcode = 8;
  t.mask = 1;
  t.payload = 64;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));

  unsigned char *s1 = (unsigned char *)s;

  printf("s[0] = 0x%x\n", s1[0]);
  printf("s[1] = 0x%x\n", s1[1]);
}

void test3() {
  //当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局。
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
  printf("当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局\ns"
         "izeof(iphdr) = %d\n\n\n",
         sizeof(struct iphdr));
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 0;
  t.opcode = 0xf;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0xc;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0x0;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0]= %x\n\n", s[0]);
}

void test3_r() {
  //当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局。
  printf("//****************** [%s] ***********************//\n", __FUNCTION__);
  struct iphdr {
    unsigned char fin : 1;
    unsigned char : 3; //该3位不能使用,与unsigned char
                       //:0截然不同,无名位域的宽度为3bit
    // unsigned char :0; //空域，宽度为8bit
    unsigned char opcode : 4;
    /* unsigned char a; */
    /* unsigned char b; */
  } t;
  unsigned char *s;

  memset(&t, 0, 1);

  s = (unsigned short *)&t;

  t.fin = 1;
  t.opcode = 0xf;
  printf("当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局\ns"
         "izeof(iphdr) = %d\n\n\n",
         sizeof(struct iphdr));
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 0;
  t.opcode = 0xf;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0xc;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0x0;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0]= %x\n\n", s[0]);
}

void test3_r1() {
  //当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局。
  printf("//****************** %s ***********************//\n", __FUNCTION__);
  struct iphdr {
    unsigned char fin : 1;
    // unsigned char : 3; //该3位不能使用,与unsigned char
    //:0截然不同,无名位域的宽度为3bit
    unsigned char : 0; //空域，宽度为8bit
    unsigned char opcode : 4;
    /* unsigned char a; */
    /* unsigned char b; */
  } t;
  unsigned char *s;

  memset(&t, 0, 1);

  s = (unsigned short *)&t;

  t.fin = 1;
  t.opcode = 0xf;
  printf("当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局\ns"
         "izeof(iphdr) = %d\n\n\n",
         sizeof(struct iphdr));
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 0;
  t.opcode = 0xf;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0xc;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = %x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0x0;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0]= %x\n\n", s[0]);
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

  printf("当位域成员大小加一起不够一个整字节的时候，验证各成员在内存中的布局\ns"
         "izeof(iphdr2) = %d\n\n\n",
         sizeof(struct iphdr2));
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);

  t.fin = 0;
  t.opcode = 0xf;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);

  t.fin = 2;
  t.opcode = 0xc;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);

  t.fin = 3;
  t.opcode = 0xd;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0x0;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0x7f;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);

  t.fin = 1;
  t.opcode = 0x20;
  vAnyToBites_IgnoreBigLittle_HumanRead(s, sizeof(t));
  vAnyToBites_FromLowAddrToHigh(s, sizeof(t));
  dump(s, sizeof(t));
  printf("s[0] = 0x%x\n\n", s[0]);
}

void vtest5() {
  //测试一个结构体的成员在内存地址的分布
  printf("//*************** test5 *************************//\n");
  printf("测试一个结构体的成员在内存地址的分布\n");
  struct iphdr {
    unsigned char a;
    unsigned char b;
    unsigned char c;
  } S;

  S.a = 12;
  S.b = 13;
  S.c = 14;

  unsigned char *p = (unsigned char *)&S;

  vAnyToBites_FromLowAddrToHigh(p, sizeof(S));
  dump(p, sizeof(S));
}

void vtest6() {
  //测试一个结构体的成员在内存地址的分布
  printf("//*************** [%s] *************************//\n", __FUNCTION__);
  printf("测试一个结构体的成员在内存地址的分布\n");
  struct iphdr {
    unsigned short a;
    unsigned short b;
    unsigned short c;
  } S;

  S.a = 0x1200;
  S.b = 0x1f2d;
  S.c = 0xff4d;
  printf("sizeof(S) = %d\n", sizeof(S));

  unsigned char *p = (unsigned char *)&S;

  vAnyToBites_FromLowAddrToHigh(p, sizeof(S));
  dump(p, sizeof(S));
}

void vtest7() {
  //测试一个结构体的成员在内存地址的分布
  printf("//*************** [%s] *************************//\n", __FUNCTION__);
  printf("测试一个结构体的成员在内存地址的分布\n");
  struct iphdr {
    unsigned short a : 3;
    unsigned short b : 4;
    unsigned short : 5;
    unsigned short c : 3;
    unsigned short d : 5;
  } S;

  S.a = 1; // 1
  S.b = 3; // 11
  S.c = 4; // 101
  S.d = 7; // 111
  printf("sizeof(S) = %d\n", sizeof(S));

  unsigned char *p = (unsigned char *)&S;

  vAnyToBites_FromLowAddrToHigh(p, sizeof(S));
  dump(p, sizeof(S));
}

void vtest8() {
  //测试一个结构体的成员在内存地址的分布
  printf("//*************** [%s] *************************//\n", __FUNCTION__);
  printf("测试一个结构体的成员在内存地址的分布\n");
  struct Foo2 {
    unsigned short a : 1;
    unsigned short b : 3;
    unsigned short c : 4;
    unsigned short d : 4;
    unsigned short e : 4;
  };
  union {
    struct Foo2 s;
    unsigned short s_data;
  } S;

  S.s.a = 1; // 100
  S.s.b = 3; // 111
  S.s.c = 5; // 101
  S.s.d = 7; // 1000
  S.s.e = 15;
  printf("sizeof(S) = %d\n", sizeof(S));

  unsigned char *p = (unsigned char *)&(S.s);
  printf("val is 0x%x.\n", S.s_data);
  vAnyToBites_FromLowAddrToHigh(p, sizeof(S.s));
  dump(p, sizeof(S.s));
}

void vbit_order() {
  printf("//*************** [%s] *************************//\n", __FUNCTION__);
  struct bit_order {
    unsigned char a : 2, b : 3, c : 3;
  };

  unsigned char ch = 0x79;
  struct bit_order *ptr = (struct bit_order *)&ch;

  printf("bit_order->a : %u\n", ptr->a);
  printf("bit_order->b : %u\n", ptr->b);
  printf("bit_order->c : %u\n", ptr->c);

  unsigned char *p = (unsigned char *)ptr;
  vAnyToBites_FromLowAddrToHigh(p, sizeof(struct bit_order));
  dump(p, sizeof(struct bit_order));
}

/*
  原则一：结构体中元素是按照定义顺序一个一个放到内存中去的，但并不是紧密排列的。从结构体存储的首地址开始，每一个元素放置到内存中时，它都会认为内存是以它自己的大小来划分的，因此元素放置的位置一定会在自己宽度的整数倍上开始（以结构体变量首地址为0计算）。
  原则二：在经过第一原则分析后，检查计算出的存储单元是否为所有元素中最宽的元素的长度的整数倍，是，则结束；若不是，则补齐为它的整数倍。
  原则三：由于位域本质上是一种特殊的结构体成员，因此一般结构体成员的引用方法同样适用于位域成员。不过，需要特别注意的是，位域成员存储是以二进制位作为单位的，而内存的最小寻址单元是字节，所以不能直接引用位域成员的地址。

无论是大端或小端模式，位域的存储都是由内存低地址向高地址分配，即从低地址字节的低位bit开始向高地址字节的高位bit分配空间；
位域成员在已分配的内存区域内，按照机器定义的比特序对数据的各个bit位进行排列。即在小端模式中，位域成员的最低有效位存放在内存低bit位，最高有效位存放在内存高bit位；大端模式则相反。

从test1-6可以看出，当结构体的成员的字节数sizeof()值都>=1时，结构体的每个成员从上往下在内存中依次从低地址往高地址的位置存的，这与系统的大小端无关，
但是每个成员在相应的字段里存储方式是以字节为单位，且与系统的大小端有关的，

*/

void hex() {
  printf("//******************* hex ********************//\n");
  unsigned char a = 14;
  printf("a = 0x%x\n", a);

  a = 25; // 00011001
  printf("a = 0x%x\n", a);

  printf("sizeof(unsigned short) = %d\n", sizeof(unsigned short));
}

int main(int argc, char *argv[]) {

  test1();
  test2();
  test3();
  test3_r();
  test3_r1();
  test4();
  vtest5();
  vtest6();
  vtest7();
  vtest8();
  vbit_order();

  hex();
  checkBiglittle();
  checkBiglittle1();
  checkBiglittle2();
  checkBiglittle3();
  checkBiglittle4();
}
