/*************************************************************************
  >> File Name: hello.c
  >> Author: 陈俊杰
  >> Mail: 2716705056qq.com

  >> Created Time: 2021年04月29日 星期四 15时21分51秒

  >> 此程序的功能是：
 ************************************************************************/

#include "Net.h"
#include "DOA.h"
//#include "Globle.h"
#include "Struct.h"
#include "Time.h"

extern int A;

void hello(void) {
  // extern int A;
  A += 100;
  int b = 1011;

  printf("function: [%s], File Path: [%s], Line: [%d], Time: [%s] \n", __func__,
         __FILE__, __LINE__, GetTimeOfNow());
  printf("A = %d, b = %d\n", A, b);
}

void showstr(STR2 *p) {
  printf("a = %d, b = %lf, c = %f, d = %hhu, \n", p->a, p->b, p->c, p->d);
}
