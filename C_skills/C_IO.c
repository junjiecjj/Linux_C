/*************************************************************************
>> File Name: C_IO.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.05.10

该代码主要功能是：
C语言中常用的几个输入输出函数的用法:
****************************************************************************************
语言没有专门用于存储字符串的变量类型，字符串都被存储在char类型的数组中。数组由连续的存储单元组成，字符串中的字符被存储在相邻的存储单元中，每个单元存储一个字符（见图4.1）。
[Zing went the heart!\0]
图4.1 数组中的字符串
注意图4.1中数组末尾位置的字符\0。这是空字符（null
character），C语言用它标记字符串的结束。空字符不是数字0，它是非打印字符，其ASCII码值是（或等价于）0。C中的字符串一定以空字符结束，这意味着数组的容量必须至少比待存储字符串中的字符数多1。

***********************************  printf()
***************************************************** int printf(const char
*format, ...) 发送格式化输出到标准输出 stdout。
返回值：如果成功，则返回打印字符的总数，否则返回一个负数。


***********************************  sprintf()
***************************************************** int sprintf(char *str,
const char *format, ...) 发送格式化输出到 str 所指向的字符串。
返回值：如果成功，则返回写入的字符总数，不包括字符串追加在字符串末尾的空字符。如果失败，则返回一个负数。


*************************************  scanf()
****************************************************** int scanf(const char
*format, ...) 从标准输入 stdin 读取格式化输入。
返回值：如果成功，该函数返回成功匹配和赋值的个数(针对所有字符数，包括空格和不可见的换行符\n)。如果到达文件末尾或发生读错误，则返回
EOF。
scanf()函数使用空白（换行符、制表符和空格）把输入分成多个字段。在依次把转换说明和字段匹配时跳过空白。

假设scanf()根据一个%d转换说明读取一个整数。scanf()函数每次读取一个字符，跳过所有的空白字符，直至遇到第1个非空白字符才开始读取。因为要读取整数，所以scanf()希望发现一个数字字符或者一个符号（+或-）。如果找到一个数字或符号，它便保存该字符，并读取下一个字符。如果下一个字符是数字，它便保存该数字并读取下一个字符。scanf()不断地读取和保存字符，直至遇到非数字字符。如果遇到一个非数字字符，它便认为读到了整数的末尾。然后，scanf()把非数字字符放回输入。这意味着程序在下一次读取输入时，首先读到的是上一次读取丢弃的非数字字符。最后，scanf()计算已读取数字（可能还有符号）相应的数值，并将计算后的值放入指定的变量中。

如果使用字段宽度，scanf()会在字段结尾或第1个空白字符处停止读取（满足两个条件之一便停止）。

如果第1个非空白字符是A而不是数字，会发生什么情况？scanf()将停在那里，并把A放回输入中，不会把值赋给指定变量。程序在下一次读取输入时，首先读到的字符是A。如果程序只使用%d转换说明，scanf()就一直无法越过A读下一个字符。另外，如果使用带多个转换说明的scanf()，C规定在第1个出错处停止读取输入。

如果使用%s转换说明，scanf()会读取除空白以外的所有字符。scanf()跳过空白开始读取第1个非空白字符，并保存非空白字符直到再次遇到空白。这意味着scanf()根据%s转换说明读取一个单词，即不包含空白字符的字符串。如果使用字段宽度如%10s，scanf()在字段末尾或第1个空白字符处停止读取。无法利用字段宽度让只有一个%s的scanf()读取多个单词。最后要注意一点：当scanf()把字符串放进指定数组中时，它会在字符序列的末尾加上'\0'，让数组中的内容成为一个C字符串。

假设程序要求用getchar()处理字符输入，用scanf()处理数值输入，这两个函数都能很好地完成任务，但是不能把它们混用。因为getchar()读取每个字符，包括空格、制表符和换行符；而scanf()在读取数字时则会跳过空格、制表符和换行符。

scanf()函数允许把普通字符放在格式字符串中。除空格字符外的普通字符必须与输入字符串严格匹配。例如，假设在两个转换说明中添加一个逗号：
scanf("%d,%d", &n, &m);
scanf()函数将其解释成：用户将输入一个数字、一个逗号，然后再输入一个数字。也就是说，用户必须像下面这样进行输入两个整数：
88,121
由于格式字符串中，%d后面紧跟逗号，所以必须在输入88后再输入一个逗号。但是，由于scanf()会跳过整数前面的空白，所以下面两种输入方式都可以：
88, 121
和
88,
121
格式字符串中的空白意味着跳过下一个输入项前面的所有空白。例如，对于下面的语句：
scanf("%d ,%d", &n, &m);
以下的输入格式都没问题：
88,121 回车
88 ,121 回车
88 , 121 回车
请注意，“所有空白”的概念包括没有空格的特殊情况。注意，上述scanf在读取了88,121后，以及88,121之间的空格也会被忽略，即不会，回车依然被留在输入队列中。这个回车会被getchar()捕捉到，所以慎将scanf()和getchar()混合在一起使用。

许多程序使用getchar()逐字符读取输入。通常，系统使用行缓冲输入，即当用户按下Enter键后输入才被传送给程序。按下Enter键也传送了一个换行符，编程时要注意处理这个换行符。ANSI
C把缓冲输入作为标准。

混合使用getchar()和scanf()时，如果在调用getchar()之前，scanf()在输入行留下一个换行符，会导致一些问题。不过，意识到这个问题就可以在程序中妥善处理。


*****************************************   getchar()
**********************************************************************************************
int getchar(void) 从标准输入 stdin 获取一个字符（一个无符号字符）。这等同于 getc
带有 stdin 作为参数。 返回值：该函数以无符号 char 强制转换为 int
的形式返回读取的字符，如果到达文件末尾或发生读错误，则返回 EOF。


******************************************  putchar()
************************************************************************** int
putchar(int char) 把参数 char 指定的字符（一个无符号字符）写入到标准输出 stdout
中。 返回值：该函数以无符号 char 强制转换为 int
的形式返回写入的字符，如果发生错误则返回 EOF。


******************************************  gets()
*********************************************************************************************
char *gets(char *str) 从标准输入 stdin 读取一行，并把它存储在 str
所指向的字符串中。当读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。
返回值：如果成功，该函数返回
str。如果发生错误或者到达文件末尾时还未读取任何字符，则返回 空指针NULL。

gets()函数简单易用，它读取整行输入，直至遇到换行符，然后丢弃换行符，存储其余字符，并在这些字符的末尾添加一个空字符使其成为一个C字符串。它经常和puts()函数配对使用，该函数用于显示字符串，并在末尾添加换行符。


********************************************  puts()
*******************************************************************************************
int puts(const char *str) 把一个字符串写入到标准输出
stdout，直到空字符，但不包括空字符。换行符会被追加到输出中。
返回值：如果成功，该函数返回一个非负值，如果发生错误则返回 EOF。

因为puts()在显示字符串时会自动在其末尾添加一个换行符。puts()如何知道在何处停止？该函数在遇到空字符时就停止输出，所以必须确保有空字符。


********************************************  fgets()
*******************************************************************************************
 char *fgets(char *str, int n, FILE *stream) 从指定的流 stream
读取一行，并把它存储在 str 所指向的字符串内。当读取 (n-1)
个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。
返回值: 如果成功，该函数返回相同的 str
参数。如果到达文件末尾或者没有读取到任何字符，str
的内容保持不变，并返回一个空指针NULL。如果发生错误，返回一个空指针NULL。

fgets()和gets()的区别如下。
·fgets()函数的第2个参数指明了读入字符的最大数量。如果该参数的值是n，那么fgets()将读入n-1个字符，或者读到遇到的第一个换行符为止。
·如果fgets()读到一个换行符，会把它存储在字符串中。这点与gets()不同，gets()会丢弃换行符。
·fgets()函数的第3个参数指明要读入的文件。如果读入从键盘输入的数据，则以stdin（标准输入）作为参数，该标识符定义在stdio.h中。
因为fgets()函数把换行符放在字符串的末尾（假设输入行不溢出），通常要与fputs()函数（和puts()类似）配对使用。
如果fgets(words, 14,
stdin)函数的第2个参数为14，此时如果输入chen回车，则words保存的为chen\n\0，如果输入的为chenjunjieiwang回车，则word保存的为chenjunjiwa\0，且超出的长度依然保留在输入缓冲中，会被下一次读入。具体请看***第3次*******

fgets()函数读取输入直到第1个换行符的后面，或读到文件结尾，或者读取STLEN-1个字符（以上面的fgets()为例）。然后，fgets()在末尾添加一个空字符使之成为一个字符串。字符串的大小是其字符数加上一个空字符。如果fgets()在读到字符上限之前已读完一整行，它会把表示行结尾的换行符放在空字符前面。fgets()函数在遇到EOF时将返回NULL值，可以利用这一机制检查是否到达文件结尾；如果未遇到EOF则返回之前传给它的第一个参数地址。

********************************************  fputs()
*******************************************************************************************
int fputs(const char *str, FILE *stream) 把字符串写入到指定的流 stream
中，但不包括空字符。 返回值：该函数返回一个非负值，如果发生错误则返回 EOF。

fputs()函数是puts()针对文件定制的版本。它们的区别如下。
·fputs()函数的第2个参数指明要写入数据的文件。如果要打印在显示器上，可以用定义在stdio.h中的stdout（标准输出）作为该参数。
·与puts()不同，fputs()不会在输出的末尾添加换行符。
注意，gets()丢弃输入中的换行符，但是puts()在输出中添加换行符。另一方面，fgets()保留输入中的换行符，fputs()不在输出中添加换行符。

这里关键要注意：puts()应与gets()配对使用，fputs()应与fgets()配对使用。


***************************************************************************************************************************************
空字符和空指针的区别：
从概念上看，两者完全不同。空字符（或'\0'）是用于标记C字符串末尾的字符，其对应字符编码是0。由于其他字符的编码不可能是0，所以不可能是字符串的一部分。
空指针（或NULL）有一个值，该值不会与任何数据的有效地址对应。通常，函数使用它返回一个有效地址表示某些特殊情况发生，例如遇到文件结尾或未能按预期执行。
空字符是整数类型，而空指针是指针类型。两者有时容易混淆的原因是：它们都可以用数值0来表示。但是，从概念上看，两者是不同类型的0。另外，空字符是一个字符，占1字节；而空指针是一个地址，通常占4字节。


******************************************  fprintf()
*********************************************************************************************

int fprintf(FILE *stream, const char *format, ...) 发送格式化输出到流 stream
中。 返回值：如果成功，则返回写入的字符总数，否则返回一个负数。

******************************************  fscanf()
*********************************************************************************************
int fscanf(FILE *stream, const char *format, ...) 从流 stream 读取格式化输入。
返回值：如果成功，该函数返回成功匹配和赋值的个数。如果到达文件末尾或发生读错误，则返回
EOF。

******************************************  getc()
*********************************************************************************************
int getc(FILE *stream) 从指定的流 stream
获取下一个字符（一个无符号字符），并把位置标识符往前移动。
返回值：该函数以无符号 char 强制转换为 int
的形式返回读取的字符，如果到达文件末尾或发生读错误，则返回 EOF。

******************************************  putc()
*********************************************************************************************
int putc(int char, FILE *stream) 把参数 char
指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动。
返回值：该函数以无符号 char 强制转换为 int
的形式返回写入的字符，如果发生错误则返回 EOF。
************************************************************************************************************
标准I/O的机理
我们在前面学习了标准I/O包的特性，本节研究一个典型的概念模型，分析标准I/O的工作原理。
通常，使用标准I/O的第1步是调用fopen()打开文件（前面介绍过，C程序会自动打开3种标准文件）。fopen()函数不仅打开一个文件，还创建了一个缓冲区（在读写模式下会创建两个缓冲区）以及一个包含文件和缓冲区数据的结构。另外，fopen()返回一个指向该结构的指针，以便其他函数知道如何找到该结构。假设把该指针赋给一个指针变量fp，我们说fopen()函数“打开一个流”。如果以文本模式打开该文件，就获得一个文本流；如果以二进制模式打开该文件，就获得一个二进制流。

这个结构通常包含一个指定流中当前位置的文件位置指示器。除此之外，它还包含错误和文件结尾的指示器、一个指向缓冲区开始处的指针、一个文件标识符和一个计数（统计实际拷贝进缓冲区的字节数）。

我们主要考虑文件输入。通常，使用标准I/O的第2步是调用一个定义在stdio.h中的输入函数，如fscanf()、getc()或fgets()。一调用这些函数，文件中的缓冲大小数据块就被拷贝到缓冲区中。缓冲区的大小因实现而异，一般是512字节或是它的倍数，如4096或16384（随着计算机硬盘容量越来越大，缓冲区的大小也越来越大）。最初调用函数，除了填充缓冲区外，还要设置fp所指向的结构中的值。尤其要设置流中的当前位置和拷贝进缓冲区的字节数。通常，当前位置从字节0开始。

在初始化结构和缓冲区后，输入函数按要求从缓冲区中读取数据。在它读取数据时，文件位置指示器被设置为指向刚读取字符的下一个字符。由于stdio.h系列的所有输入函数都使用相同的缓冲区，所以调用任何一个函数都将从上一次函数停止调用的位置开始。

当输入函数发现已读完缓冲区中的所有字符时，会请求把下一个缓冲大小的数据块从文件拷贝到该缓冲区中。以这种方式，输入函数可以读取文件中的所有内容，直到文件结尾。函数在读取缓冲区中的最后一个字符后，把结尾指示器设置为真。于是，下一次被调用的输入函数将返回EOF。

输出函数以类似的方式把数据写入缓冲区。当缓冲区被填满时，数据将被拷贝至文件中。

关于EOF和文件结尾：
从文件中读取数据的程序在读到文件结尾时要停止。如何告诉程序已经读到文件结尾？如果getc()函数在读取一个字符时发现是文件结尾，它将返回一个特殊值EOF。所以C程序只有在读到超过文件末尾时才会发现文件的结尾（一些其他语言用一个特殊的函数在读取之前测试文件结尾，C语言不同）。

*******************************************  fopen()
********************************************************** FILE *fopen(const
char *filename, const char *mode) 返回值：该函数返回一个 FILE 指针。否则返回
NULL，且设置全局变量 errno 来标识错误。

***********************************************  fwrite()
******************************************************
介绍fread()和fwrite()函数之前，先要了解一些背景知识。之前用到的标准I/O函数都是面向文本的，用于处理字符和字符串。
对于标准I/O，fread()和fwrite函数用于以二进制形式处理数据:


fwrite()函数的原型如下：
size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb,FILE *
restrict fp);
fwrite()函数把二进制数据写入文件。size_t是根据标准C类型定义的类型，它是sizeof运算符返回的类型，通常是unsigned
int，但是实现可以选择使用其他类型。指针ptr是待写入数据块的地址。size表示待写入数据块的大小（以字节为单位），nmemb表示待写入数据块的数量。和其他函数一样，fp指定待写入的文件。例如，要保存一个大小为256字节的数据对象（如数组），可以这样做：
char buffer[256];

fwrite(buffer, 256, 1, fp);
以上调用把一块256字节的数据从buffer写入文件。另举一例，要保存一个内含10个double类型值的数组，可以这样做：
double earnings[10];

fwrite(earnings, sizeof(double), 10, fp);
以上调用把earnings数组中的数据写入文件，数据被分成10块，每块都是double的大小。
注意fwrite()原型中的const void * restrict
ptr声明。fwrite()的一个问题是，它的第1个参数不是固定的类型。例如，第1个例子中使用buffer，其类型是指向char的指针；而第2个例子中使用earnings，其类型是指向double的指针。在ANSI
C函数原型中，这些实际参数都被转换成指向void的指针类型，这种指针可作为一种通用类型指针（在ANSI
C之前，这些参数使用char *类型，需要把实参强制转换成char *类型）。
fwrite()函数返回成功写入项的数量。正常情况下，该返回值就是nmemb，但如果出现写入错误，返回值会比nmemb小。

*********************************************  fread()
******************************************************** size_t
fread()函数的原型如下： size_t fread(void * restrict ptr, size_t size, size_t
nmemb,FILE * restrict fp);
fread()函数接受的参数和fwrite()函数相同。在fread()函数中，ptr是待读取文件数据在内存中的地址，fp指定待读取的文件。该函数用于读取被fwrite()写入文件的数据。例如，要恢复上例中保存的内含10个double类型值的数组，可以这样做：
double earnings[10];

fread(earnings, sizeof (double), 10, fp);
该调用把10个double大小的值拷贝进earnings数组中。
fread()函数返回成功读取项的数量。正常情况下，该返回值就是nmemb，但如果出现读取错误或读到文件结尾，该返回值就会比nmemb小。

************************************************  feof()
***************************************************** int feof(FILE *fp)和int
ferror(FILE *fp)函数
如果标准输入函数返回EOF，则通常表明函数已到达文件结尾。然而，出现读取错误时，函数也会返回EOF。feof()和ferror()函数用于区分这两种情况。当上一次输入调用检测到文件结尾时，feof()函数返回一个非零值，否则返回0。当读或写出现错误，ferror()函数返回一个非零值，否则返回0。


**********************************************  system()
******************************************************* C 库函数 int
system(const char *command) 把 command
指定的命令名称或程序名称传给要被命令处理器执行的主机环境，并在命令完成后返回。
返回值: 如果发生错误，则返回值为 -1，否则返回命令的状态。
执行 dos(windows系统) 或 shell(Linux/Unix系统)
命令，参数字符串command为命令名。另，在windows系统下参数字符串不区分大小写。

在Linux/Unix系统中，system函数会调用fork函数产生子进程，由子进程来执行command命令，命令执行完后随即返回原调用的进程。

system("ls -l" );
*********************************************************************

getchar(),putchar(),printf(),scanf()都是标准I/O包的成员,处理stdin和stdout这两个流.
scanf()函数返回成功读取的项数,如果读取失败,返回0,当scanf()检测到"文件结尾"时,返回EOF(EOF是stdio.h中的特殊值,通常用#define指令将EOF定义为-1)。
getchar()函数读取文件检测到文件结尾时返回EOF。
gets(char *)和fgets(char *, size_t n, FILE *)读到文件结尾时都会返回空指针NULL。
getc(FILE *)在读取一个文件时如果读到文件结尾,则返回EOF。
fscanf(FILE *, "%s", char *)在读取一个文件时如果读到文件结尾,则返回EOF.


何时使用圆括号取决于运算对象是类型还是特定量。运算对象是类型时，圆括号必不可少，但是对于特定量，圆括号可有可无。也就是说，对于类型，应写成sizeof(char)或sizeof(float)；对于特定量，可写成sizeof
name或sizeof 6.28。尽管如此，还是建议所有情况下都使用圆括号，如sizeof(6.28)。
************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 40
#define STLEN 14

size_t writeNum = 0;
size_t readNum = 0;

//申明
void showInt2DArray(int m, int n, int (*A)[n]) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5d  ", A[i][j]);
    }
    printf("\n");
  }
}

void showInt2DArray_point(int m, int n, int **A) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5d  ", A[i][j]);
    }
    printf("\n");
  }
}

void showDouble1DArray(int m, double *A) {
  for (int i = 0; i < m; i++) {
    printf("%8lf  ", A[i]);
  }
  printf("\n");
}

void showFloat2DArray(int m, int n, float (*A)[n]) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5f  ", A[i][j]);
    }
    printf("\n");
  }
}

void showFloat2DArray_point(int m, int n, float **A) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5f  ", A[i][j]);
    }
    printf("\n");
  }
}

void showDouble2DArray(int m, int n, double (*A)[n]) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5lf  ", A[i][j]);
    }
    printf("\n");
  }
}

void showDouble2DArray_point(int m, int n, double **A) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5lf  ", A[i][j]);
    }
    printf("\n");
  }
}

//如果fgets()返回NULL，说明读到文件结尾或出现读取错误，s_gets()函数跳过了这个过程。它模仿程序清单11.9的处理方法，如果字符串中出现换行符，就用空字符替换它；如果字符串中出现空字符，就丢弃该输入行的其余字符，然后返回与fgets()相同的值。为什么要丢弃过长输入行中的余下字符。这是因为，输入行中多出来的字符会被留在缓冲区中，成为下一次读取语句的输入。例如，如果下一条读取语句要读取的是double类型的值，就可能导致程序崩溃。丢弃输入行余下的字符保证了读取语句与键盘输入同步。
char *s_gets(char *st, int n) {
  char *ret_val;
  int i = 0;
  ret_val = fgets(st, n, stdin);
  if (ret_val) {
    while (st[i] != '\n' && st[i] != '\0') {
      i++;
    }

    if (st[i] == '\n') {
      st[i] = '\0';
    } else {
      while (getchar() != '\n') {
        continue;
      }
    }
  }
  return ret_val;
}

int main(int argc, char *argv[]) {
  FILE *in, *out;
  int ch;

  printf("************************ 1 *********************\n");
  //用int getc(FILE *stream) 读取.txt文件，然后用putchar(int char) 显示在屏幕
  if ((in = fopen("./In.txt", "r")) == NULL) {
    printf("open failed ...\n");
  } else {
    printf("open successful ...\n");
  }
  while ((ch = getc(in)) != EOF) {
    putchar(ch);
  }

  fclose(in);

  printf("\n********************* 2 ************************\n");
  char *S = (char *)malloc(LEN * sizeof(char));
  scanf("%s", S);
  printf("读取的字符串为：%s\n", S);
  while (getchar() != '\n')
    continue;
  //如果输入chenjunjie回车，则S = "chenjunjie"，没有回车。

  printf("\n*********************** 3 **********************\n");
  char words[STLEN];

  puts("Enter a string, please.");
  fgets(words, STLEN, stdin);
  printf(
      "Your string twice (puts(), then fputs()):\n"); //如果输入chen回车，则words="chen\n\0"；
  printf("字符串长度:%lu\n", strlen(words));
  printf("words[3]=%c...\n", words[3]); // words[4]为'n'
  printf("words[4]=%c...", words[4]);   // words[4]为回车
  puts(words);
  fputs(words, stdout);
  puts("Enter another string, please.");
  fgets(words, STLEN, stdin);
  printf("Your string twice (puts(), then fputs()):\n");
  puts(words);
  fputs(words, stdout);
  puts("Done.");
  /*
  第1行输入，apple pie，比fgets()读入的整行输入短，因此，apple
  pie\n\0被存储在数组中，这里的\n\0很奇怪，但是就是这样。所以当puts()显示该字符串时又在末尾添加了换行符，因此apple
  pie后面有一行空行。因为fputs()不在字符串末尾添加换行符，所以并未打印出空行。
  第2行输入，strawberry
  shortcake，超过了大小的限制，所以fgets()只读入了13个字符，并把strawberry
  sh\0存储在数组中。再次提醒读者注意，puts()函数会在待输出字符串末尾添加一个换行符，而fputs()不会这样做。
  fgets()函数返回指向char的指针。如果一切进行顺利，该函数返回的地址与传入的第1个参数相同。但是，如果函数读到文件结尾，它将返回一个特殊的指针：空指针（null
  pointer）。该指针保证不会指向有效的数据，所以可用于标识这种特殊情况。在代码中，可以用数字0来代替，不过在C语言中用宏NULL来代替更常见（如果在读入数据时出现某些错误，该函数也返回NULL）。
  */
  char words1[STLEN];

  puts("Enter strings (empty line to quit):");
  while (fgets(words1, STLEN, stdin) != NULL && words1[0] != '\n')
    fputs(words1, stdout);
  puts("Done.");

  /*
  下面是该程序的输出示例：
  Enter strings (empty line to quit):
  By the way, the gets() function
  By the way, the gets() function
  also returns a null pointer if it
  also returns a null pointer if it
  encounters end-of-file.
  encounters end-of-file.
  Done.
  有意思，虽然STLEN被设置为10，但是该程序似乎在处理过长的输入时完全没问题。程序中的fgets()一次读入STLEN
  - 1个字符（该例中为9个字符）。所以，一开始它只读入了“By the wa”，并存储为By
  the
  wa\0；接着fputs()打印该字符串，而且并未换行。然后while循环进入下一轮迭代，fgets()继续从剩余的输入中读入数据，即读入“y,
  the ge”并存储为y, the
  ge\0；接着fputs()在刚才打印字符串的这一行接着打印第2次读入的字符串。然后while进入下一轮迭代，fgets()继续读取输入、fputs()打印字符串，这一过程循环进行，直到读入最后的“tion\n”。fgets()将其存储为tion\n\0，fputs()打印该字符串，由于字符串中的\n，光标被移至下一行开始处。
  系统使用缓冲的I/O。这意味着用户在按下Return键之前，输入都被存储在临时存储区（即，缓冲区）中。按下Return键就在输入中增加了一个换行符，并把整行输入发送给fgets()。对于输出，fputs()把字符发送给另一个缓冲区，当发送换行符时，缓冲区中的内容被发送至屏幕上。

  fgets()存储换行符有好处也有坏处。坏处是你可能并不想把换行符存储在字符串中，这样的换行符会带来一些麻烦。好处是对于存储的字符串而言，检查末尾是否有换行符可以判断是否读取了一整行。如果不是一整行，要妥善处理一行中剩下的字符。
  首先，如何处理掉换行符？一个方法是在已存储的字符串中查找换行符，并将其替换成空字符：

  while (words[i] != '\n') // 假设\n在words中
      i++;
  words[i] = '\0';
  */

  printf("************************** 4 **************************\n");
  /*
  该代码是统计输入的一段字符流(该字符流以\n结尾)中输入的总字符、空格和tab键的个数。
  */
  int ch1;
  int count = 0, spacenum = 0;
  /* ch = scanf("%s",S); */
  /* printf("ch= %d\n",ch); */
  while ((ch1 = getchar()) != '\n') {
    putchar(ch1);
    ++count;
    if (ch1 == ' ' || ch1 == '\t') {
      ++spacenum;
    }
  }
  printf("count = %d\n", count);
  printf("spacecount = %d\n", spacenum);
  printf("**************************** 5 *************************\n");
  //用int getc(FILE *stream)先读取In.txt文件，再用int putc(int char, FILE
  //*stream) 输出到另外的文件out1.txt
  in = fopen("./In.txt", "r");
  out = fopen("./out1.txt", "w");
  while ((ch = getc(in)) != EOF) {
    putc(ch, out);
  }

  fclose(in);
  fclose(out);

  printf("*********************** 6 ****************************\n");
  //用char *fgets(char *str, int n, FILE *stream) 读取文件，再用int fputs(const
  // char *str, FILE *stream) 写入文件
  char *cr = (char *)malloc(sizeof(char) * LEN);
  in = fopen("./In.txt", "r");
  out = fopen("./out2.txt", "w");
  while (fgets(cr, LEN, in) != NULL) {
    fputs(cr, out);
  }

  fclose(in);
  fclose(out);

  printf("*************************** 7 ***************************\n");
  //用char *fgets(char *str, int n, FILE *stream) 从stdin读取数据，再用int
  // fputs(const char *str, FILE *stream) 写入文件
  char *cr1 = (char *)malloc(sizeof(char) * LEN);
  // in = fopen("./In.txt", "r");
  out = fopen("./out3.txt", "w");
  while (fgets(cr1, LEN, stdin) != NULL) {
    fputs(cr1, out);
  }

  // fclose(in);
  fclose(out);

  printf("************************* 8 ****************************\n");
  //用char *fgets(char *str, int n, FILE *stream) 从stdin读取数据，再用int
  // fputs(const char *str, FILE *stream) 写入stdout
  char *cr2 = (char *)malloc(sizeof(char) * LEN);
  // in = fopen("./In.txt", "r");
  // out = fopen("./out3.txt", "w");
  while (fgets(cr2, LEN, stdin) != NULL) {
    fputs(cr2, stdout);
  }
  // fclose(in);
  // fclose(out);
  printf("*************************** 9 *****************************\n");
  //用int getchar(void) 从stdin读取文本，然后用int putc(int char, FILE
  //*stream)写入文件
  out = fopen("./out4.txt", "w");
  while ((ch = getchar()) != EOF) {
    putc(ch, out);
  }

  fclose(out);

  printf("************************ 10 *********************\n");
  //将数组写入.txt文件
  int m = 5, n = 10;
  int A[m][n];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = i * n + j;
    }
  }

  printf("打印数组A第一次......\n");
  showInt2DArray(m, n, A);

  //用int fprintf(FILE *stream, const char *format, ...)
  //将数组写入array1.txt文件
  out = fopen("./array1.txt", "w");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      fprintf(
          out, "%d,",
          A[i]
           [j]); //这里加两个空格或者逗号,不然array1.txt各个数字之间每空格,无法阅读
    }
    // putc('\n', out);
    fputs("\n", out);
  }
  fclose(out);

  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组
  int AA[5][10] = {0};
  in = fopen("./array1.txt", "r");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      fscanf(in, "%d,", &AA[i][j]);
    }
  }
  fclose(in);
  printf("打印数组A第二次........\n");
  showInt2DArray(m, n, AA);

  printf("\n************************ 11 ***************************\n");
  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array.txt文件中的数组

  int B[4][6] = {0};
  printf("打印读取前的数组\n");
  showInt2DArray(4, 6, B);
  in = fopen("./array2.txt", "r");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      fscanf(in, "%d,", &B[i][j]);
    }
  }
  fclose(in);
  printf("打印读取后的数组\n");
  showInt2DArray(4, 6, B);

  printf("\n************************ 12 ***************************\n");
  //用fscanf读取.txt文件(字符串，不是矩阵)
  char buf[512];

  in = fopen("./string.txt", "r");

  while (fscanf(in, "%s", buf) != EOF) {
    fputs(buf, stdout);
    printf("\n");
  }

  fclose(in);
  printf("\n************************ 13 ***************************\n");
  //用fread/fwrite将数组读取/写入.txt文件

  double earnings[10] = {1.12, 2.12, 3.12, 4.12, 5.12,
                         6.12, 7.12, 8.12, 9.12, 10.12};
  showDouble1DArray(10, earnings);
  //用int fprintf(FILE *stream, const char *format, ...)
  //将数组写入array4.txt文件
  FILE *Double1DFile_wr = fopen("./oneDDoubleFile.txt", "wb");
  size_t wriNum = 0;
  if ((wriNum = fwrite(earnings, sizeof(double), 10, Double1DFile_wr)) > 0 &&
      (wriNum == 10)) {
    printf(" fwrite  success\n");
    printf("wrNum = %zd\n", wriNum);
  } else {
    printf(" fwrite  failed\n");
    printf("wrNum = %zd\n", wriNum);
  }

  fclose(Double1DFile_wr);

  double earnings1[10] = {0};
  FILE *Double1DFile_re = fopen("./oneDDoubleFile.txt", "rb");
  size_t reNum = 0;
  if ((reNum = fread(earnings1, sizeof(double), 10, Double1DFile_re)) > 0 &&
      (reNum == 10)) {
    printf(" fread  success\n");
    printf("reNum = %zd\n", reNum);

  } else {
    printf(" fread  failed\n");
    printf("reNum = %zd\n", reNum);
  }
  fclose(Double1DFile_re);
  showDouble1DArray(10, earnings1);

  printf("\n************************ 14 ***************************\n");
  // int m = 5, n = 10;
  int C[m][n];
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = i * n + j + 1;

  showInt2DArray(m, n, C);
  FILE *Int2D_wr = fopen("./Int2D.txt", "wb");

  writeNum = 0;
  if ((writeNum = fwrite(C, sizeof(int), m * n, Int2D_wr)) > 0 &&
      (writeNum == m * n)) {
    printf(" fwrite 2D array success\n");
    printf(" writeNum = %zd\n", writeNum);
  } else {
    printf(" fwrite 2D array  failed\n");
    printf(" writeNum = %zd\n", writeNum);
  }

  fclose(Int2D_wr);

  int CC[5][10] = {0};
  readNum = 0;
  FILE *Int2D_re = fopen("./Int2D.txt", "rb");

  if ((readNum = fread(CC, sizeof(int), 50, Int2D_re)) > 0 &&
      (readNum == m * n)) {
    printf(" fread 2D array success\n");
    printf("readNum = %zd\n", readNum);
  } else {
    printf(" fread 2D array failed\n");
    printf("readNum = %zd\n", readNum);
  }
  fclose(Int2D_re);
  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组

  showInt2DArray(m, n, CC);

  printf("\n************************ 15 ***************************\n");
  //用fread/fwrite将数组读取/写入.txt文件

  //************************************************************
  // int m = 5, n = 10;
  int **D;

  D = (int **)malloc(m * sizeof(int *));

  for (int i = 0; i < m; i++) {
    D[i] = (int *)malloc(n * sizeof(int));
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      D[i][j] = i * n + j;
    }
  }
  printf("D[1][2] = %d\n", D[1][2]);

  showInt2DArray_point(m, n, D);

  FILE *Int2D_piont_wr = fopen("./Int2D_piont.txt", "wb");

  writeNum = 0;
  if ((writeNum = fwrite(D, sizeof(int), m * n, Int2D_piont_wr)) > 0 &&
      (writeNum == m * n)) {
    printf(" fwrite 2D array success\n");
    printf(" writeNum = %zd\n", writeNum);
  } else {
    printf(" fwrite 2D array  failed\n");
    printf(" writeNum = %zd\n", writeNum);
  }

  fclose(Int2D_piont_wr);

  int **DD;

  DD = (int **)malloc(m * sizeof(int *));

  for (int j = 0; j < m; j++) {
    DD[j] = (int *)malloc(n * sizeof(int));
  }

  readNum = 0;
  FILE *Int2D_piont_re = fopen("./Int2D_piont.txt", "rb");

  if ((readNum = fread(DD, sizeof(int), m * n, Int2D_piont_re)) > 0 &&
      (readNum == m * n)) {
    printf(" fread 2D array success\n");
    printf("readNum = %zd\n", readNum);
  } else {
    printf(" fread 2D array failed\n");
    printf("readNum = %zd\n", readNum);
  }
  fclose(Int2D_piont_re);
  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组
  printf("DD[1][2] = %d\n", DD[1][2]);

  showInt2DArray_point(m, n, DD);
  free(D);
  free(DD);

  printf("\n************************ 16 ***************************\n");
  //用fread/fwrite将数组读取/写入.txt文件

  // int m = 5, n = 10;
  float **E;

  E = (float **)malloc(m * sizeof(float *));

  for (int i = 0; i < m; i++) {
    E[i] = (float *)malloc(n * sizeof(float));
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      E[i][j] = i * n + j;
    }
  }
  printf("E[1][2] = %f\n", E[1][2]);

  showFloat2DArray_point(m, n, E);

  FILE *Float2D_point_wr = fopen("./Float2D_point.txt", "wb");

  writeNum = 0;
  if ((writeNum = fwrite(E, sizeof(float), m * n, Float2D_point_wr)) > 0 &&
      (writeNum == m * n)) {
    printf(" fwrite 2D array success\n");
    printf(" writeNum = %zd\n", writeNum);
  } else {
    printf(" fwrite 2D array  failed\n");
    printf(" writeNum = %zd\n", writeNum);
  }

  fclose(Float2D_point_wr);

  float **EE;

  EE = (float **)malloc(m * sizeof(float *));

  for (int j = 0; j < m; j++) {
    EE[j] = (float *)malloc(n * sizeof(float));
  }

  readNum = 0;
  FILE *Float2D_point_re = fopen("./Float2D_point.txt", "rb");

  if ((readNum = fread(EE, sizeof(float), m * n, Float2D_point_re)) > 0 &&
      (readNum == m * n)) {
    printf(" fread 2D array success\n");
    printf("readNum = %zd\n", readNum);
  } else {
    printf(" fread 2D array failed\n");
    printf("readNum = %zd\n", readNum);
  }
  fclose(Float2D_point_re);
  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组
  printf("EE[1][2] = %f\n", EE[1][2]);

  showFloat2DArray_point(m, n, EE);

  free(E);
  free(EE);

  printf("\n************************ 17 ***************************\n");
  //用fread/fwrite将数组读取/写入.txt文件

  // int m = 5, n = 10;
  float F[m][n];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      F[i][j] = i * n + j;
    }
  }

  showFloat2DArray(m, n, F);
  FILE *Float2D_wr = fopen("./Float2D.txt", "wb");

  writeNum = 0;
  if ((writeNum = fwrite(F, sizeof(float), m * n, Float2D_wr)) > 0 &&
      (writeNum == m * n)) {
    printf(" fwrite 2D array success\n");
    printf(" writeNum = %zd\n", writeNum);
  } else {
    printf(" fwrite 2D array  failed\n");
    printf(" writeNum = %zd\n", writeNum);
  }

  fclose(Float2D_wr);

  float FF[5][10] = {0};
  readNum = 0;
  FILE *Float2D_re = fopen("./Float2D.txt", "rb");

  if ((readNum = fread(FF, sizeof(float), m * n, Float2D_re)) > 0 &&
      (readNum == m * n)) {
    printf(" fread 2D array success\n");
    printf("readNum = %zd\n", readNum);
  } else {
    printf(" fread 2D array failed\n");
    printf("readNum = %zd\n", readNum);
  }
  fclose(Float2D_re);
  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组

  showFloat2DArray(m, n, FF);
  printf("\n************************ 18 ***************************\n");
  //用fread/fwrite将数组读取/写入.txt文件

  // int m = 5, n = 10;
  double G[m][n];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      G[i][j] = i * n + j;
    }
  }

  showDouble2DArray(m, n, G);
  FILE *Double2D_wr = fopen("./Double2D.txt", "wb");

  writeNum = 0;
  if ((writeNum = fwrite(G, sizeof(double), m * n, Double2D_wr)) > 0 &&
      (writeNum == m * n)) {
    printf(" fwrite 2D array success\n");
    printf(" writeNum = %zd\n", writeNum);
  } else {
    printf(" fwrite 2D array  failed\n");
    printf(" writeNum = %zd\n", writeNum);
  }

  fclose(Double2D_wr);

  double GG[5][10] = {0};
  readNum = 0;
  FILE *Double2D_re = fopen("./Double2D.txt", "rb");

  if ((readNum = fread(GG, sizeof(double), m * n, Double2D_re)) > 0 &&
      (readNum == m * n)) {
    printf(" fread 2D array success\n");
    printf("readNum = %zd\n", readNum);
  } else {
    printf(" fread 2D array failed\n");
    printf("readNum = %zd\n", readNum);
  }
  fclose(Double2D_re);
  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组

  showDouble2DArray(m, n, GG);

  printf("\n************************ 19 ***************************\n");

  //用fread/fwrite将数组读取/写入.txt文件

  // int m = 5, n = 10;
  double **H;

  H = (double **)malloc(m * sizeof(double *));

  for (int i = 0; i < m; i++) {
    H[i] = (double *)malloc(n * sizeof(double));
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      H[i][j] = i * n + j;
    }
  }
  printf("H[1][2] = %lf\n", H[1][2]);

  showDouble2DArray_point(m, n, H);

  FILE *Double2D_point_wr = fopen("./Double2D_point.txt", "wb");

  writeNum = 0;
  if ((writeNum = fwrite(H, sizeof(double), m * n, Double2D_point_wr)) > 0 &&
      (writeNum == m * n)) {
    printf(" fwrite 2D array success\n");
    printf(" writeNum = %zd\n", writeNum);
  } else {
    printf(" fwrite 2D array  failed\n");
    printf(" writeNum = %zd\n", writeNum);
  }

  fclose(Double2D_point_wr);

  double **HH;
  HH = (double **)malloc(m * sizeof(double *));

  for (int j = 0; j < m; j++) {
    HH[j] = (double *)malloc(n * sizeof(double));
  }

  readNum = 0;
  FILE *Double2D_point_re = fopen("./Double2D_point.txt", "rb");

  if ((readNum = fread(HH, sizeof(double), m * n, Double2D_point_re)) > 0 &&
      (readNum == m * n)) {
    printf(" fread 2D array success\n");
    printf("readNum = %zd\n", readNum);
  } else {
    printf(" fread 2D array failed\n");
    printf("readNum = %zd\n", readNum);
  }

  //用int fscanf(FILE *stream, const char *format, ...)
  //读取array1.txt文件中的数组
  printf("HH[1][2] = %lf\n", HH[1][2]);

  showDouble2DArray_point(m, n, HH);

  free(H);
  free(HH);
  fclose(Double2D_point_re);

  printf("\n************************over***************************\n");

  return 0;
}
