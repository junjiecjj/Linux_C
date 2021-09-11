/*************************************************************************
>> File Name: test.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2019年09月14日
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


int main(void)
{
    int zippo[4][2] = { {2,4}, {6,8}, {1,3}, {5, 7} };
    
    printf("zippo = %p, zippo + 1 = %p\n",zippo,zippo + 1);
    printf("zippo[0] = %p, zippo[0] + 1 = %p\n",zippo[0],zippo[0] + 1);
    printf("&zippo[0] = %p\n", &zippo[0]);
    printf("*zippo = %p, *zippo + 1 = %p\n",*zippo, *zippo + 1);
    printf("zippo[0][0] = %d\n", zippo[0][0]);
    printf("  *zippo[0] = %d\n", *zippo[0]);
    printf("    **zippo = %d\n", **zippo);
    printf("      zippo[2][1] = %d\n", zippo[2][1]);
    printf("*(*(zippo+2) + 1) = %d\n", *(*(zippo+2) + 1));
    
    return 0;
}
