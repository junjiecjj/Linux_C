/*************************************************************************
>> File Name: test.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月27日 星期日 00时49分15秒

>> 此程序的功能是：
https://www.runoob.com/w3cnote/cpp-static-const.html
************************************************************************/



#include "Function.h"

void ChangeStu(Student *student)
{
    student->realAge = 12;
}


// 注意，参数列表不同包括参数的个数不同、类型不同或顺序不同，仅仅参数名称不同是不可以的。函数返回值也不能作为重载的依据。

// 函数的重载的规则：
// 函数名称必须相同。
// 参数列表必须不同（个数不同、类型不同、参数排列顺序不同等）。
// 函数的返回类型可以相同也可以不相同。
// 仅仅返回类型不同不足以成为函数的重载。

//交换 int 变量的值
void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//交换 float 变量的值
void Swap(float *a, float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}
//交换 char 变量的值
void Swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
//交换 bool 变量的值
void Swap(bool *a, bool *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

void TestSwap(void)
{
    printf("\n\n***************************  测试 Swap 类   *******************************************\n\n");
    //交换 int 变量的值
    int n1 = 100, n2 = 200;
    Swap(&n1, &n2);
    cout<<n1<<", "<<n2<<endl;

    //交换 float 变量的值
    float f1 = 12.5, f2 = 56.93;
    Swap(&f1, &f2);
    cout<<f1<<", "<<f2<<endl;

    //交换 char 变量的值
    char c1 = 'A', c2 = 'B';
    Swap(&c1, &c2);
    cout<<c1<<", "<<c2<<endl;

    //交换 bool 变量的值
    bool b1 = false, b2 = true;
    Swap(&b1, &b2);
    cout<<b1<<", "<<b2<<endl;
}