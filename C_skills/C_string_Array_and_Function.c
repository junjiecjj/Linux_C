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

#define SLEN 40
#define LIM 5

void test1() {
  char heart[] = "I love Tillie!";
  char *head = "I love Tillie!";

  //首先，两者都可以使用数组表示法：

  for (int i = 0; i < 6; i++) {
    putchar(heart[i]);
  }
  putchar('\n');

  for (int i = 0; i < 6; i++) {
    putchar(head[i]);
  }
  putchar('\n');

  // 其次，两者都能进行指针加法操作：

  for (int i = 0; i < 6; i++) {
    putchar(*(heart + i));
  }
  putchar('\n');

  for (int i = 0; i < 6; i++) {
    putchar(*(head + i));
  }
  putchar('\n');

  //但是，只有指针表示法可以进行递增操作：
  while (*(head) != '\0') {
    putchar(*(head++));
  }

  //总之，如果打算修改字符串，就不要用指针指向字符串字面量。
}

/*
从某些方面来看，mytalents和yourtalents非常相似。两者都代表5个字符串。使用一个下标时都分别表示一个字符串，
如mytalents[0]和yourtalents[0]；使用两个下标时都分别表示一个字符，例如mytalents[1][2]表示mytalents数组中第2个指针所指向的字符串的第3个字符'l'，
yourtalents[1][2]表示youttalentes数组的第2个字符串的第3个字符'e'。而且，两者的初始化方式也相同。但是，它们也有区别。mytalents数组是一个内含5个指针的数组
，在我们的系统中共占用40字节。而yourtalents是一个内含5个数组的数组，每个数组内含40个char类型的值，共占用200字节。
所以，虽然mytalents[0]和yourtalents[0]都分别表示一个字符串，但mytalents和yourtalents的类型并不相同。mytalents中的指针指向初始化时所用的字符串字面量的位置，
这些字符串字面量被存储在静态内存中；而yourtalents中的数组则存储着字符串字面量的副本，所以每个字符串都被存储了两次。
此外，为字从某些方面来看，mytalents和yourtalents非常相似。两者都代表5个字符串。使用一个下标时都分别表示一个字符串，如mytalents[0]和yourtalents[0]；
使用两个下标时都分别表示一个字符，例如mytalents[1][2]表示mytalents数组中第2个指针所指向的字符串的第3个字符'l'，yourtalents[1][2]表示youttalentes数组的第2个字符串的第3个字符'e'。
而且，两者的初始化方式也相同。但是，它们也有区别。mytalents数组是一个内含5个指针的数组，在我们的系统中共占用40字节。而yourtalents是一个内含5个数组的数组，
每个数组内含40个char类型的值，共占用200字节。所以，虽然mytalents[0]和yourtalents[0]都分别表示一个字符串，但mytalents和yourtalents的类型并不相同。
mytalents中的指针指向初始化时所用的字符串字面量的位置，这些字符串字面量被存储在静态内存中；而yourtalents中的数组则存储着字符串字面量的副本，
所以每个字符串都被存储了两次。此外，为字符串数组分配内存的使用率较低。yourtalents中的每个元素的大小必须相同，而且必须是能存储最长字符串的大小。
我们可以把yourtalents想象成矩形二维数组，每行的长度都是40字节；把mytalents想象成不规则的数组，每行的长度不同。
图11.2演示了这两种数组的情况（实际上，mytalents数组的指针元素所指向的字符串不必存储在连续的内存中，图中所示只是为了强调两种数组的不同）。
*/
void test2() {
  const char *mytalents[LIM] = {
      "Adding numbers swiftly", "Multiplying accurately", "Stashing data",
      "Following instructions to the letter", "Understanding the C language"};
  char yourtalents[LIM][SLEN] = {"Walking in a straight line", "Sleeping",
                                 "Watching television", "Mailing letters",
                                 "Reading email"};
  int i;

  puts("Let's compare talents.");
  printf("%-36s  %-25s\n", "My Talents", "Your Talents");
  for (i = 0; i < LIM; i++)
    printf("%-36s  %-25s\n", mytalents[i], yourtalents[i]);
  printf("\nsizeof mytalents: %zd, sizeof yourtalents: %zd\n",
         sizeof(mytalents), sizeof(yourtalents));
}

/*
 我们来仔细分析最后两个printf()的输出。首先第1项，mesg和copy都以字符串形式输出（%s转换说明）。这里没问题，两个字符串都是"Don't
 be a fool!"。
 接着第2项，打印两个指针的地址。如上输出所示，指针mesg和copy分别存储在地址为0x0012ff48和0x0012ff44的内存中。注意最后一项，显示两个指针的值。
 所谓指针的值就是它存储的地址。mesg和copy的值都是0x0040a000，说明它们都指向的同一个位置。因此，程序并未拷贝字符串。语句copy
 = mesg;把mesg的值赋给copy，
 即让copy也指向mesg指向的字符串。为什么要这样做？为何不拷贝整个字符串？假设数组有50个元素，考虑一下哪种方法更效率：拷贝一个地址还是拷贝整个数组？
 通常，程序要完成某项操作只需要知道地址就可以了。如果确实需要拷贝整个数组，可以使用strcpy()或strncpy()函数，本章稍后介绍这两个函数。
 */

void test3() {
  const char *mesg = "Don't be a fool!";
  const char *copy;

  copy = mesg;
  printf("%s\n", copy);
  printf("mesg = %s; &mesg = %p; value = %p\n", mesg, &mesg, mesg);
  printf("copy = %s; &copy = %p; value = %p\n", copy, &copy, copy);
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
}
