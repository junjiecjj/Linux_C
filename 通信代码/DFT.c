/*************************************************************************
>> File Name: DFT.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
 
>> Created Time: 2021年02月05日 星期五 18时09分02秒
>> Last Modified : 2021年02月06日 星期六 20时07分30秒
>> 此程序的功能是：离散傅里叶变换，傅立叶变换数字落地，也即离散形式是离散傅立叶变换DFT(Discrete Fourier Transform)，而大家所熟知的快速傅立叶变换FFT(Fast Fourier Transform)则是DFT的高效率实现。

https://mp.weixin.qq.com/s?__biz=MzI0ODU0NDI1Mg==&mid=2247510611&idx=1&sn=ed96ea22fa2b021540fb8da013a4b010&chksm=e99dc4c0deea4dd6a1f20f77981f810032fd8cff6c00a0ac760299be0a6294c887847935a861&mpshare=1&scene=1&srcid=01102DZVqMgugLttdkykk2IB&sharer_sharetime=1610278768753&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd


X(k) = sum(N-1)(n=0){x(n)e[-j*2*PI*k*n/N]}   (k = 0,1,2,3...,N-1)

************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.1415926
#define  N 8000

typedef  struct
{
    double real, imag;
} Complex;


//输出y(k)
Complex X[N];


//输出的模
double amp[N];

int main(int argc, char *argv[])
{
    double xn;
    for(int k = 0; k < N; ++k)
    {
        X[k].real = 0;
        X[k].imag = 0;
        /* (X+k)->real = 0; */
        /* (X+k)->imag = 0; */
        for(int n = 0; n < N; ++n)
        {
            //原信号
            xn = 0.6*sin(n*PI*100) + 0.6*sin(n*PI*1000);
            X[k].real += xn*cos(-2*PI*n*k/N);
            X[k].imag += xn*cos(-2*PI*n*k/N);
            /* (X+k)->real += xn*sin(-2*PI*n*k/n); */
            /* (X+k)->imag += xn*sin(-2*PI*n*k/n); */
        }

        amp[k] = sqrt(X[k].real*X[k].real + X[k].imag*X[k].imag);
        printf("%8d %f\n", k, amp[k]);
    }

    return 0;
}
