/*************************************************************************
>> File Name: 小招喵跑步.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.11
************************************************************************/

#include<iostream>
using namespace std;
#define MIN(x,y) ( x<y? x : y)

int get(int N)
{
    if(N < 4)
        return N;
    if(N % 2 == 0)
    {
        return 1 + get(N/2);
    }
    else
    {
        int a = 1 + get(N+1);
        int b = 1 + get(N-1);
        return MIN(a,b);
    }
}


int main(int argc, char *argv[])
{
    int N;
    scanf("%d", &N);
    if(N < 0)
        N = -N;
    printf("%d\n", get(N));
    return 0;
}
