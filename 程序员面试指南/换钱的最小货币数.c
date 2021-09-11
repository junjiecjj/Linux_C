/*************************************************************************
>> File Name: 换钱的最小货币数.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
# Created Time: Fri 13 Sep 2019 04:46:47 PM CST
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<string.h>
#include<sys/socket.h>
#include<stddef.h>
#include<locale.h>
#include<time.h>
#include<complex.h>

void show(int *A, int n)
{
    printf("打印数组\n");
    for(int i=0; i < n; ++i)
    {
        printf("%-4d ",A[i]);
    }
    printf("\n\n");
}

int main(int argc, char *argv[])
{
    int n,aim;
    n = aim = 0;
    int a[1000] = {0};
    int maxnum = 5001;
    int dp[5000];
    scanf("%d%d",&n,&aim);
    for(int i = 0;i < n;i++)
    {
        scanf("%d",&a[i]);
    }
    show(a, n);
    for(int i = 0;i <= aim;i++)
    {
        dp[i] = maxnum;
    }
    dp[0] = 0;
    show(dp, aim);
    for (int i = 0;i < n;i++)
    {
        for(int j = a[i];j <= aim;j++)
        {
            if(dp[j - a[i]] + 1 < dp[j])
            {
                dp[j] = dp[j - a[i]] + 1;
            }
        }
        show(dp, aim);
    }

    if(dp[aim] == maxnum)
    {
       printf("-1");
    }
    else
    {
       printf("%d",dp[aim]);
    }

    return 0;
}

