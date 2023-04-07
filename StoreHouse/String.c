/*************************************************************************
>> File Name: C_string.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.03.25

char a[10];
怎么给这个数组赋值呢？

1、定义的时候直接用字符串初始化
char a[10]="hello";
注意：不能先定义再给它赋值，如char a[10]; a[10]="hello";这样是错误的！只有定义初始化是才能这样赋值

2、对数组中字符逐个赋值
char a[10]={'h','e','l','l','o'};

3、利用strcpy，这个比较值得推荐的方法
char a[10]; strcpy(a, "hello");


易错情况：
1、char a[10]; a[10]="hello";//一个字符怎么能容纳一个字符串？况且a[10]也是不存在的！

这个最常见错误：
2、char a[10]; a="hello";//这种情况容易出现，a虽然是指针，但是它已经指向在堆栈中分配的10个字符空间，现在这个情况a又指向数据区中的hello常量，这里的指针a出现混乱，不允许！会出现const char无法转换为 char类型

3 、补充一点 char *a; a="hello";//这种情况是正确的。因为定义时a还没有指向的空间，不存在指针指向混乱的情况。

还有：不能使用关系运算符“＝＝”来比较两个字符串，只能用strcmp() 函数来处理。

C语言的运算符根本无法操作字符串。在C语言中把字符串当作数组来处理，因此，对字符串的限制方式和对数组的一样，特别是， 它们都不能用C语言的运算符进行复制和比较操作。

直接尝试对字符串进行复制或比较操作会失败。 例如，假定str1和str2有如下声明：
char str1[10], str2[10];
利用=运算符来把字符串复制到字符数组中是不可能的：
str1 = "abc";       //会报错，原理同上面分析的
str2 = str1;           //不能直接赋值
C语言把这些语句解释为 一个指针与另一个指针之间的（非法的）赋值运算 。

但是， 使用=初始化字符数组是合法的：
char str1[10] = "abc";
这是因为在声明中，=不是赋值运算符。
试图使用关系运算符或判等运算符来比较字符串是合法的，但不会产生预期的结果：
if (str1==str2) ...
这条语句把str1和str2作为指针来进行比较，而不是比较两个数组的内容。因为str1和str2有不同的地址，所以表达式str1 == str2的值一定为0。

(一)  给字符数组赋值的方法
1.定义字符数组定义时直接初始化
定义字符数组定义时直接初始化,下面例子中直接将字符串123456的首地址赋值给a

char a[6]=“123456”;

需要注意的是，在定义之后，不可以在对a数组使用字符串直接初始化，如下

char a[6];
a = "123456"

a是一个静态数组，在C语言中其在编译期间为一个常量表达式，而常量表达式可以当做是常量来使用，所以不能对于a进行指针赋值操作，既然这样是错误的，这么对于字符数组进行赋值呢

2.字符数组单个字符的赋值操作
最简单的方法是通过for循环，使用数组下标方式或指针方式，来对字符数组进行赋值。
例子:

char a[10];
char ch=‘1’;
for( i=0;i<10;i++ )
    a[i]=ch+i ; //可通过数组下标引用数组元素，完成赋值

char *p;
for(p=a; p<a+10; p++ )
    *p=ch++; //通过指针对数组相应元素赋

3、字符串赋值
实际上，可使用string.h头文件中的字符串操作函数进行赋值，那就是memcpy/strcpy或者sprintf，此memcpy 和 strcpy 的区别，后者只适用 string - 字符串，copy 数目大小由源string中的 '\0'来决定；而memcpy适用于所有类型，且由第三个参数决定 copy 的长度。函数原型为：

char *strcpy(char *dest, const char *src)
void *memcpy(void *dest, const void *src, size_t n)
int sprintf( char *buffer, const char *format, [ argument] … );

例子:

#include <stdio.h>
#include <string.h>

int main()
{
    char a[10];
    strcpy(a, "123456");
    printf("%s\n", a);
    sprintf(a, "%s", "1234567");
    printf("%s\n", a);
    memcpy(a, "12345678", 8);
    printf("%s\n", a);

   return 0;
}


(二)  给字符指针赋值的方法

#================================================================================================================================

int main() {

	char ps[6] = { 'h', 'e', 'l', 'l', 'o' }; // 等价于：char ps[6] = "hello";
	printf("%s    \n", ps);
	strcpy(ps, "abcd");
	//ps = "abcd";			// 为什么不行呢？
	printf("%s", ps);
}

因为数组在初始化的时候，就确定了指向具体内存的地址，数组名 & 内存地址都深度绑定的，不能再修改了！
虽然地址不能修改，但是地址内的值是可以修改的，上述代码中，ps[0] = ‘m’，（单引号，代表里面是字符）类似这样是可以的。
ps = “abcd”，这个是不行的。因为char ps[6] = { ‘h’, ‘e’, ‘l’, ‘l’, ‘o’ };里面，{ ‘h’, ‘e’, ‘l’, ‘l’, ‘o’ }存储在了常量内存中，而ps存储在栈内存中，初始化的时候就深度绑定了，无法再修改内存指向。而ps = “abcd"相当于在常量内存中，再找个空间存储"abcd”,然后让ps指向这块内存，所以最终无法编译通过。
strcpy(ps, “abcd”),这个之所以可以，是因为strcpy的本质是：通过字符指针修改的内容。C—为什么不能向函数传递一个数组。在原始常量区地址修改值，而不是新建一块内存空间去初始化。（strcpy的详情如下）

#================================================================================================================================



用双引号括起来的内容称为字符串字面量（string literal） ， 也叫作字符串常量（string constant），字符串常量属于静态存储类别（static storage class）。
双引号中的字符和编译器自动加入末尾的\0字符， 都作为字符串储存在内存中， 所以"I am a symbolic stringconstant."、 "I am a string in an array."、 "Something is pointed at me."、 "Here are some strings:"都是字符串字面量。

const char * pt1 = "Something is pointing at me.";
该声明和下面的声明几乎相同：
const char ar1[] = "Something is pointing at me.";
以上两个声明表明，pt1和ar1都是该字符串的地址。在这两种情况下，带双引号的字符串本身决定了预留给字符串的存储空间。尽管如此，这两种形式并不完全相同。
数组和指针
数组形式和指针形式有何不同？以上面的声明为例，数组形式（ar1[]）在计算机的内存中分配为一个内含29个元素的数组（每个元素对应一个字符，还加上一个末尾的空字符'\0'），每个元素被初始化为字符串字面量对应的字符。通常，字符串都作为可执行文件的一部分存储在数据段中。当把程序载入内存时，也载入了程序中的字符串。字符串存储在静态存储区（static
memory）中。但是，程序在开始运行时才会为该数组分配内存。此时，才将字符串拷贝到数组中（第12章将详细讲解）。注意，此时字符串有两个副本。一个是在静态内存中的字符串字面量，另一个是存储在ar1数组中的字符串。
此后，编译器便把数组名ar1识别为该数组首元素地址（&ar1[0]）的别名。这里关键要理解，在数组形式中，ar1是地址常量。不能更改ar1，如果改变了ar1，则意味着改变了数组的存储位置（即地址）。可以进行类似ar1+1这样的操作，标识数组的下一个元素。但是不允许进行++ar1这样的操作。递增运算符只能用于变量名前（或概括地说，只能用于可修改的左值），不能用于常量。
指针形式（*pt1）也使得编译器为字符串在静态存储区预留29个元素的空间。另外，一旦开始执行程序，它会为指针变量pt1留出一个存储位置，并把字符串的地址存储在指针变量中。该变量最初指向该字符串的首字符，但是它的值可以改变。因此，可以使用递增运算符。例如，++pt1将指向第2个字符（o）。
字符串字面量被视为const数据。由于pt1指向这个const数据，所以应该把pt1声明为指向const数据的指针。这意味着不能用pt1改变它所指向的数据，但是仍然可以改变pt1的值（即，pt1指向的位置）。如果把一个字符串字面量拷贝给一个数组，就可以随意改变数据，除非把数组声明为const。
总之，初始化数组把静态存储区的字符串拷贝到数组中，而初始化指针只把字符串的地址拷贝给指针。
总之，如果打算修改字符串，就不要用指针指向字符串字面量。

初始化字符串的方式：
char S[91];
char S[]="hello,jack!!!";
char *p = (char *)malloc(sizeof(char)*Len);




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


#====================================================================================
描述
C 库函数 char *strrchr(const char *str, int c) 在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置。

声明
下面是 strrchr() 函数的声明。

char *strrchr(const char *str, int c)
参数
str -- C 字符串。
c -- 要搜索的字符。以 int 形式传递，但是最终会转换回 char 形式。
返回值
该函数返回 str 中最后一次出现字符 c 的位置。如果未找到该值，则函数返回一个空指针。

#====================================================================================
描述
C 库函数 char *strstr(const char *haystack, const char *needle) 在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'。

声明
下面是 strstr() 函数的声明。

char *strstr(const char *haystack, const char *needle)
参数
haystack -- 要被检索的 C 字符串。
needle -- 在 haystack 字符串内要搜索的小字符串。
返回值
该函数返回在 haystack 中第一次出现 needle 字符串的位置，如果未找到则返回 null。

#====================================================================================
描述
C 库函数 char *strtok(char *str, const char *delim) 分解字符串 str 为一组字符串，delim 为分隔符。

声明
下面是 strtok() 函数的声明。

char *strtok(char *str, const char *delim)
参数
str -- 要被分解成一组小字符串的字符串。
delim -- 包含分隔符的 C 字符串。
返回值
该函数返回被分解的第一个子字符串，如果没有可检索的字符串，则返回一个空指针。
************************************************************************/

#include "String.h"

char *s_gets(char *st, int n)
{
  char *ret_val;
  int i = 0;

  ret_val = fgets(st, n, stdin);
  if (ret_val) {
    while (st[i] != '\n' && st[i] != '\0')
      i++;
    if (st[i] == '\n')
      st[i] = '\0';
    else // must have words[i] == '\0'
      while (getchar() != '\n')
        continue;
  }
  return ret_val;
}

void strptr(void)
{
    printf("%s, %p, %c\n", "We", "are", *"space farers");
}


void ArrDiffPnt(void)
{
    /*

    */
    printf("**************************** 测试指针和字符数组的不同之处 ******************************\n");
    char heart[] = "I love Tillie!";
    char *head   = "I love Millie!";

    //首先，两者都可以使用数组表示法：
    for (int i = 0; i < 15; i++) {
        putchar(heart[i]);
    }
    putchar('\n');

    for (int i = 0; i < 15; i++) {
        putchar(head[i]);
    }
    putchar('\n');

    // 其次，两者都能进行指针加法操作：
    for (int i = 0; i < 15; i++) {
        putchar(*(heart + i));
    }
    putchar('\n');

    /*
    假设想让head和heart统一，可以这样做:
    head=heart;
    这使得head指针指向heart数组的首元素，顺带一提，这样不会导致head指向的字符串消失， 这样做只是改变了储存在head中的地址。 除非已经保存了"I love Millie!"的地址， 否则当head指向别处时， 就无法再访问该字符串。另外， 还可以改变heart数组中元素的信息：
    heart[7]= 'M';或者*(heart + 7) = 'M';
    */

    //但是，只有指针表示法可以进行递增操作：
    // while (*(head) != '\0') {
    //     putchar(*(head++));
    // }
    // putchar('\n');
    //上面的例子会导致内存泄露，每次迭代head都会增加1，最后head会指向字符串末尾的NULL字符，导致无法回到字符串的首地址；
    //
    //总之，如果打算修改字符串，就不要用指针指向字符串字面量。

    printf("*************** 通过字符数组改变字符串 ****************\n");
    heart[2] = 'H';
    heart[3] = 'A';
    heart[4] = 'T';
    heart[5] = 'E';
    for (int i = 0; i < sizeof(heart)/sizeof(char); i++)
    {
        putchar(heart[i]);
    }
    putchar('\n');

    printf("*************** 通过指针改变字符串 ****************\n");
    // head[2] = 'H';   //段错误，因此在指针初始化为字符串字面量时使用const限定符。
    // head[3] = 'A';   //段错误
    // head[4] = 'T';   //段错误
    // head[5] = 'E';   //段错误
    for (int i = 0; i < sizeof(heart)/sizeof(char); i++)
    {
        putchar(head[i]);
    }
    putchar('\n');

    char amessage[] = "nw is the time";  /* 定义一个数组 */
    char *pmessage = "now is the time";  /* 定义一个指针 */
    /*
    上述声明中，amessage是一个仅仅足以存放初始化字符串以及空格'\0'的一维数组，数组中的单个字符可以进行修改，但是amessage始终指向同一存储位置，另一方面，pmessage是一个指针，其初始值指向一个字符串常量，之后它可以被修改以指向其他地址，但如果试图修改字符串的内容，会导致程序段错误。
    */
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
void arrchar(void)
{
    printf("**************************** 字符串数组 ******************************\n");
    const char *mytalents[LIM] = {
        "Adding numbers swiftly",
        "Multiplying accurately",
        "Stashing data",
        "Following instructions to the letter",
        "Understanding the C language"};

    char yourtalents[LIM][SLEN] = {
        "Walking in a straight line",
        "Sleeping",
        "Watching television",
        "Mailing letters",
        "Reading email"};

    int i;

    puts("Let's compare talents.");
    printf("%-36s  %-25s\n", "My Talents", "Your Talents");
    for (i = 0; i < LIM; i++)
        printf("%-36s  %-25s\n", mytalents[i], yourtalents[i]);
    printf("\nsizeof mytalents: %zd, sizeof yourtalents: %zd\n", sizeof(mytalents), sizeof(yourtalents));
}

/*
    我们来仔细分析最后两个printf()的输出。首先第1项，mesg和copy都以字符串形式输出（%s转换说明）。这里没问题，两个字符串都是"Don't be a fool!"。接着第2项，打印两个指针的地址。如上输出所示，指针mesg和copy分别存储在地址为 0x0012ff48 和 0x0012ff44 的内存中。注意最后一项，显示两个指针的值。所谓指针的值就是它存储的地址。mesg和copy的值都是0x0040a000，说明它们都指向的同一个位置。因此，程序并未拷贝字符串。语句copy = mesg;把mesg的值赋给copy，即让copy也指向mesg指向的字符串。为什么要这样做？为何不拷贝整个字符串？假设数组有50个元素，考虑一下哪种方法更效率：拷贝一个地址还是拷贝整个数组？ 通常，程序要完成某项操作只需要知道地址就可以了。如果确实需要拷贝整个数组，可以使用strcpy()或strncpy()函数，本章稍后介绍这两个函数。
 */

void p_and_s(void)
{
    printf("**************************** 指针和字符串 ******************************\n");
    const char *mesg = "Don't be a fool!";
    const char *copy;

    copy = mesg;
    printf("%s\n", copy);
    printf("mesg = %s; &mesg = %p; value = %p\n", mesg, &mesg, mesg);
    printf("copy = %s; &copy = %p; value = %p\n", copy, &copy, copy);
}

int UseStrncat(void)
{
    char src[50], dest[50];
    strcpy(src,  "This is source");
    strcpy(dest, "This is destination");
    strncat(dest, src, 15);
    printf("最终的目标字符串： |%s|", dest);

    return 0;
}



/*
前面提到过，如果pts1和pts2都是指向字符串的指针，那么下面语句拷贝的是字符串的地址而不是字符串本身：
pst2 = pst1;

如果希望拷贝整个字符串，要使用strcpy()函数。程序清单11.25要求用户输入以q开头的单词。该程序把输入拷贝至一个临时数组中，如果第1个字母是q，程序调用strcpy()把整个字符串从临时数组拷贝至目标数组中。strcpy()函数相当于字符串赋值运算符。

请注意，strcpy()第2个参数（temp）指向的字符串被拷贝至第1个参数（qword[i]）指向的数组中。拷贝出来的字符串被称为目标字符串，
最初的字符串被称为源字符串。参考赋值表达式语句，很容易记住strcpy()参数的顺序，即第1个是目标字符串，第2个是源字符串。

程序员有责任确保目标数组有足够的空间容纳源字符串的副本。下面的代码有点问题：
char *str;
strcpy(str, "the c of Tranquility");
strcpy()把"The C of
Tranquility"拷贝至str指向的地址上，但是str未被初始化，所以该字符串可能被拷贝到任意的地方！
总之，strcpy()接受两个字符串指针作为参数，可以把指向源字符串的第2个指针声明为指针、数组名或字符串常量；
而指向源字符串副本的第1个指针应指向一个数据对象（如，数组），且该对象有足够的空间存储源字符串的副本。
记住，声明数组将分配存储数据的空间，而声明指针只分配存储一个地址的空间。

*/

void copy1(void)
{
    printf("**************************** strcpy()函数 ******************************\n");
    char qwords[LIM][SIZE1];
    char temp[SIZE1];
    int i = 0;

    printf("Enter %d words beginning with q:\n", LIM);
    while (i < LIM && s_gets(temp, SIZE1)) {
        if (temp[0] != 'q')
        printf("%s doesn't begin with q!\n", temp);
        else {
        strcpy(qwords[i], temp);
        i++;
        }
    }
    puts("Here are the words accepted:");
    for (i = 0; i < LIM; i++)
        puts(qwords[i]);
}

/*
strcpy()函数还有两个有用的属性。第一，strcpy()的返回类型是char*，该函数返回的是第1个参数的值，即一个字符的地址。第二，第1个参数不必指向数组的开始。这个属性可用于拷贝数组的一部分。下面函数的这两个属性。注意，strcpy()把源字符串中的空字符也拷贝在内。在该例中，空字符覆盖了copy数组中that的第1个t（见图11.5）。注意，由于第1个参数是copy + 7，所以ps指向copy中的第8个元素（下标为7）。因此puts(ps)从该处开始打印字符串。
 */
void copy2(void)
{
    printf("**************************** strcpy()的其他属性 ******************************\n");
    const char *orig = WORDS;
    char copy[SIZE1] = "Be the best that you can be.";
    char *ps;

    puts(orig);
    puts(copy);
    ps = strcpy(copy + 7, orig);
    puts(copy);
    puts(ps);
}

/*
更谨慎的选择：
strncpy()strcpy()和strcat()都有同样的问题，它们都不能检查目标空间是否能容纳源字符串的副本。
拷贝字符串用strncpy()更安全，该函数的第3个参数指明可拷贝的最大字符数。程序清单11.27用strncpy()代替程序清单11.25中的strcpy()。
为了演示目标空间装不下源字符串的副本会发生什么情况，该程序使用了一个相当小的目标字符串（共7个元素，包含6个字符）。

strncpy(target, source,
n)把source中的n个字符或空字符之前的字符（先满足哪个条件就拷贝到何处）拷贝至target中。
因此，如果source中的字符数小于n，则拷贝整个字符串，包括空字符。但是，strncpy()拷贝字符串的长度不会超过n，
如果拷贝到第n个字符时还未拷贝完整个源字符串，就不会拷贝空字符。所以，拷贝的副本中不一定有空字符。
鉴于此，该程序把n设置为比目标数组大小少1（TARGSIZE-1），然后把数组最后一个元素设置为空字符：
*/
void copy3(void)
{
    printf("**************************** strncpy()函数 ******************************\n");
    char qwords[LIM][TARGSIZE];
    char temp[SIZE1];
    int i = 0;

    printf("Enter %d words beginning with q:\n", LIM);
    while (i < LIM && s_gets(temp, SIZE1)) {
        if (temp[0] != 'q')
        printf("%s doesn't begin with q!\n", temp);
        else {
        strncpy(qwords[i], temp, TARGSIZE - 1);
        qwords[i][TARGSIZE - 1] = '\0';
        i++;
        }
    }
    puts("Here are the words accepted:");
    for (i = 0; i < LIM; i++)
        puts(qwords[i]);
}

/*

sprintf()函数声明在stdio.h中，而不是在string.h中。该函数和printf()类似，但是它是把数据写入字符串，而不是打印在显示器上。
因此，该函数可以把多个元素组合成一个字符串。sprintf()的第1个参数是目标字符串的地址。其余参数和printf()相同，即格式字符串和待写入项的列表。
程序清单11.28中的程序用sprintf()把3个项（两个字符串和一个数字）组合成一个字符串。注意，sprintf()的用法和printf()相同，
只不过sprintf()把组合后的字符串存储在数组formal中而不是显示在屏幕上。
*/
void format(void)
{
    printf("**************************** sprintf()函数 ******************************\n");
    char first[MAX];
    char last[MAX];
    char formal[2 * MAX + 100];
    double prize;

    puts("Enter your first name:");
    s_gets(first, MAX);
    puts("Enter your last name:");
    s_gets(last, MAX);
    puts("Enter your prize money:");
    scanf("%lf", &prize);
    sprintf(formal, "%s, %-19s: $%6.2f\n", last, first, prize);
    puts(formal);
}

// https://zhuanlan.zhihu.com/p/377633216
// 逐个访问字符串中的字符并逐行打印

// 思路一：根据数组长度逐个遍历
void travel_str(void)
{
	int i = 0;
	char str[] = {"Hello World!"};
	int len = strlen(str); // 计算字符串大小

        // 逐个遍历
	for(i=0;i<len;i++)
	{
		printf("%c\n", str[i]);
	}
}

// 思路二：利用指针进行遍历
void travel_str1(void)
{
	char str[] = {"Hello World!"};
	char *ch = str;

        // 不能直接采用原指针str遍历，因为此处的str不能改变其指向的地址。
        // 即使可以也会因为str指向了别处导致str原来指向的内存无法被释放，造成内存泄露。
	while(*ch != '\0') // 以'\0'作为字符串结束标志
	{
		printf("%c\n", *ch++);
	}
}

// // 方式一：必须指定第二维的大小，且应大于等于数组最长字符串的长度
// char str_arr1[][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
// // 方式二
// char *str_arr2[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
// 遍历数组中的字符串

// 思路一
void travel_str_array(void)
{
	unsigned char i = 0, size = 0;
	// char str_arr[][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	char *str_arr[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

	size = sizeof(str_arr)/sizeof(str_arr[0]); // 获取数组大小

	for(i=0; i<size; i++)
	{
		// printf("%s\n", str_arr[i]);
		printf("%s\n", *(str_arr+i));
	}
}

// 思路二
void travel_str_array1(void)
{
	char *str_arr[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", NULL};
	char **str = str_arr; // 采用临时指针指向原数组，避免因原数组指针移动导致内存泄露。

	// 采用该方法遍历时建议采用方法二定义数组，并在数组最后手动添加NULL。
	while(*str != NULL)
	{
		printf("%s\n", *str++);
	}

	// 另一种循环方式
#if 0
	char **ptr = NULL;
	for(ptr=str_arr; *ptr!=NULL; ptr++)
	{
		printf("%s\n", *ptr);
	}
#endif
}

// 【小结】

// 若采用指针遍历字符串数组时，务必在数组最后手动添加NULL，以确保能够准确找到字符串数组的结尾。否则，指针会指向其他非目标位置，甚至导致程序崩溃。
// 若通过计算数组大小来遍历字符串数组时，尾部无需添加NULL。如果手动添加了NULL ，则在遍历数组时应将数组长度减去1，因为编译器多分配了一个指向NULL的指针。访问NULL指针会导致程序崩溃。具体分析见第五节。



// 五、遍历字符串数组中的字符
void travel_str_array_by_char(void)
{
	unsigned char i,j = 0;
	char *str_arr[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", NULL};
	int len = sizeof(str_arr)/sizeof(str_arr[0]);
	char **str = str_arr;

	// 利用指针遍历字符串数据中的字符
	for(str=str_arr; *str!=NULL; str++)
	{
		for(j=0; j<strlen(*str);j++)
		{
			printf("%c ", *((*str)+j));
		}
		printf("\n");
	}

	// 利用字符串数组大小和字符串长度来遍历字符串数组中的字符
	for(i=0; i<len-1; i++)
	{
		for(j=0;j<strlen(str_arr[i]);j++)
		{
			// printf("%c ",*(*(str_arr+i)+j));
			printf("%c ",str_arr[i][j]);
		}
		printf("\n");
	}

	// 错误示例
#if 0
	for(i=0; i<len; i++)
	{
		// 当i=len-1时，str_arr[i] = NULL，此时strlen(NULL)访问NULL指针，程序崩溃。
		for(j=0;j<strlen(str_arr[i]);j++)
		{
			// printf("%c ",*(*(str_arr+i)+j));
			printf("%c ",str_arr[i][j]);
		}
		printf("\n");
	}
#endif
}

/*
一、字符串的定义

char *str1 = {"Hello world!"};  // 方式一 (可省略{})
char str2[] = {"Hello world!"}; // 方式二 (可省略{})
char str3[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0'}; // 方式三
几种字符串定义方式之间的区别
(1) 方式一的本质是定义了一个char型指针str1， 指向的是字符串常量Hello world!，因此str1所指向地址中的内容是不可更改的，即不能使用类似str1[0] = 'h';的语句对其进行赋值操作。但是指针str1仍然可以指向其他地址，例如可利用str1 = str2;语句将str1指向str2所指向的地址。 此外，字符串的结尾会被编译器自动加上结束符\0。

(2) 方式二定义了以一个char型数组str2，str2指向数组第一个元素所处内存的地址。此时内存空间是由栈分配的，地址一经分配就不能更改，因此str2不能再指向其他内存空间，但其所指向的内存空间中的内容是可以更改的，即可以使用类似str2[0] = 'h';的语句对其进行赋值操作。字符串的结尾也会被编译器自动加上结束符\0。

(3)方式三中如果没有指定大小的话，编译器只会会根据字符串大小分配空间，但不会在字符串结尾添加'\0'。为避免其他异常情况的出现，务必在字符串结尾处手动加上'\0'。以该方式定义字符串时不允许有空的单字符''，即' '中的空格不能省略；

获取字符串的长度
常用运算符sizeof()和strlen()函数这两种方式来计算字符串的长度。

sizeof()的值是在编译时计算得到的，因此不能用于计算动态分配的内存空间大小。sizeof()可用于基本类型、结构体以及数组等静态分配的对象所占空间大小的计算，其返回值与内存中存储的内容无关。

例如，在32位系统中，char类型变量占用的空间为一个字节 ，即sizeof(char)的值为1。而字符型指针char *的本质是一个int型变量，所以其占用的空间大小为四个字节，即sizeof(char *)的值为4。

函数strlen()的函数原型为size_t __cdecl strlen(const char *); ，其声明位于头文件string.h中。 strlen()是在运行时计算的，其返回值为从给定的地址开始到遇见的第一个NULL之间的长度。 返回的长度并不包含NULL所占用的空间。

【小结】运算符sizeof()与函数strlen()的区别。

sizeof()	                  strlen()
编译时计算。	               运行时计算。
数组、结构体等静态变量。	    char *类型的变量，必须以'\0'结尾。
数组名传给sizeof()不会退化。	数组名传给strlen()会退化为指针。
利用sizeof()和strlen()分别计算上述三种定义方式定义的字符串的长度：

printf("sizeof(str1)=%d\n", sizeof(str1));
printf("sizeof(str2)=%d\n", sizeof(str2));
printf("sizeof(str3)=%d\n", sizeof(str3));
printf("sizeof(str4)=%d\n", sizeof(str4));

printf("strlen(str1)=%d\n", strlen(str1));
printf("strlen(str2)=%d\n", strlen(str2));
printf("strlen(str3)=%d\n", strlen(str3));
printf("strlen(str4)=%d\n", strlen(str4));


计算结果为

sizeof(str1)=4    // 即sizeof(char *),返回的是字符型指针的大小，故sizeof无法计算方式一定义的字符串的长度。
sizeof(str2)=13   // 包含'\0'。
sizeof(str3)=13   // 包含'\0'。
sizeof(str4)=16   // 返回的是实际分配的内存大小，而不是字符串的长度。

strlen(str1)=12   // 不包含'\0'。
strlen(str2)=12   // 不包含'\0',故比sizeof(str2)的值小1。
strlen(str3)=12   // 不包含'\0',故比sizeof(str3)的值小1。
strlen(str4)=12   // 返回的是字符串的实际长度(不包含'\0'),而不是实际分配的内存大小。


sizeof() 和 strlen() 是 C 语言中两个非常常用的函数，它们都与计算内存大小有关，但是它们的作用是不同的。

sizeof() 和 strlen() 的主要区别在于：

sizeof() 是一个运算符，而 strlen() 是一个函数。
sizeof() 计算的是变量或类型所占用的内存字节数，而 strlen() 计算的是字符串中字符的个数。
sizeof() 可以用于任何类型的数据，而 strlen() 只能用于以空字符 '\0' 结尾的字符串。
sizeof() 计算字符串的长度，包含末尾的 '\0'，strlen() 计算字符串的长度，不包含字符串末尾的 '\0'。
sizeof() 函数是一个运算符而不是函数，用于计算一个类型或变量所占用的内存字节数。可以用它来获取任何类型的数据的字节数，包括基本数据类型、数组、结构体、共用体等等。

sizeof就是一个计算数据类型所占空间大小的单目运算符，在计算字符串的空间大小时，包含了结束符\0的位置；而strlen是一个计算字符串长度的函数，使用时需要引用头文件#include <string.h>，不包含\0,即计算第一个 \0 之前的字符串长度。

strlen() 函数用于计算一个字符串的长度，即它所包含的字符个数（不包括字符串结尾的空字符 '\0'）。
需要注意的是，strlen() 函数只能用于计算以空字符 '\0' 结尾的字符串的长度，如果字符串中没有空字符，则 strlen() 函数的行为是未定义的。


*/
void LenSizeofStr(void)
{
    printf("**************************** 字符数组和sizeof、strlen等 ******************************\n");
    char S1[20] = "hello world";
    char S2[20] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
    char S3[20] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd', '\0'};
    char S4[20] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char S5[] = "hello\0world";
    char S6[] = {'h', 'e', 'l', 'l', 'o', '\0', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
    char S7[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
    char S8[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}; // strlen(S8)产生未定义的结果，因为S8不是以'\0'结尾，strlen可能一直向前查找直到遇到空字符
    char *S9 = "hello world";

    printf("s1 = %s, s2 = %s, s3 = %s, s4 = %s, s5 = %s, s6 = %s, s7 = %s, s8 = %s, s9 =%s\n", S1, S2, S3, S4, S5, S6, S7, S8, S9);

    printf("strlen(S1) = %zd , strlen(S2) = %zd , strlen(S3) = %zd, strlen(S4) = %zd , strlen(S5) = %zd, strlen(S6) = %zd, strlen(S7) = %zd, strlen(S8) = %zd, strlen(S9) = %zd\n", strlen(S1), strlen(S2), strlen(S3), strlen(S4), strlen(S5), strlen(S6), strlen(S7), strlen(S8), strlen(S9));

    printf("sizeof(S1) = %zd , sizeof(S2) = %zd , sizeof(S3) = %zd , sizeof(S4) = %zd , sizeof(S5) = %zd ,sizeof(S6) = %zd , sizeof(S7) = %zd, sizeof(S8) = %zd ,sizeof(S9) = %zd\n", sizeof(S1), sizeof(S2), sizeof(S3), sizeof(S4), sizeof(S5), sizeof(S6), sizeof(S7), sizeof(S8), sizeof(S9));

// s1 = hello world, s2 = hello world, s3 = hello, s4 = hello world, s5 = hello, s6 = hello, s7 = hello world, s8 = hello worldhello, s9 =hello world
// strlen(S1) = 11 , strlen(S2) = 11 , strlen(S3) = 5, strlen(S4) = 11 , strlen(S5) = 5, strlen(S6) = 5, strlen(S7) = 11, strlen(S8) = 16, strlen(S9) = 11
// sizeof(S1) = 20 , sizeof(S2) = 20 , sizeof(S3) = 20 , sizeof(S4) = 20 , sizeof(S5) = 12 ,sizeof(S6) = 13 , sizeof(S7) = 12, sizeof(S8) = 11 ,sizeof(S9) = 8


    printf("==================================================================================================\n\n");
    char a[] = "hello";
    printf("a = %s\n", a);
    printf("strlen(a) = %zd\n", strlen(a));  // 5
    printf("sizeof(a) = %zd\n\n", sizeof(a));  // 6


    char b[] = "hello\0";
    printf("b = %s\n", b);
    printf("strlen(b) = %zd\n", strlen(b));  // 5
    printf("sizeof(b) = %zd\n\n", sizeof(b));  // 7


    char c[] = "hello\n";
    printf("c = %s\n", c);
    printf("strlen(c) = %zd\n", strlen(c)); // 6
    printf("sizeof(c) = %zd\n\n", sizeof(c));  // 7


    char d[] = "hello\0\n";
    printf("d = %s\n", d);
    printf("strlen(d) = %zd\n", strlen(d));  // 5
    printf("sizeof(d) = %zd\n\n", sizeof(d));  // 8


    char e[] = "hello\n\0";
    printf("e = %s\n", e);
    printf("strlen(e) = %zd\n", strlen(e));  // 6
    printf("sizeof(e) = %zd\n\n", sizeof(e));  // 8


    char f[] = "hello\0\0\n";
    printf("f = %s\n", f);
    printf("strlen(f) = %zd\n", strlen(f));  // 5
    printf("sizeof(f) = %zd\n\n", sizeof(f));   // 9


    char g[] = "hello\n\0\0";
    printf("g = %s\n", g);
    printf("strlen(g) = %zd\n", strlen(g));    // 6
    printf("sizeof(g) = %zd\n\n", sizeof(g));    // 9


    char h[] = "hello\0\n\n";
    printf("h = %s\n", h);
    printf("strlen(h) = %zd\n", strlen(h));   //  5
    printf("sizeof(h) = %zd\n\n", sizeof(h));   //  9


    char i[] = "hello\n\n\0";
    printf("i = %s\n", i);
    printf("strlen(i) = %zd\n", strlen(i));   // 7
    printf("sizeof(i) = %zd\n\n", sizeof(i));  //  9


    char j[] = "hello\r\n";
    printf("j = %s\n", j);
    printf("strlen(j) = %zd\n", strlen(j));  //  7
    printf("sizeof(j) = %zd\n\n", sizeof(j)); //  8


    char k[] = "hello\n\r";
    printf("k = %s\n", k);
    printf("strlen(k) = %zd\n", strlen(k));  //  7
    printf("sizeof(k) = %zd\n\n", sizeof(k));   // 8

    char *l = "hello";
    printf("l = %s\n", l);
    printf("strlen(k) = %zd\n", strlen(l));  //  7
    printf("sizeof(k) = %zd\n\n", sizeof(l));   // 8


    //  strlen()只能以char*作为参数,不能以类型作为参数,该函数实际完成的功能是从代表该字符串的第一个地址开始遍历，直到遇到结束符'\0', 在遇到'\0'前的任何字符都算作字符串的成员，如'\n'、'\t'、'\r'等. 返回的长度大小不包括'\0'。
    //  c/c++ strlen(str)和str.length()和str.size()都可以求字符串长度。 其中str.length()和str.size()是用于求string类对象长度的成员函数. strlen(str)是用于求字符数组的长度，其参数是char*
}

int CString(void)
{
    printf("**************************** 测试字符串和指针 ******************************\n");


    //ArrDiffPnt();

    //p_and_s();


    //copy1();


    //copy2();


    //copy3();


    //format();


    // arrchar();


    LenSizeofStr();

    return 0;
}
/*
输出为：

strlen(S1) = 11 , strlen(S2) = 11 , strlen(S3) = 5 , strlen(S4) = 11 ,
strlen(S5) = 5 , strlen(S6) = 5 , strlen(S7) = 11 , strlen(S8) = 22 , strlen(S9)
= 11

sizeof(S1) = 20 , sizeof(S2) = 20 , sizeof(S3) = 20 , sizeof(S4) = 20 ,
sizeof(S5) = 12 ,sizeof(S6) = 13 , sizeof(S7) = 12 , sizeof(S8) = 11 ,sizeof(S9)
= 8 sizeof(S9)是求字符指针的字节数，为8个字节


 */


int main(int argc, char *argv[]){

    CString();


    return 0;
}