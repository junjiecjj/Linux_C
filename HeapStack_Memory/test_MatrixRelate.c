#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 200  //最大计算阶数，可以更改
# define N 100


//两个函数的声明

double Determinant(double  **arr, int order);
double Cofactor(double  **arr, int order, int raw, int col);

void Display2DFloatArray2DPoint(int rows, int cols, double **arr);
void Display2DFloatArrayNorm(int rows, int cols, const double ar[MAX][MAX]);

double DeterminantGaussNormal(double **arr, int order);  // 普通 gaussian 求行列式
double DeterminantGaussColPrime(double **arr, int order);      // 列主元 gaussian 求行列式


void swap(double* a,double*b);
void SwapArrCol(double **arr, int col_a, int col_b, int order);

void InverseGauss(double **A, double **inverse);
void LinalgSolve(double **A, double *b, int order);




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
    printf("\n");
}

//适用于A[m][n]形式申明的二维数组,C++中无法使用
void Display2DFloatArrayNorm(int rows, int cols, const double ar[MAX][MAX])  // 带变长数组形参arr的函数,arr是一个变长数组
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



// 递归计算行列式,当 order 超过10时不适用, 计算时间指数级, 一般都用Gauss消元法.
double Determinant(double **arr, int order)
{
    double  sum = 0;//i是第一行的列指标，M是余子式的值，sum是行列式的计算值

	if (order == 1)//一阶行列式直接得出结果
		return arr[0][0];
	else if (order > 1)
	{
        // printf("here!!!\n");
		for (int i = 0; i < order; i++)//按第一行展开
		{
			sum += 1.0 * pow(-1, i+2) * arr[0][i] * Cofactor(arr, order, 0, i);
		}
	}
	return sum;
}


/**************************************************************
功能:递归计算 arr 的 row 行 col 列的余子式. 基本不用，一般都用Gauss消元法.
**************************************************************/
double Cofactor(double **arr, int order, int row, int col)
{

    double result = 0;
	double  **arr2;
    int origin_i, origin_j, r, c;

    //分配内存
    arr2 = (double **)malloc((order-1) * sizeof(double *));  //每一行的首地址分配内存，不一定连续
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
            if(i == row || j == col);
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
    // printf("order : %d\n", order-1);
    // Display2DFloatArray2DPoint(order-1, order-1, arr2);


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


void swap(double* a, double*b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void SwapArrCol(double **arr, int col_a, int col_b, int order)
{

	for(int i = 0; i < order; i++)
		swap(&arr[i][col_a], &arr[i][col_b]);
}

/***********************************************************************************************************************************************************
https://blog.csdn.net/Dream_wave/article/details/119192417
数学知识:
矩阵行列式的初等行变换：
1）换行变换：交换两行（行列式需变号）
2）倍法变换：将行列式的某一行（列）的所有元素同乘以数k（行列式需乘K倍）
3）消法变换：把行列式的某一行（列）的所有元素乘以一个数k并加到另一行（列）的对应元素上（行列式不变）

其中 1)会使矩阵的行列式的值反号;  2)会使得行列式的值变为 k*|A|;  3) 不改变行列式的值.
因此我们主要使用 1)和3) 化简矩阵，需要记录操作 1) 的总次数，包括行交换次数a 和 列交换的次数 b, 使得其变为对角阵, 然后对角相乘，再乘以 (-1)^(a+b) 得到最后的结果;

注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是普通的消元法;

方法一: 普通的消元法
功能: 利用普通的高斯消元法计算行列式：
1) 首先输入矩阵A;
2) 对于 A[i][i]的对角元素，找到第 i 行第一个不为0的元素的列 j, 以A[i][j]为主元，交换A[:][i] 和 A[:][j], 即交换A的第 i 和 j 列;
3) 消去 >i 的所有行的第 i 个元素;

重复以上过程，得到三角矩阵，对角元素乘积 再乘以 列交换的次数 就是行列式的值;
*****************************************************************************************/

double DeterminantGaussNormal(double **matrix, int order)
{
    int k;
	int n;				    // 阶数
	int sign = 0;			// 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp;			    // 暂存乘积因子
    double tmpvalue;        // 暂存矩阵的值
	double sum = 1.0;       // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("[exist.  file:%s,fun:%s, Line:%d,  ] \n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }


    //========================================================================
    // 为了消元过程不影响原 matrix, 先分配内存并拷贝数值;
    //========================================================================
    double **arr;
    arr = (double **)malloc(order * sizeof(double *));
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double));
    }
    // 拷贝矩阵数值
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}

    // 开始消元
	for(int i = 0; i < order - 1; i++){// 遍历对角线, 消元是以对角线为主轴的.
		k = 1;
		while(arr[i][i] == 0.0 && i+k < order){	     //确保标准数不为0. 寻找第i行的第一个不为0 的元素的列，并交换i 和 j列.
			// SwapArrCol(arr, i, i+(k++), order);
            for(int raw = 0; raw < order; raw++){
                tmpvalue = arr[raw][i];
                arr[raw][i] = arr[raw][i+k];
                arr[raw][i+k] = tmpvalue;
            }
            k++;
			sign++;
		}
        // printf("sign = %d\n", sign);
		if(arr[i][i] == 0.0 && i+k == order){		// 若整个一行都为0, 则结果为0, 结束;
			// printf("0");
			return 0;
		}
		for(int j = i + 1; j < order; j++){     // 开始消去i行后的每一行;
			if(arr[j][i] == 0.0){			    // 如 j 行的第 i 列元素为0, 则那一行不用化简;
				continue;
            }
			else{
				tmp = -(double)arr[j][i]/arr[i][i];		    // 保存乘积因子;
				for(k = i; k < order; k++)                  // 消去第 j 行的每一列元素;
					arr[j][k] += (tmp*arr[i][k]);
			}
		}

	}
	for(int i = 0; i < order; i++)
		sum *= arr[i][i];
    sum = sum * pow(-1, sign); // 考虑列交换的次数

    //================ 释放内存 ======================
    for(int i = 0;  i < order; ++i){
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);

	return sum;
}





/***********************************************************************************************************************************************************
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是列主元 的消元法;

方法一: 列主元 的消元法
功能: 利用 列主元 的高斯消元法计算行列式：
整体流程与代码
1）判断传入指针是否为空
2）判断矩阵维数，判断是否为方阵
3）为临时矩阵开辟空间
4）将原矩阵数据拷贝到临时矩阵中（保护原矩阵）
5）选择主元：利用初等行变换，找出每列绝对值最大的数，与主元行互换（1.提高一定的精度 2.避免原函数主对角线有0）
6）利用初等行变换进行消0

高斯消去法在消元过程中可能出现零主元，即，这时消元过程将无法进行；也可能主元绝对值非常小，用它做除法将会导致舍入误差的扩散，使数值解不可靠。解决该问题的办法是避免使用绝对值过小的元素作主元。
选择主元的方法：
1）找到主对角线以下每列最大的数Max所在的行数k
2）利用初等行变换——换行变换，将k行与当前主元行互换（记录总共换行次数n）
3）以当前主元行为基，利用初等行变换——消法变换，将主对角线下方消0
4）行列式每次换行需变号，行列式最后的符号为
5）每次进行高斯消去前都必须选择主元，计算n维的行列式，则需要进行n-1次主元选择

原文链接：https://blog.csdn.net/why1472587/article/details/128140020
https://blog.csdn.net/qq_59002046/article/details/121354692
https://blog.csdn.net/why1472587/article/details/128140020
https://blog.csdn.net/LanderXX/article/details/96686287
https://blog.csdn.net/you_big_father/article/details/83016329
https://blog.csdn.net/qq_49606218/article/details/124529117
https://blog.csdn.net/qq_43452446/article/details/90731365
https://blog.csdn.net/mohenxiang/article/details/122003372
https://blog.csdn.net/lzyws739307453/article/details/89816311
*****************************************************************************************/
double DeterminantGaussColPrime(double **matrix, int order)
{
    int k;
    int maxrow;             // 暂存主元的行号
    int maxval;             // 暂存对角线及以下元素的最大值
	int n;				    // 阶数
	int sign = 0;			// 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp;			    // 暂存乘积因子
	double sum = 1.0;       // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("[exist.  file:%s,fun:%s, Line:%d,  ] \n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }

    //=======================================================
    // 为了消元过程不影响matrix, 先分配内存并拷贝数值;
    //=======================================================
    double **arr;
    arr = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
    printf("拷贝的 %d × %d 矩阵:\n",order,order);
    Display2DFloatArray2DPoint(order, order, arr);

    //================================================================
    for(int i = 0; i < order - 1; ++i){// 遍历对角线, 消元是以对角线为主轴的.

        maxval = fabs(arr[i][i]);
        maxrow = i;
        for(int j = i + 1; maxrow < order; ++maxrow ){
            if( fabs(arr[j][i]) > maxval ){
                maxrow = j;
                maxval = fabs(arr[j][i]);
            }
        }
        if(maxval == 0.0)
        {
            printf("zero colum\n");
            return 0;
        }
        

    }





    //======================================
    // 释放内存
    //======================================
    for(int i = 0;  i < order; ++i){
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);

	return sum;

}


int main1()
{
	//我的坏毛病，参数过多，后面不一定有用上
    int k,n,i,j,r,w,e,g;
	double a[N][N+1],b[N],m[N][N],x[N],c[N],s=0,f,max,uu[N];
	printf("请输入未知数的个数：");
	scanf("%d",&n);
	printf("请输入数据：");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n+1;j++)
		{
			scanf("%lf",&a[i][j]);
		}

	}
	for(i=0;i<n;i++)
	{
		b[i]=a[i][n];
	}
	/*  验证代码是否正确 可将这段代码放到任何一个位置进行正确性检验
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%lf ",a[i][j]);
		}
		printf("%lf\n",b[i]);
	}*/
    for(r=0; r<n-1; r++)//这一步开始寻找每一列最大的数
	{
        k=r;
        max=a[r][r];
        for(w=r; w<n-1; w++)//寻找，若找到该列下面有比起始大的数，则进行标记
        {
            if(a[w+1][r] >= a[w][r])
            {
                max = a[w+1][r];
                k = w+1;          //若找到下列大的数，标记
            }
        }
        if(k >= r)//此时表示找到
        {
            for(e = r; e < n; e++)//将下列最大的数的那一行与这列起始数的那一行所有数进行行更换
            {
                f = a[r][e];
                a[r][e] = a[k][e];
                a[k][e] = f;
            }
            f = b[r];//让y保持与行同变化
            b[r] = b[k];
            b[k] = f;
        }
        for(i = r+1; i < n; i++)//与上面相同，进行高斯消去法，因为列已经变化完毕
        {
            m[i][r] = 1.0*a[i][r]/a[r][r];
            b[i] = b[i] - 1.0*m[i][r]*b[r];
            for(j =r; j < n; j++){
                a[i][j] = a[i][j]-1.0*m[i][r]*a[r][j];
            }
        }
    }
	//回代过程
	x[n-1]=1.0*b[n-1]/a[n-1][n-1];
    for(i=n-2;i>=0;i--)
    {
        s=0;
        for(j=i+1;j<n;j++)
        {
            c[j]=1.0*a[i][j]*x[j];
            s=c[j]+s;
		}
		x[i]=1.0*(b[i]-s)/a[i][i];
	}
	for(i=0;i<n;i++)
	{
	    printf("x[%d]=%lf\n",i+1,x[i]);
	}
	return 0;
}





/*****************************************************************************************
功能: 利用高斯消元法计算矩阵的逆矩阵;
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是

数学知识: 对于阶数为 n 的矩阵A，求它的逆矩阵可以如下:
1) 构造矩阵 B = [A, I]_{nx2n}
2） 只能利用初等行变换将 B 化简为 B = [I, A^-1]的形式
3) B 的右部分就是 A 的逆矩阵.

*****************************************************************************************/
void InverseGauss(double **A, double **inverse)
{

}




/*****************************************************************************************
功能: 利用高斯消元法求解线性方程组;
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是

数学知识: 对于阶数为 n 的矩阵A，求它的逆矩阵可以如下:
1) 构造矩阵 B = [A, I]_{nx2n}
2） 只能利用初等行变换将 B 化简为 B = [I, A^-1]的形式
3) B 的右部分就是 A 的逆矩阵.

*****************************************************************************************/
void LinalgSolve(double **A, double *b, int order)
{


}


int main()
{
    //=========================================================================================================

    int order;
    FILE *fp;

	printf("请输入行列式阶数：");
	scanf("%d", &order);
    double **matrix;
    //这样分配内存不连续,行内连续，行间不一定连续，
    matrix = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        matrix[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }


	if ((fp = fopen("/home/jack/snap/Matrix.txt", "r")) == NULL){
			fprintf(stderr, "\n Cannot open the file!!!\n");
			exit(1);
	}

	for (int a = 0; a < order; a++) {
		for (int b = 0; b < order; b++) {
			fscanf(fp, "%lf", &matrix[a][b]);
		}
	}
    fclose(fp);

    printf("读取的 %d × %d 矩阵:\n",order,order);
    Display2DFloatArray2DPoint(order, order, matrix);

    printf("行列式为: %lf \n", DeterminantGaussNormal(matrix, order));
    printf("行列式为: %lf \n", DeterminantGaussColPrime(matrix, order));
    // printf("行列式为: %f\n", Determinant(matrix, order));
    // printf("原来的 %d × %d 矩阵:\n",order,order);
    // Display2DFloatArray2DPoint(order, order, matrix);

    for(int i = 0;  i < order; ++i){
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);

    //========================================================================================================
    // int order;
	// printf("请输入行列式阶数：");
	// scanf("%d", &order);
    // double **matrix;
    // //这样分配内存不连续,行内连续，行间不一定连续，
    // matrix = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    // for (int i = 0; i < order; i++)
    // {
    //     matrix[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    // }
    // printf("输入一个 %d × %d 矩阵:\n",order,order);
	// for (int a = 0; a < order; a++) {
	// 	for (int b = 0; b < order; b++) {
	// 		scanf("%lf", &matrix[a][b]);
	// 	}
	// }

    // Display2DFloatArray2DPoint(order, order, matrix);

    // printf("%f", Determinant(matrix, order));



    // for(int i = 0;  i < order; ++i){
    //     free(matrix[i]);
    //     matrix[i] = NULL;
    // }
    // free(matrix);
    // matrix = NULL;
//=======================================================

    return 0;
}



