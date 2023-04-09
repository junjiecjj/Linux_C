/*************************************************************************
>> File Name: SignalProcess.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2023年04月03日 星期一 22时02分08秒

>> 此程序的功能是：
************************************************************************/

#include "SignalProcess.h"




/******************************************************************************************
https://blog.csdn.net/qq_42528769/article/details/105599043

https://www.cnblogs.com/liudianfengmang/p/12700990.html

https://zhuanlan.zhihu.com/p/40505277?utm_oi=859350339957182464

https://blog.csdn.net/qq_20115319/article/details/111998342

https://blog.csdn.net/tengfei0973/article/details/102961477


******************************************************************************************/
void FFT(double **x, double **X, int len)
{
    for(int i = 0; i < len; i++){

    }

}

void shift(double *arr, int len)
{
    if(NULL== arr){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }
    double *tmparr  =  NULL;

    if( len % 2== 0 ){

    }
}


int main(int argc, char *argv[]){



    return 0;
}
