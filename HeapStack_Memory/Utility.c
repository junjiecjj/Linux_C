

// 其他实用的小功能函数,都放在这

#include  "Utility.h"

#define LEN 10


/**************************************************************************************************************************
            常用的打印函数，如打印一维二维数组函数，
***************************************************************************************************************************/
int Sum1DIntArray1(const int ar[], int n)
{
    int total = 0;
    for (int i=0; i < n; ++i)
    {
        total += ar[i];
    }
    return total;
}

/*
以上代码中的const告诉编译器，该函数不能修改ar指向的数组中的内容。如果在函数中不小心使用类似ar[i]++的表达式，编译器会捕获这个错误，并生成一条错误信息。

这里一定要理解，这样使用const并不是要求原数组是常量，而是该函数在处理数组时将其视为常量，不可更改。这样使用const可以保护数组的数据不被修改，就像按值传递可以保护基本数据类型的原始值不被改变一样。一般而言，如果编写的函数需要修改数组，在声明数组形参时则不使用const；如果编写的函数不用修改数组，那么在声明数组形参时最好使用const。
*/
int Sum1DIntArray2(int *start, int *end)
{
    int total = 0;

    while (start < end)
    {
        total += *start; // add value to total
        start++;         // advance pointer to next element
    }

    return total;
}


/* 数组的每个元素乘以相同的值，ar[]相当于 double *p,会改变原数组 */
void mult_array(double ar[], int n, double mult)
{
    int i;

    for (i = 0; i < n; i++)
        ar[i] *= mult;
}
/*************************************************************************************************************
 * 打印一维Int数组
*************************************************************************************************************/
void Display1DIntArray(const int arr[], int size)
{
    printf("****************  一维数组：传递一维数组 方法1*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}


void Display1DIntArray2(const int arr[], int size)
{
    printf("****************  一维数组：传递一维数组 方法5*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", *(arr + i));
    }
    printf("\n");
}


void Display1DIntArray3(const int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法2*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", arr[i]);
    }
    printf("\n");
}


void Display1DIntArray4(const int *arr, int size)
{
    printf("****************  一维数组：传递一维数组 方法4*********************\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%5d ", *(arr + i));
    }
    printf("\n");
}


/*************************************************************************************************************
 * 打印二维Int数组
*************************************************************************************************************/


//适用于A[m][n]形式申明的二维数组,C++中无法使用
void Display2DIntArray(int rows, int cols,int (*A)[cols])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d  ", A[i][j]);
        }
    printf("\n");
    }
}

//C++中无法使用
void Display2DIntArray1(int rows, int cols, int A[][cols])
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%8d", A[i][j]);
        }
        printf("\n");
    }
}

//适用于int **A形式申明的二维数组,内存连续或者不连续都行,推荐
void Display2DIntArray2DPoint(int rows, int cols, int **A)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d  ", A[i][j]);
            //printf("%5d  ", A[i*cols+j]);  //错误的做法
        }
    printf("\n");
    }
}



//适用于A[m][n]形式申明的二维数组,C++中无法使用
void Display2DIntArrayNorm(int rows, int cols, const int ar[rows][cols])  // 带变长数组形参arr的函数,arr是一个变长数组
{
    for(int i=0; i< rows;++i)
    {
        for(int j=0; j< cols; ++j)
        {
            printf("%5d  ", ar[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//适用于int **A形式申明的二维数组,内存连续,不连续时编译不会出错但是不对;
// A[m][n]形式声明的数组也行
void Display2DIntArrayUse1D(int rows, int cols, int *ar)
{
    for(int i=0; i< rows;++i)
    {
        for(int j=0; j<cols;++j)
        {
            // printf("%5d  ", *(ar+i*cols+j));
            printf("%5d  ", ar[i*cols+j]);
        }
        printf("\n");
    }

    printf("\n");
}


void Free2DNotContinueMem(int** pm,int r,int c){
    for(int i=0;  i<r; ++i){
        free(pm[i]);
        pm[i] = NULL;
    }
    free(pm);
    pm = NULL;
    //可以看出分配空间与释放空间都是逐步进行的，但是释放空间的顺序与分配空间的顺序相反。　
}


/**********************************************************************************************
矩阵相关，求行列式 ，逆矩阵 、伴随式、等
***********************************************************************************************/


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

int main_matrix()
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



/**********************************************************************************************
矩阵相关，求行列式 ，逆矩阵 、伴随式、等
***********************************************************************************************/








