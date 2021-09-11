/*************************************************************************
>> File Name: 拼凑硬币.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
# Created Time: Sat 07 Sep 2019 02:49:51 PM CST
************************************************************************/

#include<bits/stdc++.h>
using namespace std;
map<long,long> m;

long solve(long n)
{
    if(m.count(n))
        return m[n];

    long count = 0;

    if((n&1) != 1)
        count = solve(n>>1) + solve((n>>1) - 1);
    else
        count = solve(n >> 1);
    m[n] = count;
    return count;
}

int main(int argc,char *argv[])
{
    m[0] = 1;
    m[1] = 1;
    long n;
    scanf("%ld",&n);
    printf("%ld",solve(n));
    //cout << solve(n) << endl;
    return 0;
}

