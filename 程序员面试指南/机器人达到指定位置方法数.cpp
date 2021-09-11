/*************************************************************************
>> File Name: 机器人达到指定位置方法数.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2019年09月14日
************************************************************************/
/*
题目描述
假设有排成一行的N个位置，记为1~N，开始时机器人在M位置，机器人可以往左或者往右走，如果机器人在1位置，
那么下一步机器人只能走到2位置，如果机器人在N位置，那么下一步机器人只能走到N-1位置。
规定机器人只能走k步，最终能来到P位置的方法有多少种。由于方案数可能比较大，所以答案需要对1e9+7取模。
输入描述:
输出包括一行四个正整数N（2<=N<=5000）、M(1<=M<=N)、K(1<=K<=5000)、P(1<=P<=N)。
输出描述:
输出一个整数，代表最终走到P的方法数对10^9+7取模后的值。
示例1
输入:
5 2 3 3
输出:
3
*/


#include<bits/stdc++.h>
using namespace std;
int mod = 1e9+7;

void show(int m,  int (*M)[10])
{
    for(int i = 0; i < m; ++i)
    {
        for(int j=0; j < 10; ++j)
        {
            printf("%d  ",M[i][j]);
        }
        printf("\n");
    }
}


int walk1(int N, int cur, int rest, int p)
{
    //N：一共N个位置
    //cur：当前位置
    //rest：剩下步数
    //p：目标位置
    
    if(rest==0)
        return cur==p ? 1:0;
    if(cur == 1)
        return walk1(N, 2, rest-1, p);
    if(cur == N)
        return walk1(N, N-1, rest-1, p);
    return walk1(N, cur-1, rest-1,p) + walk1(N, cur+1, rest-1, p);
}

int walk2(int N, int Cur, int Rest, int P)
{
    vector<vector<int>> dp(Rest+1, vector<int>(N+1,0));
    dp[0][P] = 1;
    for(int rest=1; rest<=Rest; ++rest)
    {
        for(int  cur=1; cur <= N; ++cur)
        {
            if(cur==1)
            {
                dp[rest][cur] = dp[rest-1][2]%mod;
            }
            else if(cur == N)
            {
                dp[rest][cur] = dp[rest-1][N-1];
            }
            else
            {
                dp[rest][cur] = dp[rest-1][cur-1]+dp[rest-1][cur+1];
            }   
        }
    }
    return dp[Rest][Cur];
}

int walk3(int N, int Cur, int Rest, int P)
{
    vector<int> dp(N+1,0);
    dp[P] = 1;
    for(int rest=1; rest<=Rest; ++rest)
    {
        int upleft = dp[1];
        for(int cur=1; cur <= N; ++cur)
        {
            int tmp = dp[cur];
            if(cur==1)
            {
                dp[cur] = dp[2]%mod;
            }
            else if(cur == N)
            {
                dp[cur] = upleft%mod;
            }
            else
            {
                dp[cur] = (upleft+dp[cur+1])%mod;
            }
            upleft = tmp;
        }
    }
    return dp[Cur]%mod;
}



int main(int argc, char *argv[])
{
    int N,M,K,P;
    scanf("%d %d %d %d",&N, &M, &K, &P);
    if(N<2 || M>N || K>5000 || P>N)
        return 0;
    printf("%d",walk3(N ,M , K, P));
    return 0;
}
