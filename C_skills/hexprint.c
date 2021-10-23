/*************************************************************************
>> File Name: hexprint.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年10月23日 星期六 18时00分31秒

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

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++)
    printf(" %.2x", start[i]); // line:data:show_bytes_printf
  printf("\n");
}

void show_int(int x) {
  show_bytes((byte_pointer)&x, sizeof(int)); // line:data:show_bytes_amp1
}

void show_float(float x) {
  show_bytes((byte_pointer)&x, sizeof(float)); // line:data:show_bytes_amp2
}

void show_double(double x) {
  show_bytes((byte_pointer)&x, sizeof(double)); // line:data:show_bytes_amp2
}

void show_pointer(void *x) {
  show_bytes((byte_pointer)&x, sizeof(void *)); // line:data:show_bytes_amp3
}

/* $begin test-show-bytes */
void test_show_bytes(int val) {
  int ival = val;
  float fval = (float)ival;
  int *pval = &ival;
  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}
/* $end test-show-bytes */

void simple_show_a() {
  /* $begin simple-show-a */
  int val = 0x87654321;
  byte_pointer valp = (byte_pointer)&val;
  show_bytes(valp, 1); /* A. */
  show_bytes(valp, 2); /* B. */
  show_bytes(valp, 3); /* C. */
  /* $end simple-show-a */
}

void simple_show_b() {
  /* $begin simple-show-b */
  int val = 0x12345678;
  byte_pointer valp = (byte_pointer)&val;
  show_bytes(valp, 1); /* A. */
  show_bytes(valp, 2); /* B. */
  show_bytes(valp, 3); /* C. */
  /* $end simple-show-b */
}

void float_eg() {
  int x = 3490593;
  float f = (float)x;
  printf("For x = %d\n", x);
  show_int(x);
  show_float(f);

  x = 3510593;
  f = (float)x;
  printf("For x = %d\n", x);
  show_int(x);
  show_float(f);
}

void string_ueg() {
  /* $begin show-ustring */
  const char *s = "ABCDEF";
  show_bytes((byte_pointer)s, strlen(s));
  /* $end show-ustring */
}

void string_leg() {
  /* $begin show-lstring */
  const char *s = "abcdef";
  show_bytes((byte_pointer)s, strlen(s));
  /* $end show-lstring */
}

void show_twocomp() {
  /* $begin show-twocomp */
  short x = 12345;
  short mx = -x;

  show_bytes((byte_pointer)&x, sizeof(short));
  show_bytes((byte_pointer)&mx, sizeof(short));
  /* $end show-twocomp */
}

int main(int argc, char *argv[]) {
  int a = 12345;
  float b = 12.12;
  double c = 123.123;
  const char *S = "ABCDEF";
  const char *S1 = "abcdef";

  printf("sizeof(int) = %zd\n", sizeof(int));
  printf("sizeof(float) = %zd\n", sizeof(float));
  printf("sizeof(double) = %zd\n", sizeof(double));
  printf("sizeof(void *) = %zd\n", sizeof(void *));

  show_int(a);
  show_bytes(&a, 4);
  show_bytes((byte_pointer)&a, 4);
  show_float(a);
  show_double(a);
  show_pointer((void *)a);
  show_bytes((byte_pointer)S, strlen(S) + 1);
  show_bytes((byte_pointer)S1, strlen(S1) + 1);

  int val = 12345;

  if (argc > 1) {
    if (argc > 1) {
      val = strtol(argv[1], NULL, 0);
    }
    printf("calling test_show_bytes\n");
    test_show_bytes(val);
  } else {
    printf("calling show_twocomp\n");
    show_twocomp();
    printf("Calling simple_show_a\n");
    simple_show_a();
    printf("Calling simple_show_b\n");
    simple_show_b();
    printf("Calling float_eg\n");
    float_eg();
    printf("Calling string_ueg\n");
    string_ueg();
    printf("Calling string_leg\n");
    string_leg();
  }

  return 0;
}
