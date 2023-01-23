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
#include "C_StaticGlobal.h"
#include "C_StaticGlo.h"
#include "Diceroll.h"
#include "loc_stat.h"
#include "PartAB.h"
#include "Where.h"
#include "S_and_r.h"
#include "VLAmal.h"
#include "ArrayPoint.h"
#include "String.h"

int main(int argc, char *argv[])
{
    /**************************************************************************************************/

    //CString();
    TestStruct();
    TestArrayPoint();


    // printf("******************* 测试全局和静态变量的定义、初始化、使用 *******************\n");
    // InitStaticMemory();
    // ChangeStaticMem();
    // FreeStaticMem();

    // /**************************************************************************************************/
    // printf("\n********************  ******************* \n");
    // DisplayMonth();
    // /**************************************************************************************************/
    // printf("\n******************** 被调函数创建一个数组并返回指针， 供主调函数访问， 然后主调函数在末尾调用free()释放之前被调函数分配的内存。 ******************* \n");
    // //这样是可以的，只要后面释放，不会造成内存泄露

    // UseLocalPoint();


    // /**************************************************************************************************/
    // printf("\n******************** 程序把静态对象、 自动对象和动态分配的对象储存在不同的区域 ******************* \n");
    // WHERE();

    // /***************************************************************************************************/
    // printf("******************** 静态存储期，外部连接，文件作用域，所有函数外******************** \n");
    // ChangeGlob();

    // /***************************************************************************************************/
    // printf("\n******************** 静态存储期，无连接，块内，块作用域，函数内******************** \n");
    // Trystat();

    // /***************************************************************************************************/
    // printf("\n******************** 掷骰子游戏: 静态存储期，外部连接，文件作用域，所有函数外******************** \n");
    // maindice();


    // /***************************************************************************************************/
    // printf("\n******************** 随机数: 静态存储期，内部链接，文件作用域，块内******************** \n");
    // SEED();

    // /**************************************************************************************************/
    // printf("\n******************** 综合演示：静态变量(外部链接、内部链接、无链接), 寄存器变量，自动变量 ******************** \n");
    // Partab();

    // printf("****************  一维数组：传递一维数组 方法2*********************\n");
    // GlobalPoint[2] = 693;
    // for (int i = 0; i < LEN; ++i)
    // {
    //     printf("%5d ", GlobalPoint[i]);
    // }
    // printf("\n");

    // /***************************************************************************************************/
    // printf("\n******************** 被调函数创建一个数组并返回指针， 供主调函数访问， 然后主调函数在末尾调用free()释放之前被调函数分配的内存。 ******************* \n");
    // FreeLocalPoint(GlobalPoint);

    // Display1DIntArray3(GlobalPoint, LEN);
    /***************************************************************************************************/
    return 0;




}
