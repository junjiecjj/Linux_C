/*************************************************************************
>> File Name: 最大乘机.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.04.08

题目描述
给定一个无序数组，包含正数、负数和0，要求从中找出3个数的乘积，使得乘积最大，要求时间复杂度：O(n)，空间复杂度：O(1)
输入描述:
数组大小:n
无序整数数组A[n]
输出描述:
满足条件的最大乘积
************************************************************************/

#include<iostream>
using namespace std;
#include<climits>

int main(int argc,char *argv[])
{
    int n;
    cin >> n;
    long long max1 = INT_MIN;
    long long max2 = INT_MIN;
    long long max3 = INT_MIN;
    long long min1 = INT_MAX;
    long long min2 = INT_MAX;

    long long num;

    for(int i = 0; i < n; ++i)
    {
        cin >> num;

        if(num < min1)
        {
            min2 = min1;
            min1 = num;
        }
        else if(num < min2)
        {
            min2 = num;
        }

        if(num > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if(num > max2)
        {
            max3 = max2;
            max2 = num;
        }
        else if(num > max3)
        {
            max3 = num;
        }
    }
    cout << max(max1*max2*max3, max1*min1*min2) << endl;
    return 0;
}
