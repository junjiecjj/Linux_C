


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float determinant(float matrix[20][20], int order);
float cofactor(float matrix[20][20], int order, int r, int c);
float adjugate_matrix(float matrix[20][20], int order, int r, int c);
float inverse_matrix(float matrix[20][20], int order, int r, int c);
float transposed_matrix(float matrix[20][20], int r, int c, int i, int j);
void show_inverse_matrix(float matrix[20][20], int order);
void show_adjugate_matrix(float matrix[20][20], int order);
void show_transposed_matrix(float matrix[20][20], int r, int c);
void menu(void);

int testmain()
{
    float matrix[20][20];
    int r,c,i,j,choice;
begin:
    printf("输入矩阵的行规模:");
    scanf("%d",&r);
    printf("输入矩阵的列规模:");
    scanf("%d",&c);
    printf("输入一个 %d × %d 矩阵:\n",r,c);
    for(i = 0;i < r;i ++)
        for(j = 0;j < c;j ++)
            scanf("%f",&matrix[i][j]);
menu:
    menu();
    scanf("%d",&choice);
    if(choice == 1)
    {
        if(r != c)
            printf("非方阵不存在伴随矩阵!\n");
        else
        {
            printf("矩阵的伴随矩阵为:\n");
            show_adjugate_matrix(matrix,r);
        }
        goto menu;
    }
    else if(choice == 2)
    {
        if(r != c)
            printf("非方阵不存在逆矩阵!\n");
        else
            if(determinant(matrix,r) == 0)
                printf("方阵不存在逆矩阵!\n");
            else
            {
                printf("矩阵的逆矩阵为:\n");
                show_inverse_matrix(matrix,r);
            }
        goto menu;
    }
    else if(choice == 3)
    {
        printf("矩阵的转置矩阵为:\n");
        show_transposed_matrix(matrix,r,c);
        goto menu;
    }
    else if(choice == 0)
        goto end;
    else
    {
        printf("指令错误，重新输入!\n");
        goto menu;
    }
end:
    return 0;
}

float determinant(float matrix[20][20], int order)
{
    float result = 0,sign = 1;
    int i;

    if(order == 1)
        result = matrix[0][0];
    else
        for(i = 0;i < order;i ++)
        {
            result += sign * matrix[i][0] * cofactor(matrix, order, i, 0);
            sign *= -1;
        }

    return result;
}


float cofactor(float matrix[20][20], int order, int r, int c)
{
    float result = 0, cofactor[20][20];
    int original_i, original_j, i, j;

    for(i = 0; i < order; i ++)
        for(j = 0; j < order; j ++)
        {
            original_i = i;
            original_j = j;
            if(i == r || j == c);
            else
            {
                if(i > r)
                    i --;
                if(j > c)
                    j --;
                cofactor[i][j] = matrix[original_i][original_j];
                i = original_i;
                j = original_j;
            }
        }
    if(order >= 2)
        result = determinant(cofactor, order - 1);

    return result;
}

float adjugate_matrix(float matrix[20][20], int order, int r, int c)
{
    float result = 0;

    if(order == 1 && r == 0 && c == 0)
        result = 1;
    else
        result = pow(-1, r + c) * cofactor(matrix,order,c,r);
    if(result <= 0 && result >= -0.0005)
        result = fabs(result);

    return result;
}

float inverse_matrix(float matrix[20][20],int order,int r,int c)
{
    float result = 0;

    result = adjugate_matrix(matrix,order,r,c) / determinant(matrix,order);
    if(result <= 0 && result >= -0.0005)
        result = fabs(result);

    return result;
}

float transposed_matrix(float matrix[20][20],int r,int c,int i,int j)
{
    return matrix[j][i];
}

void show_inverse_matrix(float matrix[20][20],int order)
{
    int i,j;

    for(i = 0;i < order;i ++)
    {
        for(j = 0;j < order;j ++)
            printf("%.3f\t",inverse_matrix(matrix,order,i,j));
        printf("\n");
    }
}

void show_adjugate_matrix(float matrix[20][20],int order)
{
    int i,j;

    for(i = 0;i < order;i ++)
    {
        for(j = 0;j < order;j ++)
            printf("%.3f\t",adjugate_matrix(matrix,order,i,j));
        printf("\n");
    }
}

void show_transposed_matrix(float matrix[20][20],int r,int c)
{
    int i,j;

    for(i = 0;i < c;i ++)
    {
        for(j = 0;j < r;j ++)
            printf("%.3f\t",transposed_matrix(matrix,r,c,i,j));
        printf("\n");
    }
}

void menu(void)
{
    printf("\n");
    printf("[1]求伴随矩阵.\n");
    printf("[2]求逆矩阵.\n");
    printf("[3]求转置矩阵.\n");
    printf("[0]结束.\n");
    printf("输入你的选择:");
}

//适用于int **A形式申明的二维数组,内存连续或者不连续都行,推荐
void Display2DFloatArray2DPoint(int rows, int cols, float **A)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%-12.3f", A[i][j]);
            //printf("%5d  ", A[i*cols+j]);  //错误的做法
        }
    printf("\n");
    }
}

//适用于A[m][n]形式申明的二维数组,C++中无法使用
void Display2DFloatArrayNorm(int rows, int cols, const float ar[2][2])  // 带变长数组形参arr的函数,arr是一个变长数组
{
    for(int i=0; i< rows;++i)
    {
        for(int j=0; j< cols; ++j)
        {
            printf("%-12.3f", ar[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{

    int row = 3, col = 3;

    float **matrix;
    //这样分配内存不连续,行内连续，行间不一定连续，
    matrix = (float **)malloc(row * sizeof(float *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (float *)malloc(col * sizeof(float)); //每一行一定连续
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = i * col + j+1;
        }
    }

    printf("%-12.3lf\n", 12.23);
    // printf("输入矩阵的行规模:");
    // scanf("%d",&row);
    // printf("输入矩阵的列规模:");
    // scanf("%d",&col);
    // printf("输入一个 %d x %d 矩阵:\n", row, col);
    // for(i = 0; i < row; i ++)
    //     for(j = 0; j < col; j ++)
    //         scanf("%f",&matrix[i][j]);

    Display2DFloatArray2DPoint(row, col, matrix);




    return 0;
}