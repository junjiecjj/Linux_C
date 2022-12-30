/*************************************************************************
>> File Name: test.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月27日 星期日 00时49分15秒

>> 此程序的功能是：
https://www.runoob.com/w3cnote/cpp-static-const.html
************************************************************************/


#ifndef _DEFINE_CJJ
#define _DEFINE_CJJ


#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#include<cstdio>
#include<ctime>
#include<string>
#include<clocale>
#include<vector>





/*****************************************************************************
测试静态成员变量和静态成员函数


1.静态成员变量

静态成员变量是一种特殊的成员变量，类体中的数据成员声明时前面加上关键字static，即成为该类的静态数据成员，即静态成员变量。静态成员变量实际上就是类域中的全局变量，必须初始化，且只能在类体外。初始化时不受private和protected访问限制。

静态成员变量属于类，不属于某个具体的对象。如上面的代码，即使创建多个对象，也只为num分配一份内存，所有对象使用的是这份内存中的数据，当某个对象修改了num，也会影响到其他的对象。static成员变量不占用对象内存，在所有对象外开辟内存，不创建对象也可以访问。

static成员变量和普通static变量一样，编译时在静态数据区分配内存，到程序结束时才释放。这就意味着static成员变量不随对象的创建而分配内存，也不随对象的销毁而释放内存。而普通成员变量在对象创建时分配内存，在对象销毁时释放内存。

static成员变量初始化不赋值会被默认初始化，一般是 0。静态数据区的变量都有默认的初始值，而动态数据区（堆区、栈区）的变量默认是垃圾值。

静态成员变量可以成为成员函数的可选参数，而普通成员变量不可以。

静态成员变量的类型可以是所属类的类型，但是普通成员变量不行。普通成员只能声明为所属类类型的指针或引用。

在C++中，我们可以使用静态成员变量来实现多个对象共享数据的目标。静态成员变量是一种特殊的成员变量，它被关键字static修饰，例如：
//  static 成员变量属于类，不属于某个具体的对象，即使创建多个对象，也只为 static 成员变量 分配一份内存，所有对象使用的都是这份内存中的数据。当某个对象修改了 static 成员变量，也会影响到其他对象。
// static 成员变量必须在类声明的外部初始化.
// 静态成员变量在初始化时不能再加 static，但必须要有数据类型。被 private、protected、public 修饰的静态成员变量都可以用这种方式初始化。
// 注意：static 成员变量的内存既不是在声明类时分配，也不是在创建对象时分配，而是在（类外）初始化时分配。反过来说，没有在类外初始化的 static 成员变量不能使用。
// 注意：static 成员变量不占用对象的内存，而是在所有对象之外开辟内存，即使不创建对象也可以访问。具体来说，static 成员变量和普通的 static 变量类似，都在内存分区中的全局数据区分配内存。
//  static 成员变量既可以通过对象来访问，也可以通过类来访问
// 1) 一个类中可以有一个或多个静态成员变量，所有的对象都共享这些静态成员变量，都可以引用它。
//  2) static 成员变量和普通 static 变量一样，都在内存分区中的全局数据区分配内存，到程序结束时才释放。这就意味着，static 成员变量不随对象的创建而分配内存，也不随对象的销毁而释放内存。而普通成员变量在对象创建时分配内存，在对象销毁时释放内存。
// 3) 静态成员变量必须初始化，而且只能在类体外进行。例如： int Student::m_total = 10;
// 初始化时可以赋初值，也可以不赋值。如果不赋值，那么会被默认初始化为 0。全局数据区的变量都有默认的初始值 0，而动态数据区（堆区、栈区）变量的默认值是不确定的，一般认为是垃圾值。
// 4) 静态成员变量既可以通过对象名访问，也可以通过类名访问，但要遵循 private、protected 和 public 关键字的访问权限限制。当通过对象名访问时，对于不同的对象，访问的是同一份内存。
//
//


2.静态成员函数

注意下面几点：

普通成员函数可以访问所有成员变量，而静态成员函数只能访问静态成员变量。

调用一个对象的非静态成员函数时，系统会把当前对象的起始地址赋给 this 指针。而静态成员函数并不属于某一对象，它与任何对象都无关，因此静态成员函数没有 this 指针。

静态成员函数与非静态成员函数的根本区别是：有无this指针。由此决定了静态成员函数不能访问本类中的非静态成员。

如果类的成员函数想作为回调函数来使用，一般情况下只能将它定义为静态成员才行。

*****************************************************************************/



/*****************************************************************************
定义某个类 A
*****************************************************************************/
class A{
    public:
        A(int a);
        static void printaa();//静态成员函数
        void  printbb();
    private:
        static int aa;//静态数据成员的声明
        static const int count;//常量静态数据成员（可以在构造函数中初始化）
        const int bb;//常量数据成员
};



/*****************************************************************************
定义某个类 Student
*****************************************************************************/



class Student{
    public:
        Student(char *name, int age, float score);
        void show(void);
        void setAge(int age);
        void showRealAge(void);
        int realAge;

    private:
        static int m_total;  //静态成员变量

    private:
        char *m_name;
        int m_age;
        float m_score;
};



/*****************************************************************************
定义某个类 Stamp
*****************************************************************************/

//返回北京时间
void GetTimeOfNow(char * G);

class Stamp{
    private:
        char value[128];
        static const vector<string> Wday;//  = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        static const int AA;

    public:
        Stamp();
        virtual  ~Stamp();
        void  ShowWday(void);
        const char* GetStartTime(void) const;
};



/*****************************************************************************
(一 )   测试public, private, protected
一般地，在类的内部，无论成员被声明为哪种，都是可以互相访问的；但在类的外部，如通过类的对象，则只能访问 public 属性的成员，不能访问protected、private属性的成员。
public：可以被该类中的函数、子类的函数、友元函数访问，也可以由该类的对象访问；
protected：可以被该类中的函数、子类的函数、友元函数访问，但不可以由该类的对象访问；
private：可以被该类中的函数、友元函数访问，但不可以由子类的函数、该类的对象、访问。

private：用来指定私有成员。一个类的私有成员，不论是成员变量还是成员函数，都只能在该类的成员函数内部才能被访问。

public：用来指定公有成员。一个类的公有成员在任何地方都可以被访问。

protected：用来指定保护成员。这需要等介绍“继承”之后再解释。

三种关键字出现的次数和先后次序都没有限制。成员变量的可访问范围由离它前面最近的那个访问范围说明符决定。

如果某个成员前面没有访问范围说明符，则对 class 来说，该成员默认地被认为是私有成员；对 struct 来说，该成员默认地被认为是公有成员。

注意事项
如果声明不写 public、protected、private，则默认为 private；
声明public、protected、private的顺序可以任意；
在一个类中，public、protected、private 可以出现多次，每个限定符的有效范围到出现另一个限定符或类结束为止。但为了使程序清晰，应该使每种限定符只出现一次。



(二)   const成员函数（常成员函数）:
    //  const 成员函数可以使用类中的所有成员变量，但是不能修改它们的值，这种措施主要还是为了保护数据而设置的。const 成员函数也称为常成员函数。
    // 常成员函数需要在声明和定义的时候在函数头部的结尾加上 const 关键字，
    // 最后再来区分一下 const 的位置：
    // 函数开头的 const 用来修饰函数的返回值，表示返回值是 const 类型，也就是不能被修改，例如const char * getname()。
    //  函数头部的结尾加上 const 表示常成员函数，这种函数只能读取成员变量的值，而不能修改成员变量的值，例如char * getname() const。




*****************************************************************************/



class CEmployee {
private:
    float Salary;  //工资
    int Age; //年纪

	int *arr_point;  //数组的首地址
	int arr_len;

public:
    char szName[30];  //字符数组创建，名字
    char* name;        // 字符指针创建，名字

public:
    CEmployee(){arr_point=NULL; arr_len=0;};
    CEmployee(const char  *szname, const char* nm, int age, float salary, int arr[], int arrlen);
    virtual  ~CEmployee();



    void setName(const char* name);
    // const成员函数（常成员函数）:
    void getName(char* name)  const;

    void setAge(int age);
    int getAge(void)  const;

    void setSalary(float salary);
    float getSalary(void)   const;

    void ShowEmployee(void);
    void averageSalary(CEmployee el, CEmployee e2);

    void showArray() const;
};




#endif // _TIME_CJJ