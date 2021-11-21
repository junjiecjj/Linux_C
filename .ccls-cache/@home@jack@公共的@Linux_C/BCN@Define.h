//通常，包含多个头文件时，其中的文件可能包含了相同宏定义。#ifndef指令可以防止相同的宏被重复定义。在首次定义一个宏的头文件中用#ifndef指令激活定义，随后在其他头文件中的定义都被忽略
//#ifndef指令通常用于防止多次包含一个文件。也就是说，应该像下面这样设置头文件。假设该文件被包含了多次。当预处理器首次发现该文件被包含时，THINGS_H_是未定义的，所以定义了THINGS_H_，并接着处理该文件的其他部分。当预处理器第2次发现该文件被包含时，THINGS_H_是已定义的，所以预处理器跳过了该文件的其他部分

// 为何要多次包含一个文件？最常见的原因是，许多被包含的文件中都包
// 含着其他文件，所以显式包含的文件中可能包含着已经包含的其他文件。这
// 有什么问题？在被包含的文件中有某些项（如，一些结构类型的声明）只能
// 在一个文件中出现一次。C标准头文件使用#ifndef技巧避免重复包含。但
// 是，这存在一个问题：如何确保待测试的标识符没有在别处定义。通常，实
// 现的供应商使用这些方法解决这个问题：用文件名作为标识符、使用大写字
// 母、用下划线字符代替文件名中的点字符、用下划线字符做前缀或后缀（可
// 能使用两条下划线）。例如，查看stdio.h头文件，可以发现许多类似的代码

#ifndef _DEFINE_CJJ
#define _DEFINE_CJJ


/* 系统最大跟踪批数 */
#define       MAX_L		 				8

//打印测试
#define       PRINT_FOR_TEST		 	1

//不打印
#define       NO_PRINT  	 	        0



/*==========================基本类型定义==========================*/
typedef char		        s8;
typedef short		        s16;
typedef int			s32;
typedef long long  int		s64;
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef volatile unsigned int	vu32;
typedef unsigned long long	u64;

#ifndef VOID_TYPEDEFINE
#define VOID_TYPEDEFINE
typedef void VOID;
#endif

#ifndef CHAR_TYPEDEFINE
#define CHAR_TYPEDEFINE
typedef char CHAR;
#endif


#ifndef UCHAR_TYPEDEFINE
#define UCHAR_TYPEDEFINE
typedef unsigned char UCHAR;
#endif

#ifndef SHORT_TYPEDEFINE
#define SHORT_TYPEDEFINE
typedef short int SHORT;
#endif

#ifndef WORD_TYPEDEFINE
#define WORD_TYPEDEFINE
typedef unsigned short int WORD;
#endif


#ifndef USHORT_TYPEDEFINE
#define USHORT_TYPEDEFINE
typedef unsigned short int USHORT;
#endif

#ifndef LONG_TYPEDEFINE
#define LONG_TYPEDEFINE
typedef long LONG;
#endif

#ifndef INT_TYPEDEFINE
#define INT_TYPEDEFINE
typedef int INT;
#endif

#ifndef UINT_TYPEDEFINE
#define UINT_TYPEDEFINE
typedef unsigned int UINT;
#endif

#ifndef ULONG_TYPEDEFINE
#define ULONG_TYPEDEFINE
typedef unsigned long ULONG;
#endif

#ifndef FLOAT_TYPEDEFINE
#define FLOAT_TYPEDEFINE
typedef float FLOAT;
#endif

#ifndef DOUBLE_TYPEDEFINE
#define DOUBLE_TYPEDEFINE
typedef double DOUBLE;
#endif


#ifndef BOOL_TYPEDEFINE
#define BOOL_TYPEDEFINE
typedef enum {FALSE = 0, TRUE = 1}BOOL;
#endif



//定义浮点型-实部和虚部-复数结构体表示
typedef struct ST_COMPLEX
{
	float	real; //实部

	float	imag; //虚部

} ST_COMPLEX;


#define BLACK_BLACK      "\e[40;30;1m"
#define BLACK_RED        "\e[40;31;1m"
#define BLACK_GREEN      "\e[40;32;1m"
#define BLACK_YELLOW     "\e[40;33;1m"
#define BLACK_BLUE       "\e[40;34;1m"
#define BLACK_PURTPLE    "\e[40;35;1m"
#define BLACK_DEEPGREEN  "\e[40;36;1m"
#define BLACK_WHITE      "\e[40;37;1m"

#define RED_BLACK        "\e[41;30;1m"
#define RED_RED          "\e[41;31;1m"
#define RED_GREEN        "\e[41;32;1m"
#define RED_YELLOW       "\e[41;33;1m"
#define RED_BLUE         "\e[41;34;1m"
#define RED_PURTPLE      "\e[41;35;1m"
#define RED_DEEPGREEN    "\e[41;36;1m"
#define RED_WHITE        "\e[41;37;1m"

#define GREEN_BLACK      "\e[42;30;1m"
#define GREEN_RED        "\e[42;31;1m"
#define GREEN_GREEN      "\e[42;32;1m"
#define GREEN_YELLOW     "\e[42;33;1m"
#define GREEN_BLUE       "\e[42;34;1m"
#define GREEN_PURTPLE    "\e[42;35;1m"
#define GREEN_DEEPGREEN  "\e[42;36;1m"
#define GREEN_WHITE      "\e[42;37;1m"

#define YELLOW_BLACK         "\e[43;30;1m"
#define YELLOW_RED           "\e[43;31;1m"
#define YELLOW_GREEN         "\e[43;32;1m"
#define YELLOW_YELLOW        "\e[43;33;1m"
#define YELLOW_BLUE          "\e[43;34;1m"
#define YELLOW_PURTPLE       "\e[43;35;1m"
#define YELLOW_DEEPGREEN     "\e[43;36;1m"
#define YELLOW_WHITE         "\e[43;37;1m"

#define BLUE_BLACK           "\e[44;30;1m"
#define BLUE_RED             "\e[44;31;1m"
#define BLUE_GREEN           "\e[44;32;1m"
#define BLUE_YELLOW          "\e[44;33;1m"
#define BLUE_BLUE            "\e[44;34;1m"
#define BLUE_PURTPLE         "\e[44;35;1m"
#define BLUE_DEEPGREEN       "\e[44;36;1m"
#define BLUE_WHITE           "\e[44;37;1m"

#define PURPLE_BLACK         "\e[45;30;1m"
#define PURPLE_RED           "\e[45;31;1m"
#define PURPLE_GREEN         "\e[45;32;1m"
#define PURPLE_YELLOW        "\e[45;33;1m"
#define PURPLE_BLUE          "\e[45;34;1m"
#define PURPLE_PURTPLE       "\e[45;35;1m"
#define PURPLE_DEEPGREEN     "\e[45;36;1m"
#define PURPLE_WHITE         "\e[45;37;1m"

#define DEEPGREEN_BLACK      "\e[46;30;1m"
#define DEEPGREEN_RED        "\e[46;31;1m"
#define DEEPGREEN_GREEN      "\e[46;32;1m"
#define DEEPGREEN_YELLOW     "\e[46;33;1m"
#define DEEPGREEN_BLUE       "\e[46;34;1m"
#define DEEPGREEN_PURTPLE    "\e[46;35;1m"
#define DEEPGREEN_DEEPGREEN  "\e[46;36;1m"
#define DEEPGREEN_WHITE      "\e[46;37;1m"

#define WHITE_BLACK          "\e[47;30;1m"
#define WHITE_RED            "\e[47;31;1m"
#define WHITE_GREEN          "\e[47;32;1m"
#define WHITE_YELLOW         "\e[47;33;1m"
#define WHITE_BLUE           "\e[47;34;1m"
#define WHITE_PURTPLE        "\e[47;35;1m"
#define WHITE_DEEPGREEN      "\e[47;36;1m"
#define WHITE_WHITE          "\e[47;37;1m"


#define COLOR_RESET          "\e[0m"


void Color_test();

#endif // _DEFINE_CJJ

