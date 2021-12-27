/*************************************************************************
>> File Name: 背包问题.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月27日 星期一 12时26分31秒

>> 此程序的功能是：
************************************************************************/

#include<bits/stdc++.h>
using namespace std;


int main(int argc, char *argv[])
{
    int n,c,w[1001],v[1001];
    int dp[1001][1001];
    cin>>n>>c;
    for(int i=1;i<=n;i++)
        cin>>w[i]>>v[i];
    for(int i=1;i<=n;i++) //物品
    {
        for(int j=1;j<=c;j++)  //从一枚举到C
        {
            if(j>=w[i])
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);  //最大值
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    cout<<dp[n][c]<<endl;//n个物品，背包空间为c的dp值
}
