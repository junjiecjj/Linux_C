/*************************************************************************
>> File Name: C_HeapStack.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月20日 星期六 16时49分25秒

>> 此程序的功能是：
一份通俗易懂的C语言内存总结
https://mp.weixin.qq.com/s?__biz=MzU5MzcyMjI4MA==&mid=2247483844&idx=2&sn=721c98390ec70fec0fe6c46823c928bc&chksm=fe0d6f03c97ae615311d38d3535d42de347b7dfc4ab8b846707a600450c0b82f784c0562ee75&mpshare=1&scene=1&srcid=1114yXyrYudPxmfDs4wAgQLd&sharer_sharetime=1636820459179&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd
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

void stack_test1(int a, int b, int c);
void stack_test1(int a, int b, int c) {
  printf("a = %d, &a = %#x \n", a, (unsigned int)&a);
  printf("b = %d, &b = %#x \n", b, (unsigned int)&b);
  printf("c = %d, &c = %#x \n", c, (unsigned int)&c);
}

void stack_test2(int a, int b, int c) { stack_test1(a, b, c); }

// malloc和free的简单应用
//在malloc分配完内存之后，可以用得到的指针值是否为NULL来判断内存是否分配成功。按照C语言内存分配规则，如果内存分配成功，返回的是内存的地址；如果内存分配不成功，将返回NULL（0x0），表示一个无效的地址。
void heap_test1(void) {
  int *pa;

  pa = (int *)malloc(sizeof(int));
  if (NULL != pa) {
    *pa = 0x1234;
    printf("pa = %#x, *pa = %x\n", (unsigned int)pa, *pa);
    free(pa);
  }

  return;
}

//后分配内存地址反而更小
// malloc在分配内存的时候，是从低地址至高地址方向。但是，先分配的内存地址不一定比后分配的内存地址小。下面的程序验证了这一点：
void heap_test2(void) {
  void *pa;
  void *pb;
  void *pc;
  void *pd;
  pa = (int *)malloc(1024);
  printf("pa = %#x \n", (unsigned int)pa);
  pb = (int *)malloc(1024);
  printf("pb = %#x \n", (unsigned int)pb);
  pc = (int *)malloc(1024);
  printf("pc = %#x \n", (unsigned int)pc);
  free(pb);
  pd = (int *)malloc(1024);
  printf("pd = %#x \n", (unsigned int)pd);

  free(pa);
  free(pc);
  free(pd);

  return;
}

// calloc()和malloc()很类似，主要区别是calloc()可以将分配好的内存区域的初始值全部设置为0，以下程序验证了这一点：
// calloc和malloc的主要区别,除此之外，calloc()和malloc()另外一个不同之处在于参数的个数，malloc只有一个参数，即要分配的内存字节数；calloc有两个参数，第一个是分配单元的大小，第二个是要分配的数目。从本质上，calloc使用两个参数和malloc使用一个并没有区别。
void heap_test3(void) {
  unsigned int *pa;
  int i;

  pa = (unsigned int *)calloc(sizeof(unsigned int), 5);
  if (NULL != pa) {
    printf("<< colloc pa = %#x >>\n", (unsigned int)pa);
    for (i = 0; i < 5; i++) {
      printf("pa[%d] = %d \n", i, pa[i]);
    }
    free(pa);
  }

  return;
}

// realloc的应用。realloc函数具有两个参数，一个是指向内存的地址指针，另一个是重新分配内存的大小，而返回值是指向所分配内存的指针。基本应用代码如下：
// realloc的应用,除此之外，realloc还具有两种功能：一是当指针为NULL的时候，作为malloc使用，分配内存；二是当重新分配内存大小为0的时候，作为free使用，释放内存。
void heap_test4(void) {
  int *pa;
  int i;

  pa = (int *)malloc(sizeof(int) * 6);
  if (NULL != pa) {
    for (i = 0; i < 6; i++) {
      *(pa + i) = i;
    }
    for (i = 0; i < 6; i++) {
      printf("pa[%d] = %d \n", i, pa[i]);
    }
  }
  printf("relloc重新分配内存\n");
  pa = (int *)realloc(pa, sizeof(int) * 10);
  if (NULL != pa) {
    for (i = 0; i < 10; i++) {
      printf("pa[%d] = %d\n", i, pa[i]);
    }
    free(pa);
  }

  return;
}

/*

（6）再堆内存的管理上，容易出现以下几个问题：

开辟的内存没有释放，造成内存泄漏

内存泄漏的例子：

//内存泄漏例子
void heap_test6(void)
{
 char *pa;
 pa = (char*)malloc(sizeof(char)*20);
 // ......

 return;
}


在函数heap_test6中，使用malloc开辟了20个字节的内存区域，但是使用结束后该函数没有释放这块区域，也没有通过任何返回值或者参数的手段将这块内存区域的地址告诉其它函数。此时，这20个字节的内存不会被任何程序释放，因此再调用该函数的时候，就会导致内存泄漏。



野指针被使用或者释放

野指针是一个已经被释放的内存指针，它指向的位置已经被free或者realloc释放了，此时再使用该指针，就会导致程序的错误。野指针例子：

//野指针例子
void heap_test6(void)
{
 char *pa;
 pa = (char*)malloc(sizeof(char)*20);
 // ...... *
 free(pa);
 // ...... *
 printf("pa = %s \n",pa); //野指针被使用

 return;
}


在此程序中，调用free函数已经释放了pa指针，但后面还在继续使用pa，这就是一个错误的程序。

非法释放指针

1）	非法释放静态存储区的内存，示例如下：

//非法释放静态存储区的内存
void heap_test7(void)
{
 // ...... *
 // 错误释放只读数据区指针 *
 free(ro_data);
 // 错误释放已初始化读写数据区指针 *
 free(rw_data);
 // 错误释放未初始化读写数据区指针 *
 free(bss_data);

 // 错误释放代码区指针 *
 free(heap_test7);
 // ...... *
 return;
}


2）	非法释放栈上的内存，示例如下：

//非法释放栈上的内存
void heap_test8(void)
{
 char a[20];
 int b;

 // 错误释放栈上内存 *

 // ...... *
 free(a);
 free(&b);
 // ...... *
 return;
}


3）	非法释放堆上内存，示例如下：

//非法释放堆上的内存---1
void heap_test9(void)
{
 char *pa;
 // ...... *
 pa = (char*)malloc(sizeof(char)*20);
 free(pa);
 free(pa);  //错误释放堆内存
 // ...... *
 return;
}
第一次释放之后，该地址已经变成了未被分配的堆上的内存了，free函数不能释放未分配的堆内存。



//非法释放堆上的内存---2
void heap_test10(void)
{
 char *pa;
 char *pb;
 // ...... *
 pa = (char*)malloc(sizeof(char)*20);
 pb = pa++;
 free(pb);  //错误释放堆内存
 // ...... *
 return;
}
释放内存pb是非法的内存释放，由于这个指针并不是从malloc分配出来的，而是一个中间的指针值。

*/

int main(int argc, char *argv[]) {
  int a = 1, b = 2, c = 3;

  printf("a = %d, &a = %#x \n", a, (unsigned int)&a);
  printf("b = %d, &b = %#x \n", b, (unsigned int)&b);
  printf("c = %d, &c = %#x \n", c, (unsigned int)&c);
  /*
   *可见，变量的存储是从高地址往低地址的方向存储。
栈有一个重要的特性：先放入的数据最后才能取出，后放入的数据优先能取出，即先进后出（First
In Last
Out）原则。放入数据常被称为入栈或压栈（Push），取出数据被称为出栈或弹出（Pop）。在运用过程中，栈内存可能出现满栈和空栈两种情况，这是由处理器的体系结构决定的。

栈（Stack）可以存放函数参数、局部变量、局部数组等作用范围在函数内部的数据，它的用途就是完成函数的调用。
   * */

  int a = 1, b = 2, c = 3;
  int a1 = 4, b1 = 5, c1 = 6;

  printf("第一次调用stack_test1函数：\n");
  stack_test1(a, b, c);
  printf("第二次调用stack_test1函数：\n");
  stack_test1(a1, b1, c1);
  /*
   * 可见，两次调用中函数参数使用的栈内存是相同的，即第一次调用函数完成之后，栈指针将回到函数进入之前的位置。*/

  printf("直接调用stack_test1函数：\n");
  stack_test1(a, b, c);
  printf("通过stack_test2函数间接调用stack_test1函数：\n");
  stack_test2(a, b, c);
  /*
   可见，在程序中两次调用stack_test1函数，第一次是直接调用，第二次是通过stack_test2函数间接调用。从运行结果来看，通过stack_test2函数间接调用stack_test1函数的栈指针的值变小了，说明是由于栈中压入了更多的内容。
   */

  /*
  // 分配内存空间
  void *malloc(size_t size);
  // 释放内存空间
  void free(void *ptr);
  // 分配内存空间 *
  void *calloc(size_t num, size_t size);
  // 重新分配内存空间 *
  void *realloc(void *ptr, size_t size);
  * /

      return 0;
}
