/*************************************************************************
>> File Name: C_static_gloable.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月09日 星期六 22时54分58秒
>>
// 本Project是为了学习C语言的诸多技巧和总结一些常用的功能函数而建立的，

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "VLAmal.h"



int main(int argc, char *argv[])
{
    //**************************************************************************************************
    printf("\n******************** 被调函数创建一个数组并返回指针， 供主调函数访问， 然后主调函数在末尾调用free()释放之前被调函数分配的内存。 ******************* \n");
    //这样是可以的，只要后面释放，不会造成内存泄露

    DisplayMonth();


    //**************************************************************************************************
    printf("\n******************** 程序把静态对象、 自动对象和动态分配的对象储存在不同的区域 ******************* \n");

    //***************************************************************************************************
    printf("******************** 静态存储期，外部连接，文件作用域，所有函数外******************** \n");


    //***************************************************************************************************
    printf("\n******************** 静态存储期，无连接，块内，块作用域，函数内******************** \n");


    //***************************************************************************************************
    printf("\n******************** 掷骰子游戏: 静态存储期，外部连接，文件作用域，所有函数外******************** \n");



    //***************************************************************************************************
    printf("\n******************** 随机数: 静态存储期，内部链接，文件作用域，块内******************** \n");


    //**************************************************************************************************
    printf("\n******************** 综合演示：静态变量(外部链接、内部链接、无链接), 寄存器变量，自动变量 ******************** \n");


    printf("****************  一维数组：传递一维数组 方法2*********************\n");


    //***************************************************************************************************
    printf("\n******************** 被调函数创建一个数组并返回指针， 供主调函数访问， 然后主调函数在末尾调用free()释放之前被调函数分配的内存。 ******************* \n");

    //***************************************************************************************************
    return 0;




}