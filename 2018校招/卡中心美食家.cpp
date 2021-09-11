/*************************************************************************
>> File Name: 卡中心美食家.cpp
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.11
************************************************************************/

#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int n, m;
    scanf(" %d %d",&n, &m);
    int **A;
    A = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; ++i)
    {
        A[i] = (int *)malloc(sizeof(int) * n);
        for(int j = 0; j < n; ++j)
        {
            A[i][j] = 0;
        }
    }

    //int x,y;
    for(int i = 0; i < m; ++i)
    {
        int x,y;
        scanf(" %d %d", &y, &x);
        A[x][y] = 1;
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(A[i][j] == 1)
            {
                for(int k = 0; k < n; ++k)
                {
                    if(A[k][i] == 1)
                    {
                        A[k][j] = 1;
                    }
                }
            }
        }
    }

    int *result;
    result = (int *)malloc(sizeof(int)*n);
    int *Cout;
    Cout = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
    {
        int total = 0;
        for(int j = 0; j < n; j++)
        {
            if( A[i][j] == A[j][i] && A[i][j] ==1 && A[j][i] ==1 )
            {
                printf("None");
                return 0;
            }
            if(A[i][j] == 1)
                total++;
        }

        result[i] = total;
    }

    int k = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(result[j] == i)
            {
                Cout[k++] = j;
            }
        }
    }

    for(int i = n-1; i > 0; i--)
    {
        printf("%d,", Cout[i]);
    }
    printf("%d", Cout[0]);

    return 0;

}

