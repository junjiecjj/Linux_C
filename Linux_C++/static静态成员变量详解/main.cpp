
/*************************************************************************
>> File Name: test.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月27日 星期日 00时49分15秒

>> 此程序的功能是：
http://c.biancheng.net/view/2227.html#:~:text=%E5%9C%A8%20C%2B%2B%20%E4%B8%AD%EF%BC%8C%E6%88%91%E4%BB%AC%E5%8F%AF%E4%BB%A5%E4%BD%BF%E7%94%A8%E9%9D%99%E6%80%81%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F%E6%9D%A5%E5%AE%9E%E7%8E%B0%E5%A4%9A%E4%B8%AA%E5%AF%B9%E8%B1%A1%E5%85%B1%E4%BA%AB%E6%95%B0%E6%8D%AE%E7%9A%84%E7%9B%AE%E6%A0%87%E3%80%82.%20%E9%9D%99%E6%80%81%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F%E6%98%AF%E4%B8%80%E7%A7%8D%E7%89%B9%E6%AE%8A%E7%9A%84%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F%EF%BC%8C%E5%AE%83%E8%A2%AB%E5%85%B3%E9%94%AE%E5%AD%97%20static%20%E4%BF%AE%E9%A5%B0,%EF%BC%8C%E4%BE%8B%E5%A6%82%EF%BC%9A.%20%E8%BF%99%E6%AE%B5%E4%BB%A3%E7%A0%81%E5%A3%B0%E6%98%8E%E4%BA%86%E4%B8%80%E4%B8%AA%E9%9D%99%E6%80%81%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F%20m_total%EF%BC%8C%E7%94%A8%E6%9D%A5%E7%BB%9F%E8%AE%A1%E5%AD%A6%E7%94%9F%E7%9A%84%E4%BA%BA%E6%95%B0%E3%80%82.%20static%20%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F%E5%B1%9E%E4%BA%8E%E7%B1%BB%EF%BC%8C%E4%B8%8D%E5%B1%9E%E4%BA%8E%E6%9F%90%E4%B8%AA%E5%85%B7%E4%BD%93%E7%9A%84%E5%AF%B9%E8%B1%A1%EF%BC%8C%E5%8D%B3%E4%BD%BF%E5%88%9B%E5%BB%BA%E5%A4%9A%E4%B8%AA%E5%AF%B9%E8%B1%A1%EF%BC%8C%E4%B9%9F%E5%8F%AA%E4%B8%BA%20m_total%20%E5%88%86%E9%85%8D%E4%B8%80%E4%BB%BD%E5%86%85%E5%AD%98%EF%BC%8C%E6%89%80%E6%9C%89%E5%AF%B9%E8%B1%A1%E4%BD%BF%E7%94%A8%E7%9A%84%E9%83%BD%E6%98%AF%E8%BF%99%E4%BB%BD%E5%86%85%E5%AD%98%E4%B8%AD%E7%9A%84%E6%95%B0%E6%8D%AE%E3%80%82.

************************************************************************/



#include <iostream>
using namespace std;
#include "TestDefine.h"
#include "RamDef.h"
#include "RamDefLib.h"
#include "Function.h"



int main(int argc, char* argv[]){
    GetTimeOfNow(Time);

    printf("通过Stamp类获取的时间为:%s\n",stamp.GetStartTime());
    printf("通过C语言函数类获取的时间为:%s\n",Time);


    /********************************************************************************
     * 1 A
    ********************************************************************************/
     printf("\n\n***************************  测试 A类   *******************************************\n\n");
    A a(10);
    A::printaa();//通过类访问静态成员函数
    a.printaa();//通过对象访问静态成员函数
    a.printbb();


    /********************************************************************************
     * 2 Student
    ********************************************************************************/
    printf("\n\n***************************  测试 Student  类   *******************************************\n\n");
    //创建匿名对象
    (new Student("小明", 15, 90)) -> show();
    (new Student("李磊", 16, 80)) -> show();
    (new Student("张华", 16, 99)) -> show();
    (new Student("王康", 14, 60)) -> show();


    Student xiaoming =  Student("小明", 15, 90);
    xiaoming.show();

    Student lilei = Student("李磊", 16, 80);
    lilei.show();

    Student hua = Student("张华", 16, 99);
    hua.show();

    // Student kang = Student("王康", 14, 60);  kang放在了Ramdef中定义
    kang.show();
    ChangeStu(&kang);
    kang.showRealAge();

    /********************************************************************************
     * 3 CEmployee
    ********************************************************************************/
    printf("\n\n***************************  测试 CEmployee类   *******************************************\n\n");

    int *x=new int[5];
	for (int i=0; i<5; ++i)
		x[i]=i+1;

    CEmployee E("jack", "junjie", 28, 123.212,  x, 5);
    E.ShowEmployee();

    strcpy(E.szName, "Tom1234567889");  //ok
    E.ShowEmployee();

    E.setName("Tom1234");  //ok
    E.ShowEmployee();

    E.setAge(38);  //ok
    E.ShowEmployee();

    E.setSalary(328.8126);  //ok
    E.ShowEmployee();

    char  name[20];
    E.getName(name);

    char *nameP  = nullptr;
    const int   namelen  =  20;
    nameP  =  (char*)malloc(sizeof(char)*namelen);
    E.getName(nameP);

    int age = 0;
    age = E.getAge();

    float salar  =  0;
    salar =   E.getSalary();

    printf("姓名:%s,  年龄:%d,  薪资:%.3f\n",nameP,age, salar);
    printf("姓名:%s,  年龄:%d,  薪资:%.3f\n",name,age, salar);


    //  E.Salary = 5000;  //编译出错，不能访问私有成员

    // array


	E.showArray();   // 输出1 2 3 4 5
	x[3]=999;
	E.showArray();   // 输出1 2 3 4 5, arr使用专属的存储空间！
	delete [] x;
	E.showArray();   // 输出1 2 3 4 5, arr使用专属的存储空间！！


    return 0;
}