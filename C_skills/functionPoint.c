/*************************************************************************
>> File Name: functionPoint.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月13日 星期六 19时34分37秒

>> 此程序的功能是：

指针型函数
前面我们介绍过，所谓函数类型是指函数返回值的类型。在C语言中允许一个函数的返回值是一个指针（即地址），这种返回指针值的函数称为指针型函数。定义指针型函数的一般形式为：
数据类型 *函数名(形参列表){
    //函数体
}
函数名之前加了*号表明这是一个指针型函数，它的返回值是一个指针。如：

#include <stdio.h>

// 返回两个字符串中较长的一个
char *func(char *str1, char *str2){
    if(strlen(str1) >= strlen(str2)){
        return str1;
    }else{
        return str2;
    }
}

int main(){
    char *s1 = "C Language";
    char *s2 = "C is very great!";
    char *longstr = func(s1, s2);
    printf("Long string: %s\n", longstr);

    return 0;
}


运行结果：
Long string: C is very great!

func 是一个指针型函数，它返回的指针指向一个字符串。


函数指针变量（选读）
在C语言中，一个函数总是占用一段连续的内存区域，函数名就是该函数所占内存区域的首地址。我们可以把函数的这个首地址（或称入口地址）赋予一个指针变量，使该指针变量指向该函数，然后通过指针变量就可以找到并调用这个函数。我们把这种指向函数的指针变量称为函数指针变量。

函数指针变量定义的一般形式为：
数据类型 (*指针变量名)();
数据类型表示被指函数的返回值的类型，(*指针变量名)表示 *
后面的变量是指针变量，最后的空括号表示指针变量所指的是一个函数。例如： int
(*pf)(); 表示 pf 是一个指向函数入口的指针变量，该函数的返回值是整型。

【示例】用指针形式实现对函数的调用。
#include <stdio.h>
// 返回两个值中较大的值
int max(int a, int b){
    if(a>b) return a;
    else return b;
}
int main(){
    int(*pmax)();
    int x, y, maxval;
    pmax = max;
    printf("Input two numbers:");
    scanf("%d %d", &x, &y);
    maxval = (*pmax)(x, y);
    printf("Max value: %d\n", maxval);
    return 0;
}
运行结果：
Input two numbers:100 200
Max value: 200

从上述程序可以看出用，函数指针变量形式调用函数的步骤如下：
先定义函数指针变量，第10行int(*pmax)();定义 pmax 为函数指针变量。
把被调函数的入口地址（函数名）赋予该函数指针变量，如程序中第12行pmax=max;
用函数指针变量形式调用函数，如程序第15行z=(*pmax)(x,y);
调用函数的一般形式为：(*指针变量名) (实参列表)

使用函数指针变量还应注意以下两点：
函数指针变量不能进行算术运算，这是与数组指针变量不同的。数组指针变量加减一个整数可使指针移动指向后面或前面的数组元素，而函数指针的移动是毫无意义的。
函数调用中(*指针变量名)的两边的括号不可少，其中的*不应该理解为求值运算，在此处它只是一种表示符号。
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

int main(int argc, char *argv[]) {}
