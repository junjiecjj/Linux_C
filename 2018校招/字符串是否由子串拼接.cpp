/*************************************************************************
>> File Name: 字符串是否由子串拼接.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.12
************************************************************************/

#include<iostream>
using namespace std;
#include<string>


int main(int argc, char *argv[])
{
    string str;
    cin >> str;
    unsigned long long len;
    string sub_str;

    for(len = str.size()-1; len > 0; len--)
    {
        if(str.size()%len != 0)
        {
            continue;
        }
        sub_str = str.substr(0, len);
        for(int start = len; start < str.size(); start += len)
        {
            if(sub_str != str.substr(start, len))
            {
                sub_str = "false";
                break;
            }
        }
        if(sub_str != "false")
            break;
    }

    cout << sub_str;

    return 0;
}
