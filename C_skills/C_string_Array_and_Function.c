/*************************************************************************
>> File Name: C_stringFunction.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月05日 星期五 15时45分35秒

>> 此程序的功能是：
还可以使用指针表示法创建字符串。例如，程序清单11.1中使用了下面的声明：

const char &pt1 = "Something is pointing at me."
该声明和下面的声明几乎相同：
const char ar1[] = "Something is pointing at me."
以上两个声明表明，pt1和ar1都是该字符串的地址。在这两种情况下，带双引号的字符串本身决定了预留给字符串的存储空间。尽管如此，这两种形式并不完全相同。


ANSI C库有20多个用于处理字符串的函数，下面总结了一些常用的函数。

char *strcpy(char * restrict s1, const char * restrict s2);
该函数把s2指向的字符串（包括空字符）拷贝至s1指向的位置，返回值是s1。

char *strncpy(char * restrict s1, const char * restrict s2, size_t n);
该函数把s2指向的字符串拷贝至s1指向的位置，拷贝的字符数不超过n，其返回值是s1。该函数不会拷贝空字符后面的字符，如果源字符串的字符少于n个，目标字符串就以拷贝的空字符结尾；如果源字符串有n个或超过n个字符，就不拷贝空字符。

char *strcat(char * restrict s1, const char * restrict s2);
该函数把s2指向的字符串拷贝至s1指向的字符串末尾。s2字符串的第1个字符将覆盖s1字符串末尾的空字符。该函数返回s1。


char *strncat(char * restrict s1, const char * restrict s2, size_t n);
该函数把s2字符串中的n个字符拷贝至s1字符串末尾。s2字符串的第1个字符将覆盖s1字符串末尾的空字符。不会拷贝s2字符串中空字符和其后的字符，并在拷贝字符的末尾添加一个空字符。该函数返回s1。

int strcmp(const char * s1, const char * s2);
如果s1字符串在机器排序序列中位于s2字符串的后面，该函数返回一个正数；如果两个字符串相等，则返回0；如果s1字符串在机器排序序列中位于s2字符串的前面，则返回一个负数。

int strncmp(const char * s1, const char * s2, size_t n);
该函数的作用和strcmp()类似，不同的是，该函数在比较n个字符后或遇到第1个空字符时停止比较。

char *strchr(const char * s, int c);
如果s字符串中包含c字符，该函数返回指向s字符串首次出现的c字符的指针（末尾的空字符也是字符串的一部分，所以在查找范围内）；如果在字符串s中未找到c字符，该函数则返回空指针。

char *strpbrk(const char * s1, const char * s2);
如果s1字符中包含s2字符串中的任意字符，该函数返回指向s1字符串首位置的指针；如果在s1字符串中未找到任何s2字符串中的字符，则返回空字符。

char *strrchr(const char * s, char c);
该函数返回s字符串中c字符的最后一次出现的位置（末尾的空字符也是字符串的一部分，所以在查找范围内）。如果未找到c字符，则返回空指针。

char *strstr(const char * s1, const char * s2);
该函数返回指向s1字符串中s2字符串出现的首位置。如果在s1中没有找到s2，则返回空指针。

size_t strlen(const char * s);
该函数返回s字符串中的字符数，不包括末尾的空字符。

请注意，那些使用const关键字的函数原型表明，函数不会更改字符串。例如，下面的函数原型：
char *strcpy(char * restrict s1, const char * restrict s2);
表明不能更改s2指向的字符串，至少不能在strcpy()函数中更改。但是可以更改s1指向的字符串。这样做很合理，因为s1是目标字符串，要改变，而s2是源字符串，不能更改。

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

}
