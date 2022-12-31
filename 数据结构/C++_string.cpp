/*************************************************************************
>> File Name: 向量.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.03.17
************************************************************************/

#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>

void Show(const string S)
{
    auto it = S.begin();
    for (; it != S.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void show(const string S)
{
    cout << S << endl;
    cout << "\n\n";
}

int main(int argc, char *argv[])
{
    string S = "chen junjie!!!, hello";
    cout << "字符串S的元素个数为:" << S.size() << endl;
    cout << "字符串S的最大元素个数为:" << S.max_size() << endl;

    cout << "打印字符串\n";
    cout << S << endl;
    S.push_back('N');
    S.push_back('P');

    cout << "字符串不支持string.push_front\n" << endl;
    //S.push_front('M');                        //string不支持string.push_front()

    cout << "打印字符串\n";
    cout << S << endl;
    cout << "字符串最后的元素为:" << S.back() << endl;
    cout << "字符串开始的元素为:" << S.front() << endl;
    cout << "删除字符串S最后的元素:" << endl;
    S.pop_back();

    cout << "字符串不支持string.pop_front" << endl;
    //S.pop_front()            //string不支持string.pop_front()

    cout << "打印字符串\n";
    show(S);

    cout << "字符串第7个元素为:" << S.at(6) << endl;
    cout << "字符串第8个元素为:" << S[7] << endl;
    cout << "字符串是否为空,1为空，0为非空:" << S.empty() << endl;
    cout << "通过S.at(n)和S[n]改变S" << endl;
    S.at(7) = 'P';
    cout << S << endl;

    S[8] = 'Q';
    cout << S << endl;

    auto result = find(S.cbegin(), S.cend(), 'j');
    for (auto i = result; i != S.end(); i++)
        cout << *i;
    cout << endl;
    cout << "找到 'j' 了:" << *result << endl;

    cout << "反转并打印字符串\n";
    reverse(S.begin(), S.end());
    show(S);

    cout << "排序并打印字符串\n";
    sort(S.begin(), S.end());
    show(S);

    cout << "字符串求和\n";
    int sum = accumulate(S.begin(), S.end(), 0);
    cout << "字符串和为:" << sum << endl;

    cout << "清空字符串" << endl;
    S.clear();
    cout << S << endl;
    //cout << stoi(argv[1]) <<  endl;

    string S1 = "chen&jun&jie, hello!!!";
    string S2 = "I am fear@@@";
    const char *cp = "wang yin ##!";
    cout << "字符串S1:" << S1 << endl;
    cout << "字符串S2:" << S2 << endl;
    cout << "字符串cp:" << cp << endl;

    S1.insert(5, "dick , !");
    cout << "字符串S1:" << S1 << endl;

    S1.insert(5, S2, 0, 3);
    cout << "字符串S1:" << S1 << endl;

    S1.insert(5, cp, 6);
    cout << "字符串S1:" << S1 << endl;

    S1.insert(5, cp);
    cout << "字符串S1:" << S1 << endl;

    S1.insert(5, 3, '%');
    cout << "字符串S1:" << S1 << endl;

    S1.replace(5, 3, "*****");
    cout << "字符串S1:" << S1 << endl;

    S1.erase(5, 3);
    cout << "字符串S1:" << S1 << endl;

    int i = 1234;
    cout << "int : i = " << i << endl;

    string S3 = to_string(i);
    cout << "string S3 = " << S3 << endl;

    double d = stod(S3);
    cout << "double d = " << d << endl;

    double D = 12.1234;
    string s14 = to_string(D);
    cout << "D = " << D << endl;
    cout << "s14 = " << s14 << endl;

    char S4[20] = "hello world";
    char S5[20] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
    char S6[20] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    char S7[] = "hello\0 world";
    char S8[] = {'h', 'e', 'l', 'l', 'o', '\0', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
    char S9[] = {'h', 'e', 'l', 'l', 'o', '\0', ' ', 'w', 'o', 'r', 'l', 'd'};
    char S10[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'}; //strlen(S10)产生未定义的结果，因为S10不是以'\0'结尾，strlen可能一直向前查找直到遇到空字符
    const char *S11 = "hello world";

    string S12 = "hello world";
    string S13 = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    string S14 = "hello\0world";
    string S15 = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd'};

    printf("strlen(S4) = %zd , strlen(S5) = %zd , strlen(S6) = %zd , strlen(S7) = %zd , strlen(S8) = %zd , strlen(S9) = %zd , strlen(S10) = %zd , strlen(S11) = %zd\n", strlen(S4), strlen(S5), strlen(S6), strlen(S7), strlen(S8), strlen(S9), strlen(S10), strlen(S11));

    printf("sizeof(S4) = %zd , sizeof(S5) = %zd , sizeof(S6) = %zd , sizeof(S7) = %zd , sizeof(S8) = %zd, sizeof(S9) = %zd , sizeof(S10) = %zd , sizeof(S11) = %zd\n", sizeof(S4), sizeof(S5), sizeof(S6), sizeof(S7), sizeof(S8), sizeof(S9), sizeof(S10), sizeof(S11));

    //  strlen()只能以char *作为参数,不能以类型作为参数,该函数实际完成的功能是从代表该字符串的第一个地址开始遍历，直到遇到结束符'\0'。返回的长度大小不包括'\0'。
    //  c/c++ strlen(str)和str.length()和str.size()都可以求字符串长度。
    //  其中str.length()和str.size()是用于求string类对象长度的成员函数
    //  strlen(str)是用于求字符数组的长度，其参数是char*

    //cout << "strlen(S12) = " << strlen(S12) << endl;
    cout << "\nS12.size() = " << S12.size() << endl;
    cout << "S12.length() = " << S12.length() << endl;
    cout << "sizeof(S12) = " << sizeof(S12) << endl;

    //cout << "strlen(S13) = " << strlen(S13) << endl;
    cout << "\nS13.size() = " << S13.size() << endl;
    cout << "S13.length() = " << S13.length() << endl;
    cout << "sizeof(S13) = " << sizeof(S13) << endl;

    //cout << "strlen(S14) = " << strlen(S14) << endl;
    cout << "\nS14.size() = " << S14.size() << endl;
    cout << "S14.length() = " << S14.length() << endl;
    cout << "sizeof(S14) = " << sizeof(S14) << endl;

    //cout << "strlen(S15) = " << strlen(S15) << endl;
    cout << "\nS15.size() = " << S15.size() << endl;
    cout << "S15.length() = " << S15.length() << endl;
    cout << "sizeof(S15) = " << sizeof(S15) << endl;

    // 转换为C风格的字符串
    // 虽然 C++ 提供了 string 类来替代C语言中的字符串，但是在实际编程中，有时候必须要使用C风格的字符串（例如打开文件时的路径），为此，string 类为我们提供了一个转换函数 c_str()，该函数能够将 string 字符串转换为C风格的字符串，并返回该字符串的 const 指针（const char*）。请看下面的代码：
    string path = "./test.txt";
    FILE *fp = fopen(path.c_str(), "rt");
    fclose(fp);

    // string 字符串也可以像C风格的字符串一样按照下标来访问其中的每一个字符。string 字符串的起始下标仍是从 0 开始。请看下面的代码：
    string s = "1234567890";
    for(int i=0,len=s.length(); i<len; i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s[5] = '5';
    cout<<s<<endl;

    // 字符串的拼接
    //  有了 string 类，我们可以使用+或+=运算符来直接拼接字符串，非常方便，再也不需要使用C语言中的 strcat()、strcpy()、malloc() 等函数来拼接字符串了，再也不用担心空间不够会溢出了。

    //用+来拼接字符串时，运算符的两边可以都是 string 字符串，也可以是一个 string 字符串和一个C风格的字符串，还可以是一个 string 字符串和一个字符数组，或者是一个 string 字符串和一个单独的字符。请看下面的例子：
    string s1 = "first ";
    string s2 = "second ";
    char *s3 = "third ";
    char s4[] = "fourth ";
    char ch = '@';
    string s5 = s1 + s2;
    string s6 = s1 + s3;
    string s7 = s1 + s4;
    string s8 = s1 + ch;
    cout<<s5<<endl<<s6<<endl<<s7<<endl<<s8<<endl;


    //string 字符串的增删改查
    //一. 插入字符串
    //insert() 函数可以在 string 字符串中指定的位置插入另一个字符串，它的一种原型为：
    //string& insert (size_t pos, const string& str);

    //pos 表示要插入的位置，也就是下标；str 表示要插入的字符串，它可以是 string 字符串，也可以是C风格的字符串。
    string ss1, ss2, ss3;
    ss1 = ss2 = "1234567890";
    ss3 = "aaa";
    ss1.insert(5, ss3);
    cout<< ss1 <<endl;
    ss2.insert(5, "bbb");
    cout<< ss2 <<endl;

    // 二. 删除字符串
    // erase() 函数可以删除 string 中的一个子字符串。它的一种原型为：
    // string& erase (size_t pos = 0, size_t len = npos);

    // pos 表示要删除的子字符串的起始下标，len 表示要删除子字符串的长度。如果不指明 len 的话，那么直接删除从 pos 到字符串结束处的所有字符（此时 len = str.length - pos）。

    // 请看下面的代码：
    string sss1, sss2, sss3;
    sss1 = sss2 = sss3 = "1234567890";
    sss2.erase(5);
    sss3.erase(5, 3);
    cout<< sss1 <<endl;
    cout<< sss2 <<endl;
    cout<< sss3 <<endl;

    // 三. 提取子字符串
    // substr() 函数用于从 string 字符串中提取子字符串，它的原型为：
    // string substr (size_t pos = 0, size_t len = npos) const;

    // pos 为要提取的子字符串的起始下标，len 为要提取的子字符串的长度。
    // 系统对 substr() 参数的处理和 erase() 类似：
    // 如果 pos 越界，会抛出异常；
    // 如果 len 越界，会提取从 pos 到字符串结尾处的所有字符。
    // 请看下面的代码：
    string sa1 = "first second third";
    string sa2;
    sa2 = sa1.substr(6, 6);
    cout<< sa1 <<endl;
    cout<< sa2 <<endl;


    // 四. 字符串查找
    // string 类提供了几个与字符串查找有关的函数，如下所示。
    // 1) find() 函数
    // find() 函数用于在 string 字符串中查找子字符串出现的位置，它其中的两种原型为：
    // size_t find (const string& str, size_t pos = 0) const;
    // size_t find (const char* s, size_t pos = 0) const;

    // 第一个参数为待查找的子字符串，它可以是 string 字符串，也可以是C风格的字符串。第二个参数为开始查找的位置（下标）；如果不指明，则从第0个字符开始查找。
    //find() 函数最终返回的是子字符串第一次出现在字符串中的起始下标。本例最终是在下标 6 处找到了 s2 字符串。如果没有查找到子字符串，那么会返回 string::npos，它是 string 类内部定义的一个静态常成员，用来表示 size_t 类型所能存储的最大值。
    // 请看下面的代码：
    string sq1 = "first second third";
    string sq2 = "second";
    int indexq = sq1.find(sq2,5);
    if(indexq < sq1.length())
        cout<<"Found at index : "<< indexq <<endl;
    else
        cout<<"Not found"<<endl;

    // 2) rfind() 函数
    // rfind() 和 find() 很类似，同样是在字符串中查找子字符串，不同的是 find() 函数从第二个参数开始往后查找，而 rfind() 函数则最多查找到第二个参数处，如果到了第二个参数所指定的下标还没有找到子字符串，则返回 string::npos。

    // 请看下面的例子：
    string sw1 = "first second third";
    string sw2 = "second";
    int indexw = sw1.rfind(sw2,6);
    if(indexw < sw1.length())
        cout<<"Found at index : "<< indexw <<endl;
    else
        cout<<"Not found"<<endl;


    // 3) find_first_of() 函数
    // find_first_of() 函数用于查找子字符串和字符串共同具有的字符在字符串中首次出现的位置。请看下面的代码：

    string se1 = "first second second third";
    string se2 = "asecond";
    int indexe = se1.find_first_of(se2);
    if(indexe < se1.length())
        cout<<"Found at index : "<< indexe <<endl;
    else
        cout<<"Not found"<<endl;










    return 0;
}
/*
 输出为:

字符串S的元素个数为:21
字符串S的最大元素个数为:9223372036854775807
打印字符串
chen junjie!!!, hello
字符串不支持string.push_front

打印字符串
chen junjie!!!, helloNP
字符串最后的元素为:P
字符串开始的元素为:c
删除字符串S最后的元素:
字符串不支持string.pop_front
打印字符串
chen junjie!!!, helloN


字符串第7个元素为:u
字符串第8个元素为:n
字符串是否为空,1为空，0为非空:0
通过S.at(n)和S[n]改变S
chen juPjie!!!, helloN
chen juPQie!!!, helloN
juPQie!!!, helloN
找到 'j' 了:j
反转并打印字符串
Nolleh ,!!!eiQPuj nehc


排序并打印字符串
!!!,NPQceeehhijllnou


字符串求和
字符串和为:1821
清空字符串

字符串S1:chen&jun&jie, hello!!!
字符串S2:I am fear@@@
字符串cp:wang yin ##!
字符串S1:chen&dick , !jun&jie, hello!!!
字符串S1:chen&I adick , !jun&jie, hello!!!
字符串S1:chen&wang yI adick , !jun&jie, hello!!!
字符串S1:chen&wang yin ##!wang yI adick , !jun&jie, hello!!!
字符串S1:chen&%%%wang yin ##!wang yI adick , !jun&jie, hello!!!
字符串S1:chen&*****wang yin ##!wang yI adick , !jun&jie, hello!!!
字符串S1:chen&**wang yin ##!wang yI adick , !jun&jie, hello!!!
int : i = 1234
string S3 = 1234
double d = 1234
D = 12.1234
s14 = 12.123400
strlen(S4) = 11 , strlen(S5) = 11 , strlen(S6) = 11 , strlen(S7) = 5 , strlen(S8) = 5 , strlen(S9) = 5 , strlen(S10) = 16 , strlen(S11) = 11
sizeof(S4) = 20 , sizeof(S5) = 20 , sizeof(S6) = 20 , sizeof(S7) = 13 , sizeof(S8) = 13, sizeof(S9) = 12 , sizeof(S10) = 11 , sizeof(S11) = 8
S12.size() = 11
S12.length() = 11
sizeof(S12) = 32
S13.size() = 11
S13.length() = 11
sizeof(S13) = 32
S14.size() = 5
S14.length() = 5
sizeof(S14) = 32
S15.size() = 11
S15.length() = 11
sizeof(S15) = 32

*/
