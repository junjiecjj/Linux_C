/*************************************************************************
>> File Name: 石子合并.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
# Created Time: Sun 08 Sep 2019 10:09:05 AM CST
************************************************************************/

#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstdlib>

using namespace std;

int main(int argc, char *arhv[])
{
    int N;
    scanf("%d",&N);
    int sum = 0;
    int res = 0;
    int t;
    for(int i=0; i < N; ++i)
    {
        scanf("%d",&t);
        res += sum*t;
        sum += t;
    }
    printf("%d\n",res);
    return 0;
}
