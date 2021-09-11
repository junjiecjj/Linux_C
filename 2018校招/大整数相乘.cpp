/*************************************************************************
>> File Name: 大整数相乘.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.04.08
题目描述
有两个用字符串表示的非常大的大整数,算出他们的乘积，也是用字符串表示。不能用系统自带的大整数类型。
输入描述:
空格分隔的两个字符串，代表输入的两个大整数
输出描述:
输入的乘积，用字符串表示
示例1
输入
72106547548473106236 982161082972751393
输出
70820244829634538040848656466105986748
************************************************************************/

#include<iostream>
using namespace std;
#include<string>



int main(int argc, char *argv[])
{
    string S1;
    string S2;

    cin >> S1 >> S2;
    cout << S1 << " " << S2 << endl;
    size_t l1 = S1.size();
    size_t l2 = S2.size();
    size_t l = l1 + l2;
    string res(l,'0');

    int takeover = 0;
    int offset = 0;
    size_t i = 1, j = 1;

    for(i = 1; i <= l2; ++i)
    {
        takeover = 0;
        int rightnum = S2[l2 - i] - '0';
        for(j = 1; j <= l1; ++j)
        {
            char bit = res[l - j - offset] - '0';
            int num = rightnum*(S1[l1-j]-'0') + takeover + bit;
            takeover = num/10;
            res[l - j - offset] = num%10 + '0';
        }
        if(takeover != 0)
            res[l - j - offset] = takeover + '0';
        offset++;
    }
    if(res[0] == '0')
        res.erase(0,1);
    cout << res;
    return 0;
}
