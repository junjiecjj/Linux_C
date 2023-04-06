/**********************************************************************
>> File Name: bubble_sort.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.01.19
************************************************************************/

#include "SortAlgorithms.h"




// 从大到小返回排序后的数组和索引.
void BubbleSortInt(int *A, int n, int *idx)
{
    int tmp;
    int tmp1;
	if (A == NULL || idx == NULL)
		exit(EXIT_FAILURE);

    for(int j = 0; j < n-1; j++)
    {
        for(int i = 0; i < n-1-j; i++)
        {
            if(A[i] < A[i+1]){
                tmp = A[i];
                A[i] = A[i+1];
                A[i+1] = tmp;

                tmp1 = idx[i];
                idx[i] = idx[i+1];
                idx[i+1] = tmp1;
            }
        }
    }
}

// 从大到小返回排序后的数组和索引.
void BubbleSortDouble(double *A, int n, int *idx)
{
	if (A == NULL || idx == NULL)
		exit(EXIT_FAILURE);

    double tmp;
    int tmp1;
    for(int j = 0; j < n-1; j++)
    {
        for(int i = 0; i < n-1-j; i++)
        {
            if(A[i] < A[i+1]){
                tmp = A[i];
                A[i] = A[i+1];
                A[i+1] = tmp;

                tmp1 = idx[i];
                idx[i] = idx[i+1];
                idx[i+1] = tmp1;
            }
        }
    }
}


// 从大到小返回排序后的索引,原数组不动
void BubbleIndexSort(int *src, int size, int *index)
{
	int i, j;

	if (src == NULL || index == NULL){
        printf("error: 传入空数组, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }
	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			//if (src[j] < src[i])
			if ( src[ index[j] ] > src[ index[i] ] )
			{
				int tmp = index[i];
				index[i] = index[j];
				index[j] = tmp;
			}
		}
	}
}

int main1()
{
    int A[] = {111,2,1,6,4,3,12,21,33,22,56,66,45,7,5,9,10,19,34};
    int a = 212, b = 4324;
    printf("交换前:\n");
    printf("a = %d,b = %d.\n",a,b);
    printf("\n");



    int n = sizeof(A)/sizeof(int);
    int idx[19] = {0};
    for(int i = 0; i < n; i++){
        idx[i] = i;
    }
    printf("排序前数组A为:\n");
    for(int i = 0; i < n; i++)
        printf("%5d",*(A+i));
    printf("\n");
    for(int i = 0; i < n; i++)
        printf("%5d",*(idx+i));
        //printf("%5d",A[i]);
        //这两句等价

    printf("\n");
    BubbleSortInt(A, n, idx);
    printf("排序后数组为:\n");
    for(int i = 0; i < n; i++)
        printf("%5d",A[i]);
    printf("\n");
    for(int i = 0; i < n; i++)
        printf("%5d",*(idx+i));
    printf("\n");
    return 0;
}
