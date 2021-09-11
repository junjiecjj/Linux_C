/*************************************************************************
>> File Name: 卡中心密码安全规范.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.11
************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    char C[100], S[21];
    fgets(C, 100, stdin);
    int low_c = 0, up_c = 0, num = 0, flag = 1;
    int i, n, count = 0, n1 = 0, j = 0, n2 = 0;
    if(strlen(C) > 20)
    {
        for(i = 0; i < strlen(C); i++)
        {
            if(C[i] == C[i + 1] && C[i + 1] == C[i + 2])
            {

                if(strlen(C) - n1 == 20)
                {
                    S[j] = C[i];
                    j ++;
                }
                else
                {
                    n1 ++;
                    S[j] = C[i];
                    S[j + 1] = C[i + 1];
                    j = j + 2;
                    i = i + 2;
                }
            }
            else
            {
                S[j] = C[i];
                j ++;
            }
        }
        //printf("%d\n", j);
    }
    else
        strcpy(S, C);
    printf("S = %s\n", S);
    printf("C = %s\n", C);
    if(strlen(C) - n1 > 20)
    {
        strncpy(S, C, 20);
        n2 = strlen(C) - n1 - 21;
    }
    //printf("%d\n", n2);
    for(i = 0; i < (strlen(C) - n1); i++)
    {
        if(S[i] >= 'a' && S[i] <= 'z')
        {
            low_c = 1;
        }
        if(S[i] >= 'A' && S[i] <= 'Z')
        {
            up_c = 1;
        }
        if(S[i] >= '0' && S[i] <= '9')
        {
            num = 1;
        }
        if(S[i] == S[i + 1] && S[i + 1] == S[i + 2])
        {
            i =  i + 2;
            flag = 0;
            count ++;
        }
    }
    if(flag == 0)
    {
        printf("%d", count + n1 + n2);
        return 0;
    }
    n = 3 - low_c - up_c - num;
    printf("%d", n + n1 + n2);
}

