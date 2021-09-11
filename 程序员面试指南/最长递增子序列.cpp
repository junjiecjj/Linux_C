/*************************************************************************
>> File Name: 最长递增子序列.cpp
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2019年09月21日
************************************************************************/

#include<bits/stdc++.h>
using namespace std;



void getList(vector<int>&nums, vector<int>&dp)
{////////获取最小  最长递增子序列
    int iSize = dp.size();
    if (0 == iSize)
        return;
    cout.sync_with_stdio(false);
    int len = 0;
    int index = 0;
    for (int i = 0; i < iSize; i++)
    {
        if (dp[i] >= len)
        {
            len = dp[i];
            index = i;
        }
    }
    vector<int>vret(len, 0);
    for (int i = index; i >= 0;)
    {
        int itemp = nums[i];
        if (dp[i] == len)
        {
            while (i>=0&&dp[i] == len)
            {
                itemp = itemp < nums[i] ? itemp : nums[i];
                i--;
            }
            vret[--len] = itemp;
        }
        else
            i--;
        /*if (nums[i] < nums[index] && dp[i] == dp[index] - 1)
        {
            vret[--len] = nums[i];
            index = i;
        }*/
    }
    iSize = vret.size();
    for (int i = 0; i < iSize; i++)
        cout << vret[i] << " ";
    cout << endl;
    return;
}

void maxLengthdp2(vector<int>&nums)
{/////时间复杂度O(nlgn),空间复杂度O(n)
    int iSize = nums.size();
    if (0 == iSize)
        return;
    vector<int>dp(iSize, 1);
    vector<int>vend(iSize, 1);
    vend[0] = nums[0];
    int l = 0;
    int r = 0;
    int m = 0;
    int iright = 0;
    for (int i = 1; i < iSize; i++)
    {
        l = 0;
        r = iright;
        while (l <= r)
        {
            m = (l + r) >> 1;
            if (nums[i] > vend[m])
                l = m + 1;
            else
                r = m - 1;
        }
        iright = max(iright, l);
        vend[l] = nums[i];
        dp[i] = l + 1;

        printf("iright = %d\n",iright);

        printf("Vend is:\n");
        for(int k=0; k< iSize; ++k)
        {
            printf("%5d",vend[k]);
        }
        printf("  V  \ndp is:\n");
        for(int k=0; k< iSize; ++k)
        {
            printf("%5d",dp[k]);
        }
        printf("  D  \n\n\n");
    }
    getList(nums, dp);
    return;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        if (n < 1)
            continue;
        vector<int>nums(n, 0);
        for (int i = 0; i < n; i++)
            cin >> nums[i];
        maxLengthdp2(nums);
        //cout << maxLengthdp1(nums) << endl;
    }
    return 0;
}
