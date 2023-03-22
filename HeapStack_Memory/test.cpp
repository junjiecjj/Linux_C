#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 200  //最大计算阶数，可以更改

//两个函数的声明

double Determinant(double  **arr, int order);
double Cofactor(double  **arr, int raw, int col, int order);
void Display2DFloatArray2DPoint(int rows, int cols, double **arr);




//适用于int **A形式申明的二维数组,内存连续或者不连续都行,推荐
void Display2DFloatArray2DPoint(int rows, int cols, double **arr)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%-12.3lf", arr[i][j]);
            //printf("%5d  ", A[i*cols+j]);  //错误的做法
        }
    printf("\n");
    }
}

// 递归计算行列式,当 order 很大时不适用
double Determinant(double **arr, int order)
{
    double  sum = 0;//i是第一行的列指标，M是余子式的值，sum是行列式的计算值

	if (order == 1)//一阶行列式直接得出结果
		return arr[0][0];
	else if (order > 1)
	{
        printf("here!!!\n");
		for (int i = 0; i < order; i++)//按第一行展开
		{
			sum += 1.0 * pow(-1, i) * arr[0][i] * Cofactor(arr, 0, i, order);
		}
	}
	return sum;
}


/**************************************************************
功能:递归计算 arr 的 row 行 col 列的余子式.
**************************************************************/
double Cofactor(double **arr, int row, int col, int order)
{

    double result = 0;
	double  **arr2;
    int origin_i, origin_j, r, c;

    //分配内存
    arr2 = (double **)malloc((order-1) * sizeof(float *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order-1; i++)
    {
        arr2[i] = (double *)malloc((order-1) * sizeof(double)); //每一行一定连续
    }

	//以下为构造余子式的过程。由于C语言的特性，这个过程会比较复杂，需要观察余子式与原行列式的关系。
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            origin_i = i;
            origin_j = j;
            if(i == r || j == c);
            else
            {
                if(i > row)
                    i --;
                if(j > col)
                    j --;
                arr2[i][j] = arr[origin_i][origin_j];
                i = origin_i;
                j = origin_j;
            }
        }
    }
    if(order >= 2)
    {
        result = Determinant(arr2, order - 1);//构造完后，余子式是一个新的行列式，返回DET函数进行计算。
    }

    // 释放内存
    for(int i=0;  i < order-1; ++i){
        free(arr2[i]);
        arr2[i] = NULL;
    }
    free(arr2);
    arr2 = NULL;

	return result;
}

// https://blog.csdn.net/Dream_wave/article/details/119192417
double DeterminantGauss(double **arr, int order)
{

}



int main()
{
	// float arr1[MAX][MAX];
	// int a,b,n;
	// printf("请输入行列式阶数：");
	// scanf("%d", &n);
	// printf("请输入行列式：\n");
	// for (a = 0; a < n; a++) {
	// 	for (b = 0; b < n; b++) {
	// 		scanf("%f", &arr1[a][b]);
	// 	}
	// }

    // // for (int i = 0; i < n; i++)
    // // {
    // //     for (int j = 0; j < n; j++)
    // //     {
    // //         arr1[i][j] = i * n + j+1;
    // //     }
    // // }

    // printf("%f", DET(arr1, n));


    //=======================================================
    int order = 3;
	printf("请输入行列式阶数：");
	scanf("%d", &order);
    double **matrix;
    //这样分配内存不连续,行内连续，行间不一定连续，
    matrix = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        matrix[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }

	printf("请输入行列式：\n");
	for (int a = 0; a < order; a++) {
		for (int b = 0; b < order; b++) {
			scanf("%lf", &matrix[a][b]);
		}
	}

    // for (int i = 0; i < order; i++)
    // {
    //     for (int j = 0; j < order; j++)
    //     {
    //         matrix[i][j] = rand()%10;
    //     }
    // }

    Display2DFloatArray2DPoint(order, order, matrix);

    printf("%f", Determinant(matrix, order));

    for(int i = 0;  i < order; ++i){
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;


    return 0;
}
