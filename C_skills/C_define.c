
/*
学习了这么多年C语言，说实话对宏自以为了如指掌了，没想到看内核代码的时候还是那么吃力，设备驱动代码中有很多这样或者那样的宏定义，各种define，博主在学习的过程中将C语言中所出现的#define定义整理总结了一下，供大家借鉴和学习。

原来以为什么是宏？无非就是定义一个替换的量，好比#define
PI 3.1415926，这样的功能，再深一点就是写一个类似函数的定义，好比#define MAX(a,b)
((a) > (b) ? (a) :
(b))这样的功能，再问一下宏是什么？无非就是预处理阶段所要展开的乱七八糟的东西，其实也就知道这么点，当看了Linux
Kernel
Code，其实会发现自己懂得那些其实都是皮毛，不值一提的小东西，才发现自己OUT了，为此博主将#define的使用方法总结了一下，如下所示：（如有不足请批评指正）

1. 最最最简单的define定义
    不赘述了，说一下其他的吧，如#define MAX
10，编译器在处理这个代码之前会对MAX进行处理，替换为10，或许有些人认为这样的定义看起来和const常量很相似，但是他们还是有区别的，#define的定义其实就是简单的文本的替换，并不是作为一个量来使用

2. 用#define来对函数进行“定义”
    很多就会问了，什么？居然还能用#define来定义函数，坑爹么？其实咋说呢，就是类似的一个函数定义罢了，和真正的函数定义当然还是有区别的了，下面进行举例说明：

   还是用上面的MAX的例子：#define MAX(a,b) ((a) > (b) ? (a) :
(b))，这个定义就返回两个数中较大的那个，不知道你们看到了没看到，这个”函数“没有类型检查，像不像函数模板？像？不像？
    其实是有点像的，可以作为一个普通的模板来使用罢了，他肯定没函数模板那么安全，WHY？看下面的例子：

    #define MINUS(a,b) a -
b,眨眼一看，这个肯定是减法操作的define，有木有？对，没错，就是这个意思，这个定义在一般的使用中没问题，但是在特定的情况下使用会出现问题，如果我们要这样去使用
的话，展开之后会是什么样子呢？如：2 * MINUS(a,b) /
4，就像我前面所说的那样，宏其实就是一个简单的文本替换，所以展开时候就变为 2 * a
- b / 4，和我们想要的结果是不是不一样？是不是错
了？有木有？那要如何解决这个问题呢，很简单，给原定义加一个括号就OK了，也就是#define
MINUS(a,b) (a - b)

    再说一个经常出现的一个错误，看下面的例子：
    #define pin (int *)
    pin a,b;
    本意其实都想让a和b成为int型指针，但是实际上却变成了int
*a，b;a是int型指针，b是int型变量，咋处理捏？这个时候typedef就出来了，它说我可以满
足define满足不了的要求，所以改成 typedef pin (int *) 就OK了。

    TIP：我们在写code的时候一定要养成一个良好的习惯和一个良好的代码编写风格，建议所有的层次都加上括号

3. define的单行定义，举例说明之，属于少见用法
    #define A(x) ##x
    #define B(x) #@x
    #define C(x) #x
    如果我们假设x=1，那么A(1)就是1，B(1)就是‘1’，C(1)就是”1“

4. define的多行定义
    #define可以进行多行定义，虽然看起来有点蛋疼，但是确实是一个灰常经典而且在设备驱动代码中经常要用到的一个方法，格式如下：
    #define MACRO(arg1,arg2) do {  \
    test1; \
    test2; \
    }while(0)

    TIP:在每一行的末尾要加上\，切记！

5. 定义宏和取消宏定义的方法
    定义一个宏使用#define，取消一个宏定义使用#undef

6. 使用宏进行条件编译
    格式如下：#ifdef ... (#else) ... #endif
    如：
    #ifdef HELLO
    #define WORLD 1
    #else
    #define WORLD 0
    #endif

7. 用define来处理头文件被头文件或者源文件包含的情况
    由于头文件包含可以嵌套，那么c文件有可能包含多次同一个头文件，就会出现重复定义的问题的，那么可以就通过条件编译开关来避免重复包含，如下：
    #ifndef _HELLO_H_
    #define _HELLO_H_
    ...
    //文件内容
    ...
    #endif
*/

/* preproc.c -- simple preprocessor examples */
#include <stdio.h>
#define TWO 2 /* you can use comments if you like   */
#define OW                                                                     \
  "Consistency is the last refuge of the unimagina\
tive. - Oscar Wilde" /* a backslash continues a definition */
/* to the next line                   */
#define FOUR TWO *TWO
#define PX printf("X is %d.\n", x)
#define FMT "X is %d.\n"

int main(void) {
  int x = TWO;

  PX;
  x = FOUR;
  printf(FMT, x);
  printf("%s\n", OW);
  printf("TWO: OW\n");

  return 0;
}
