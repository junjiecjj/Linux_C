/*************************************************************************
>> File Name: C_BitField.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年04月29日 星期四 16时01分17秒

>> 此程序的功能是：
Linux字节对齐的那些事
原创 土豆居士 一口Linux 8月6日
https://mp.weixin.qq.com/s?__biz=MzUxMjEyNDgyNw==&mid=2247496601&idx=1&sn=bbaf73bfed6641c2d0681b2ad4c500c0&chksm=f96b816dce1c087b1864c8a4061ddc1c687919b2f835d43ab1cbb20fbee24c0b91bef0bb10d6&mpshare=1&scene=24&srcid=1120gEq9JEnkS1D4gJGwzbcg&sharer_sharetime=1637383696588&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd

编译器给我们进行了内存对齐，各成员变量存放的起始地址相对于结构的起始地址的偏移量必须为该变量类型所占用的字节数的倍数,
且结构的大小为该结构中占用最大空间的类型所占用的字节数的倍数。

对于偏移量：变量type
n起始地址相对于结构体起始地址的偏移量必须为sizeof(type(n))的倍数结构体大小：必须为成员最大类型字节的倍数

char: 偏移量必须为sizeof(char) 即1的倍数
int: 偏移量必须为sizeof(int) 即4的倍数
float: 偏移量必须为sizeof(float) 即4的倍数
double: 偏移量必须为sizeof(double) 即8的倍数


#pragma pack(n)
用来设定变量以n字节对齐方式。n字节对齐就是说变量存放的起始地址的偏移量有两种情况：

如果n大于等于该变量所占用的字节数，那么偏移量必须满足默认的对齐方式
如果n小于该变量的类型所占用的字节数，那么偏移量为n的倍数，不用满足默认的对齐方式。
结构的总大小也有一个约束条件，如果n大于等于所有成员变量类型所占用的字节数，那么结构的总大小必须为占用空间最大的变量占用的空间数的倍数；否则必须是n的倍数。

************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

void test1() {

  struct A {
    int a;
    char b;
    short c;
  };

  struct B {
    char b;
    int a;
    short c;
  };
  struct AA {
    // int a;
    char b;
    short c;
  };

  struct BB {
    char b;
    // int a;
    short c;
  };
#pragma pack(2) /*指定按2字节对齐*/
  struct C {
    char b;
    int a;
    short c;
  };
#pragma pack() /*取消指定对齐，恢复缺省对齐*/

#pragma pack(1) /*指定按1字节对齐*/
  struct D {
    char b;
    int a;
    short c;
  };
#pragma pack() /*取消指定对齐，恢复缺省对齐*/

  struct yikou_s1 {
    double d;
    char c;
    int i;
  } yikou_t1;

  struct yikou_s2 {
    char c;
    double d;
    int i;
  } yikou_t2;

#pragma pack(4)

  struct yikou_s3 {
    char c;
    double d;
    int i;
  } yikou_t3;
#pragma pack() /*取消指定对齐，恢复缺省对齐*/

#pragma pack(8)

  struct yikou_s4 {
    char c;
    double d;
    int i;
  } yikou_t4;
#pragma pack() /*取消指定对齐，恢复缺省对齐*/

  int s1 = sizeof(struct A);
  int s2 = sizeof(struct AA);
  int s3 = sizeof(struct B);
  int s4 = sizeof(struct BB);
  int s5 = sizeof(struct C);
  int s6 = sizeof(struct D);
  printf("sizeof(struct A) = %d\n", sizeof(struct A));
  printf("sizeof(struct AA) %d\n", sizeof(struct AA));
  printf("sizeof(struct B)%d\n", sizeof(struct B));
  printf("sizeof(struct BB)%d\n", sizeof(struct BB));
  printf("sizeof(struct C)%d\n", sizeof(struct C));
  printf("sizeof(struct D)%d\n", sizeof(struct D));
  printf("sizeof(struct yikou_s1)%d\n", sizeof(struct yikou_s1));
  printf("sizeof(struct yikou_s2)%d\n", sizeof(struct yikou_s2));
  printf("sizeof(struct yikou_s3)%d\n", sizeof(struct yikou_s3));
  printf("sizeof(struct yikou_s4)%d\n", sizeof(struct yikou_s4));
}

int main(int argc, char *argv[]) {
  printf("sizeof(char) = %ld\n", sizeof(char));
  printf("sizeof(int) = %ld\n", sizeof(int));
  printf("sizeof(float) = %ld\n", sizeof(float));
  printf("sizeof(long) = %ld\n", sizeof(long));
  printf("sizeof(long long) = %ld\n", sizeof(long long));
  printf("sizeof(double) = %ld\n", sizeof(double));

  test1();
  return 0;
}
