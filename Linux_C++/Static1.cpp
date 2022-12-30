/*************************************************************************
>> File Name: test.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月27日 星期日 00时49分15秒

>> 此程序的功能是：
https://www.runoob.com/w3cnote/cpp-static-const.html
************************************************************************/





#include<bits/stdc++.h>
#include<cstdio>
#include<ctime>
using namespace std;


class A{
    public:
        A(int a);
        static void print();//静态成员函数
        void  printbb();
    private:
        static int aa;//静态数据成员的声明
        static const int count;//常量静态数据成员（可以在构造函数中初始化）
        const int bb;//常量数据成员
};

int A::aa=0;//静态成员的定义+初始化
const int A::count=25;//静态常量成员定义+初始化

A::A(int a):bb(a){//常量成员的初始化
    aa+=1;
}

void A::print(){
    cout<<"count="<<count<<endl;
    cout<<"aa="<<aa<<endl;
    // cout<<"bb="<<bb<<endl;
}

void A::printbb(){
    cout<<"bb="<<bb<<endl;
}


int main(){
    A a(10);
    A::print();//通过类访问静态成员函数
    a.print();//通过对象访问静态成员函数
    a.printbb();

    return 0;
}