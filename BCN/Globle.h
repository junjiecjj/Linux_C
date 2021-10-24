#ifndef _GLOBLE_CJJ
#define _GLOBLE_CJJ

/*定义工程中所用的全局变量：
一般，在一个Globle_Param.h文件中定义工程中的全局变量:
int 	A   =  1;
然后再别的.h或者.c文件中需要用:
extern int A;
来引用，因为全局参数只能定义一次，但可以引用多次。

 */




int 	A   =  1;


char Time[255];

const double PI = 3.1415926;


const char * MONTHS[12] = {"January", "February","March","April","May","June","July","August","September","October","November","December"};

#endif // _GLOBLE_CJJ


