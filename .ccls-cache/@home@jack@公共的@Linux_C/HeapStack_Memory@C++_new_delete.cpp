/*************************************************************************
>> File Name: C++_new_delete.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月20日 星期六 18时41分46秒

>> 此程序的功能是：

https://mp.weixin.qq.com/s?__biz=MzUxMjEyNDgyNw==&mid=2247495988&idx=1&sn=2c6af247d80989d0e23c358407d73397&chksm=f96b83c0ce1c0ad6531675a30396cc70ddbb6a377604890b82d92e98698706f9288095a8c87f&mpshare=1&scene=24&srcid=0716tozNVx1RXWxtCOPZTRCE&sharer_sharetime=1626407698049&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd


C++ 中使用 new 和 delete 从堆中分配和释放内存，new 和 delete 是运算符，不是函数，两者成对使用(后面说明为什么成对使用)。

new/delete 除了分配内存和释放内存（与 malloc/free），还做更多的事情，所有在 C++ 中不再使用 malloc/free 而使用 new/delete。

3.1 new 和 delete 使用
new 一般使用格式如下：

指针变量名 = new 类型标识符;
指针变量名 = new 类型标识符(初始值);
指针变量名 = new 类型标识符[内存单元个数];
在C++中new的三种用法包括：plain new， nothrow new 和 placement new。

plain new 就是我们最常使用的 new 的方式，在 C++ 中的定义如下：

void* operator new(std::size_t) throw(std::bad_alloc);
void operator delete( void *) throw();
plain new 在分配失败的情况下，抛出异常 std::bad_alloc 而不是返回 NULL，因此通过判断返回值是否为 NULL 是徒劳的。
************************************************************************/

#include<bits/stdc++.h>
using namespace std;


{
}

char *getMemory(unsigned long size)
{
    char * p = new char[size];
    return p;
}



int main(int argc, char *argv[])
{
    try{
        char * p = getMemory(1000000);    // 可能发生异常
        // ...
        delete [] p;
    }
    catch(const std::bad_alloc &amp; ex)
    {
        cout &lt;&lt; ex.what();
    }

    return 0;
}

/*
 * nothrow new 是不抛出异常的运算符new的形式。nothrow new在失败时，返回NULL。定义如下：

void * operator new(std::size_t, const std::nothrow_t&) throw();
void operator delete(void*) throw();*/
void func(unsinged long length)
{
    unsinged char * p = new(nothrow) unsinged char[length];
    // 在使用这种new时要加(nothrow) ，表示不使用异常处理 。

    if (p == NULL)  // 不抛异常，一定要检查
        cout << "allocte failed !";
        // ...
    delete [] p;
}

/*
 * placement new 意即“放置”，这种new允许在一块已经分配成功的内存上重新构造对象或对象数组。placement new不用担心内存分配失败，因为它根本不分配内存，它做的唯一一件事情就是调用对象的构造函数。定义如下：

void* operator new(size_t, void*);
void operator delete(void*, void*);
palcement new 的主要用途就是反复使用一块较大的动态分配的内存来构造不同类型的对象或者他们的数组。placement new构造起来的对象或其数组，要显示的调用他们的析构函数来销毁，千万不要使用delete。*/
void main1()
{
    using namespace std;
    char * p = new(nothrow) char [4];
    if (p == NULL)
    {
        cout << "allocte failed" << endl;
        exit( -1 );
    }
    // ...
    long * q = new (p) long(1000);
    delete []p;    // 只释放 p，不要用q释放。
}



/*
 * p 和 q 仅仅是首址相同，所构建的对象可以类型不同。所“放置”的空间应小于原空间，以防不测。当”放置new”超过了申请的范围，Debug 版下会崩溃，但 Release 能运行而不会出现崩溃！

该运算符的作用是：只要第一次分配成功，不再担心分配失败。*/
void main2()
{
    using namespace std;
    char * p = new(nothrow) char [100];
    if (p == NULL)
    {
        cout << "allocte failed" << endl;
        exit(-1);
    }
    long * q1 = new (p) long(100);
    // 使用q1  ...
    int * q2 = new (p) int[100/sizeof(int)];
    // 使用q2 ...
    ADT * q3 = new (p) ADT[100/sizeof(ADT)];
    // 使用q3  然后释放对象 ...
    delete [] p;    // 只释放空间，不再析构对象。
}

//注意：使用该运算符构造的对象或数组，一定要显式调用析构函数，不可用 delete 代替析构，因为 placement new 的对象的大小不再与原空间相同。

void main3()
{
    using namespace std;
    char * p = new(nothrow) char [sizeof(ADT)+2];
    if (p == NULL)
    {
        cout << "allocte failed" &lt;&lt; endl;
        exit(-1);
    }
    // ...
    ADT * q = new (p) ADT;
    // ...
    // delete q; // 错误
    q->ADT::~ADT();  // 显式调用析构函数，仅释放对象
    delete [] p;     // 最后，再用原指针来释放内存
}
/*
 * placement new 的主要用途就是可以反复使用一块已申请成功的内存空间。这样可以避免申请失败的徒劳，又可以避免使用后的释放。

特别要注意的是对于 placement new 绝不可以调用的 delete, 因为该 new 只是使用别人替它申请的地方。释放内存是 nothrow new 的事，即要使用原来的指针释放内存。free/delete 不要重复调用，被系统立即回收后再利用，再一次 free/delete 很可能把不是自己的内存释放掉，导致异常甚至崩溃。

上面提到 new/delete 比 malloc/free 多做了一些事情，new 相对于 malloc 会额外的做一些初始化工作，delete 相对于 free 多做一些清理工作。*/

class A
{
 public:
     A()
     {
        cont<<"A()构造函数被调用"<<endl;
     }
     ~A()
     {
        cont<<"~A()构造函数被调用"<<endl;
     }
}
//在 main 主函数中，加入如下代码：

A* pa = new A();  //类 A 的构造函数被调用
delete pa;        //类 A 的析构函数被调用
//可以看出：使用 new 生成一个类对象时系统会调用该类的构造函数，使用 delete 删除一个类对象时，系统会调用该类的析构函数。可以调用构造函数/析构函数就意味着 new 和 delete 具备针对堆所分配的内存进行初始化和释放的能力，而 malloc 和 free 不具备。

//2.2 delete 与 delete[] 的区别
//c++ 中对 new 申请的内存的释放方式有 delete 和 delete[] 两种方式，到底这两者有什么区别呢？

//我们通常从教科书上看到这样的说明：

// delete 释放 new 分配的单个对象指针指向的内存
// delete[] 释放 new 分配的对象数组指针指向的内存 那么，按照教科书的理解，我们看下下面的代码：
int *a = new int[10];
delete a;        //方式1
delete[] a;     //方式2
// 针对简单类型 使用 new 分配后的不管是数组还是非数组形式内存空间用两种方式均可 如：
int *a = new int[10];
delete a;
delete[] a;
// 此种情况中的释放效果相同，原因在于：分配简单类型内存时，内存大小已经确定，系统可以记忆并且进行管理，在析构时，系统并不会调用析构函数。

// 它直接通过指针可以获取实际分配的内存空间，哪怕是一个数组内存空间(在分配过程中 系统会记录分配内存的大小等信息，此信息保存在结构体 _CrtMemBlockHeader 中，具体情况可参看 VC 安装目录下 CRTSRCDBGDEL.cpp)。

// 针对类 Class，两种方式体现出具体差异,当你通过下列方式分配一个类对象数组：

class A
   {
    private:
      char *m_cBuffer;
      int m_nLen;

   `` public:
      A(){ m_cBuffer = new char[m_nLen]; }
      ~A() { delete [] m_cBuffer; }
   };

   A *a = new A[10];
   delete a;         //仅释放了a指针指向的全部内存空间 但是只调用了a[0]对象的析构函数 剩下的从a[1]到a[9]这9个用户自行分配的m_cBuffer对应内存空间将不能释放 从而造成内存泄漏
   delete[] a;      //调用使用类对象的析构函数释放用户自己分配内存空间并且   释放了a指针指向的全部内存空间
/*
 * 所以总结下就是，如果 ptr 代表一个用new申请的内存返回的内存空间地址，即所谓的指针，那么：

delete ptr  代表用来释放内存，且只用来释放 ptr 指向的内存。delete[] rg   用来释放rg指向的内存，！！还逐一调用数组中每个对象的destructor！！

对于像 int/char/long/int/struct 等等简单数据类型，由于对象没有 destructor ，所以用 delete 和 delete []是一样的！但是如果是 C++ 对象数组就不同了！

关于 new[] 和 delete[]，其中又分为两种情况：

(1) 为基本数据类型分配和回收空间；
(2) 为自定义类型分配和回收空间；
对于 (1)，上面提供的程序已经证明了 delete[] 和 delete 是等同的。但是对于 (2)，情况就发生了变化。

我们来看下面的例子，通过例子的学习了解 C++ 中的 delete 和 delete[] 的使用方法
*/

#include <iostream>
using namespace std;

class Babe
{
public:
    Babe()
    {
        cout << \"Create a Babe to talk with me\" << endl;
    }

    ~Babe()
    {
        cout << \"Babe don\'t Go away,listen to me\" << endl;
    }
};

int main()
{
    Babe* pbabe = new Babe[3];
    delete pbabe;
    pbabe = new Babe[3];
    delete[] pbabe;
    return 0;
}
/*
结果是:

Create a babe to talk with me
Create a babe to talk with me
Create a babe to talk with me
Babe don\'t go away,listen to me
Create a babe to talk with me
Create a babe to talk with me
Create a babe to talk with me
Babe don\'t go away,listen to me
Babe don\'t go away,listen to me
Babe don\'t go away,listen to me
大家都看到了，只使用 delete 的时候只出现一个 Babe don’t go away,listen to me，而使用 delete[] 的时候出现 3 个 Babe don’t go away,listen to me。不过不管使用 delete 还是 delete[] 那三个对象的在内存中都被删除，既存储位置都标记为可写，但是使用 delete 的时候只调用了 pbabe[0] 的析构函数，而使用了 delete[] 则调用了 3 个 Babe 对象的析构函数。

你一定会问，反正不管怎样都是把存储空间释放了，有什么区别。

答：关键在于调用析构函数上。此程序的类没有使用操作系统的系统资源（比如：Socket、File、Thread等），所以不会造成明显恶果。如果你的类使用了操作系统资源，单纯把类的对象从内存中删除是不妥当的，因为没有调用对象的析构函数会导致系统资源不被释放，这些资源的释放必须依靠这些类的析构函数。所以，在用这些类生成对象数组的时候，用 delete[] 来释放它们才是王道。而用 delete 来释放也许不会出问题，也许后果很严重，具体要看类的代码了。

*/

























