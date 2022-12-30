/*************************************************************************
>> File Name: test.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年06月27日 星期日 00时49分15秒

>> 此程序的功能是：
https://www.runoob.com/w3cnote/cpp-static-const.html
************************************************************************/






#include "TestDefine.h"


//==========================================================================================================================================
// A 类
//==========================================================================================================================================
int A::aa=0;//静态成员的定义+初始化
const int A::count=25;//静态常量成员定义+初始化

A::A(int a):bb(a){//常量成员的初始化
    aa+=1;
}

void A::printaa(){
    cout<<"count="<<count<<endl;
    cout<<"aa="<<aa<<endl;
    // cout<<"bb="<<bb<<endl;
}

void A::printbb(){
    cout<<"bb="<<bb<<endl;
}


//==========================================================================================================================================
// Student 类
//==========================================================================================================================================
//初始化静态成员变量
int Student::m_total = 0;



//本例中将 m_total 声明为静态成员变量，每次创建对象时，会调用构造函数使 m_total 的值加 1。
Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){
    m_total++;  //操作静态成员变量
}
void Student::show(){
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<"（当前共有"<<m_total<<"名学生）"<<endl;
}

void Student::setAge(int age) {
    m_age = age;  //ok
}

void Student::showRealAge(void){
    printf("%s的真实年龄为%d\n",m_name,realAge);
}


//==========================================================================================================================================
// GetTimeOfNow 函数
//==========================================================================================================================================


void GetTimeOfNow(char * GlobalTime)
{

    char *Wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    time_t Timep;
    struct tm *P;
    //char Time[255];
    time(&Timep);
    P = localtime(&Timep);
    sprintf(GlobalTime, "%d/%d/%d %s %02d:%02d:%02d",(1900+P->tm_year), (1+P->tm_mon), P->tm_mday, Wday[P->tm_wday], P->tm_hour, P->tm_min, P->tm_sec);

    //return GlobalTime;
}

//==========================================================================================================================================
// Stamp类
//==========================================================================================================================================
const int Stamp::AA = 48271;
// const vector<string> Stamp::Wday = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};


const vector<string>  Stamp::Wday = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

//构造函数
Stamp::Stamp(){
    // const vector<string>  Wday1 = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    time_t Timep;
    struct tm *P;
    time(&Timep);
    P = localtime(&Timep);
    sprintf(value, "%d/%d/%d %s %02d:%02d:%02d",(1900+P->tm_year), (1+P->tm_mon), P->tm_mday, Wday[P->tm_wday].c_str(), P->tm_hour, P->tm_min, P->tm_sec);
    //sprintf(value, "%s", ctime(&now));
}

// 析构函数
Stamp::~Stamp()
{

}

void Stamp::ShowWday(void)
{
    for(int i=0; i<Wday.size(); ++i){
        printf("Wday[%d] = %s\n",i, Wday[i].c_str());
    }
}


const char*  Stamp::GetStartTime(void) const {return value;}

//==========================================================================================================================================

//==========================================================================================================================================
// CEmployee 类
//==========================================================================================================================================
//构造函数
// CEmployee::CEmployee()
// {
//     arr_point=NULL; arr_len=0;
// }

CEmployee::CEmployee(const char *szname,  const char* nm,  int age, float salary, int arr[], int arrlen)
{
    strcpy(m_szName,  szname);

    // m_name = new char[strlen(nm) + 1];  //成员变量是指针，所以应该用new来分配内存，+1是因为有结束标志符,  ok
    m_name = (char *) malloc(strlen(nm) + 1);
    strcpy(m_name, nm);

    m_Age = age;
    m_Salary  =  salary;

    //  在C++中，当类中有指针类型的数据成员时，必须注意在构造函数中，分配专门的存储单元，并将地址赋值给指针型数据成员。
    // https://blog.csdn.net/sxhelijian/article/details/7492646
	m_arr_point=new int[arrlen];  //arr_point指向了属于自己的新空间
	for (int i=0; i<arrlen; ++i)
		*(m_arr_point+i)=*(arr+i);   //将数组a中元素逐个赋值
	m_arr_len=arrlen;
}

// 析构函数
// 如果一个类中有指针类型的成员变量，就要在构造函数中new动态分配内存，也需要在析构函数中delete释放内存.
CEmployee::~CEmployee()
{
    //  delete[] m_name;    // ok
    free(m_name);


	if (!m_arr_point) // 等同于if (arr_point!=NULL)
		delete [] m_arr_point; //释放在类的生命周期中分配的，arr_point指向的空间

    // delete  删除的是 指针原本所指的那部分内存而已 指针还可以使用 但是避免野指针
    // delete命令指示释放了那个指针原本所指的那部分内存而已。被delete后的指针p的值（地址值）并非就是NULL，而是随机值。
    //  也就是被delete后，如果不再加上一句p=NULL，p就成了“野指针”，在内存里乱指一通。
}



void CEmployee::setName(const char* name) {
    strcpy(m_szName, name);  //ok
}
void CEmployee::getName(char* name) const{
    strcpy(name, m_szName);  //ok
}

void CEmployee::setAge(int age) {
    m_Age = age;  //ok
}
int CEmployee::getAge(void) const{
    return m_Age;  //ok
}

void CEmployee::setSalary(float salary) {
    m_Salary = salary;  //ok
}
float CEmployee::getSalary(void) const{
    return m_Salary;  //ok
}

void CEmployee::ShowEmployee(void)
{
    printf("外号:%s(真名:%s) 的工资为%.3f, 年龄为:%d\n",m_szName, m_name, m_Age, m_Salary );
}

void CEmployee::averageSalary(CEmployee el, CEmployee e2)
{
    m_Salary = (el.m_Salary + e2.m_Salary) / 2;
}


void CEmployee::showArray() const
{
	for (int i=0; i<m_arr_len; ++i)
		cout<<*(m_arr_point+i)<<' '; //或cout<<arr_point[i]<<' '
	cout<<endl;
	return;
}
