/*************************************************************************
>> File Name: C_error.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年10月21日 星期四 23时09分15秒

>> 此程序的功能是：
https://mp.weixin.qq.com/s?__biz=MjM5NjQ4MjYwMQ==&mid=2664642491&idx=3&sn=d8d10e47c29055a8a166f4392bce4f28&chksm=bdcf0cfd8ab885ebaff8e421ac70488f6ae394617fcafb31f84f3717519d385d709c5f1269f0&mpshare=1&scene=24&srcid=1018h7iVBQMmjSPkY73XdKuH&sharer_sharetime=1634560983039&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8&exportkey=AUb%2BIAWbM3ckjlceNV3lCag%3D&pass_ticket=vP4grk57%2Fl0ry1RMv7uV4%2Fk9MicgSF7GcXaOXJOjOZeX5HoC6K0NDfiLnKxjiuWc&wx_header=0#rd

C 语言编程中的 5 个常见错误及对应解决方案 | Linux 中国
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

/*
程序启动时，系统会为其分配一块内存以供存储数据。这意味着程序启动时，变量将获得内存中的一个随机值。

有些编程环境会在程序启动时特意将内存“清零”，因此每个变量都得以有初始的零值。程序中的变量都以零值作为初始值，听上去是很不错的。但是在
C 编程规范中，系统并不会初始化变量。

看一下这个使用了若干变量和两个数组的示例程序：


这个程序不会初始化变量，所以变量以系统内存中的随机值作为初始值。在我的 Linux
系统上编译和运行这个程序，会看到一些变量恰巧有“零”值，但其他变量并没有：

很幸运，i 和 j 变量是从零值开始的，但 k 的起始值为 32766。在 numbers
数组中，大多数元素也恰好从零值开始，只有第三个元素的初始值为 4199024。

在不同的系统上编译相同的程序，可以进一步显示未初始化变量的危险性。不要误以为“全世界都在运行
Linux”，你的程序很可能某天在其他平台上运行。例如，下面是在 FreeDOS
上运行相同程序的结果：

永远都要记得初始化程序的变量。如果你想让变量将以零值作为初始值，请额外添加代码将零分配给该变量。预先编好这些额外的代码，这会有助于减少日后让人头疼的调试过程。

*/

int error1() {
  int i, j, k;
  int numbers[5];
  int *array;
  puts("These variables are not initialized:");
  printf("  i = %d\n", i);
  printf("  j = %d\n", j);
  printf("  k = %d\n", k);
  puts("This array is not initialized:");
  for (i = 0; i < 5; i++) {
    printf("  numbers[%d] = %d\n", i, numbers[i]);
  }
  puts("malloc an array ...");
  array = malloc(sizeof(int) * 5);
  if (array) {
    puts("This malloc'ed array is not initialized:");
    for (i = 0; i < 5; i++) {
      printf("  array[%d] = %d\n", i, array[i]);
    }
    free(array);
  }
  /* done */
  puts("Ok");
  return 0;
}

/*
 C 语言中，数组索引从零开始。这意味着对于长度为 10 的数组，索引是从 0 到
9；长度为 1000 的数组，索引则是从 0 到 999。

程序员有时会忘记这一点，他们从索引 1 开始引用数组，产生了“大小差一”(off by
one)错误。在长度为 5 的数组中，程序员在索引“5”处使用的值，实际上并不是数组的第 5
个元素。相反，它是内存中的一些其他值，根本与此数组无关。

这是一个数组越界的示例程序。该程序使用了一个只含有 5
个元素的数组，但却引用了该范围之外的数组元素：
 * */
int error2() {
  int i;
  int numbers[5];
  int *array;
  /* test 1 */
  puts("This array has five elements (0 to 4)");
  /* initalize the array */
  for (i = 0; i < 5; i++) {
    numbers[i] = i;
  }
  /* oops, this goes beyond the array bounds: */
  for (i = 0; i < 10; i++) {
    printf("  numbers[%d] = %d\n", i, numbers[i]);
  }
  /* test 2 */
  puts("malloc an array ...");
  array = malloc(sizeof(int) * 5);
  if (array) {
    puts("This malloc'ed array also has five elements (0 to 4)");
    /* initalize the array */
    for (i = 0; i < 5; i++) {
      array[i] = i;
    }
    /* oops, this goes beyond the array bounds: */
    for (i = 0; i < 10; i++) {
      printf("  array[%d] = %d\n", i, array[i]);
    }
    free(array);
  }
  /* done */
  puts("Ok");
  return 0;
}

/*

字符串只是特定类型的数组。在 C 语言中，字符串是一个由 char
类型值组成的数组，其中用一个零字符表示字符串的结尾。

因此，与数组一样，要注意避免超出字符串的范围。有时也称之为 字符串溢出。

使用 gets 函数读取数据是一种很容易发生字符串溢出的行为方式。gets
函数非常危险，因为它不知道在一个字符串中可以存储多少数据，只会机械地从用户那里读取数据。如果用户输入像
foo
这样的短字符串，不会发生意外；但是当用户输入的值超过字符串长度时，后果可能是灾难性的。

下面是一个使用 gets
函数读取城市名称的示例程序。在这个程序中，我还添加了一些未使用的变量，来展示字符串溢出对其他数据的影响：
 */
int error3() {
  char name[10]; /* Such as "Chicago" */
  int var1 = 1, var2 = 2;
  /* show initial values */
  printf("var1 = %d; var2 = %d\n", var1, var2);
  /* this is bad .. please don't use gets */
  puts("Where do you live?");
  gets(name);
  /* show ending values */
  printf("<%s> is length %d\n", name, strlen(name));
  printf("var1 = %d; var2 = %d\n", var1, var2);
  /* done */
  puts("Ok");
  return 0;
}

/*
“分配的内存要手动释放”是良好的 C 语言编程原则之一。程序可以使用 malloc
函数为数组和字符串分配内存，该函数会开辟一块内存，并返回一个指向内存中起始地址的指针。之后，程序可以使用
free 函数释放内存，该函数会使用指针将内存标记为未使用。

但是，你应该只使用一次 free 函数。第二次调用 free
会导致意外的后果，可能会毁掉你的程序。下面是一个针对此点的简短示例程序。程序分配了内存，然后立即释放了它。但为了模仿一个健忘但有条理的程序员，我在程序结束时又一次释放了内存，导致两次释放了相同的内存：
*/

int error4() {
  int *array;
  puts("malloc an array ...");
  array = malloc(sizeof(int) * 5);
  if (array) {
    puts("malloc succeeded");
    puts("Free the array...");
    free(array);
  }
  puts("Free the array...");
  free(array);
  puts("Ok");
}

/*
文件是一种便捷的数据存储方式。例如，你可以将程序的配置数据存储在 config.dat
文件中。Bash shell 会从用户家目录中的 .bash_profile 读取初始化脚本。GNU Emacs
编辑器会寻找文件 .emacs 以从中确定起始值。而 Zoom 会议客户端使用 zoomus.conf
文件读取其程序配置。

所以，从文件中读取数据的能力几乎对所有程序都很重要。但是假如要读取的文件不存在，会发生什么呢？

在 C 语言中读取文件，首先要用 fopen
函数打开文件，该函数会返回指向文件的流指针。你可以结合其他函数，使用这个指针来读取数据，例如
fgetc 会逐个字符地读取文件。

如果要读取的文件不存在或程序没有读取权限，fopen 函数会返回 NULL
作为文件指针，这表示文件指针无效。但是这里有一个示例程序，它机械地直接去读取文件，不检查
fopen 是否返回了 NULL：

*/
int error5() {
  FILE *pfile;
  int ch;
  puts("Open the FILE.TXT file ...");
  pfile = fopen("FILE.TXT", "r");
  /* you should check if the file pointer is valid, but we skipped that */
  puts("Now display the contents of FILE.TXT ...");
  while ((ch = fgetc(pfile)) != EOF) {
    printf("<%c>", ch);
  }
  fclose(pfile);
  /* done */
  puts("Ok");
  return 0;
}

int main(int argc, char *argv[]) {

  printf("*********************** 1 *******************************\n");
  error1();

  printf("*********************** 1 *******************************\n");
  error2();

  printf("*********************** 1 *******************************\n");
  error3();

  printf("*********************** 1 *******************************\n");
  error4();

  printf("*********************** 1 *******************************\n");
  error5();
}
