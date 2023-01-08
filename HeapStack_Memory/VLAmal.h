

/************************************************************************
C99定义的这种变长数组的使用是有限制的，不能像在C++等语言中一样自由使用
变长数组有以下限制：
1、变长数组必须在程序块的范围内定义，不能在文件范围内定义变长数组；
2、变长数组不能用static或者extern修饰；
3、变长数组不能作为结构体或者联合的成员，只能以独立的数组形式存在；
4、变长数组的作用域为块的范围，对应地，变长数组的生存时间为当函数执行流退出变长数组所在块的时

*************************************************************************/


#ifndef _VLA_CJJ
#define _VLA_CJJ



#include <stdio.h>
#include  "Utility.h"

#define MONTHS 12
#define LEN 10

extern int *GlobalPoint;

extern const int days[MONTHS];

int   *MallocAndReturnLocalPoint(void);
void  UseLocalPoint(void);
void  FreeLocalPoint(int *LocalPoint);


void DisplayMonth(void);



#endif  //_VLA_CJJ