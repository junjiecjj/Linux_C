
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
class Student{
public:
    Student(char *name, int age, float score);
    void show();
private:
    static int m_total;  //静态成员变量
private:
    char *m_name;
    int m_age;
    float m_score;
};
//初始化静态成员变量
int Student::m_total = 0;
Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){
    m_total++;  //操作静态成员变量
}
void Student::show(){
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<"（当前共有"<<m_total<<"名学生）"<<endl;
}
int main(){
    //创建匿名对象
    (new Student("小明", 15, 90)) -> show();
    (new Student("李磊", 16, 80)) -> show();
    (new Student("张华", 16, 99)) -> show();
    (new Student("王康", 14, 60)) -> show();
    return 0;
}