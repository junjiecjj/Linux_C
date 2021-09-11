/*************************************************************************
>> File Name: 打气球的最大分数.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2019年09月20日
************************************************************************/

#include<bits/stdc++.h>
using namespace std;


int main(int argc, char *argv[])
{
    int n;
    scanf("%d",&n);
    vector<int> arr(n+2,1);
    for(int i=1; i<=n; ++i)
    {
        cin>>arr[i];
    }

    vector<vector<int>> dp(n+2, vector<int>(n+2,0));
    for(int i=1; i<=n; ++i)
    {
        dp[i][i] = arr[i-1]*arr[i]*arr[i+1];
    }

    for(int L=n; L>=1; --L)
    {
        for(int R=L+1; R<=n; ++R)
        {
            int finalL = arr[L-1]*arr[L]*arr[R+1]+dp[L+1][R];
            int finalR = arr[L-1]*arr[R]*arr[R+1]+dp[L][R-1];
            dp[L][R] = max(finalL, finalR);
            for(int i=L+1; i<=R-1;++i)
            {
                dp[L][R] = max(dp[L][R],arr[L-1]*arr[i]*arr[R+1]+dp[L][i-1]+dp[i+1][R]);
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}
