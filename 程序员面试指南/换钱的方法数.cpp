/*************************************************************************
>> File Name: 换钱的方法数.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2019年09月14日
************************************************************************/

#include<bits/stdc++.h>
using namespace std;


int main(int argc, char *argv[])
{
    int n, aim;
    scanf("%d %d",&n, &aim);
    int *arr = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i)
    {
        scanf("%d",arr+i);
    }

    int M = 1e9+7;

    int *dp = (int *)malloc((aim+1)*sizeof(int));

    for(int i = 0; i < aim+1; ++i)
    {
        dp[i] = 0;
    }

    dp[0] = 1;

    for(int i = 0; i < n; ++i)
    {
        for(int j = arr[i]; j <= aim; ++j)
        {
            dp[j] = (dp[j] + dp[j - arr[i]])%M;
        }
    }

    printf("%d",dp[aim]);

    return 0;
}

