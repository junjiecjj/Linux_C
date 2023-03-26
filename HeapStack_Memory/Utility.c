

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


/****************************************************************************************************************************************************************************
矩阵相关，求行列式
****************************************************************************************************************************************************************************/


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

// 交换矩阵的两列
void SwapArrCol(double **arr, int col_a, int col_b, int order)
{

	for(int i = 0; i < order; i++)
		swap(&arr[i][col_a], &arr[i][col_b]);
}


// 交换矩阵的两行
void SwapArrRaw(double **arr, int raw_a, int raw_b, int order)
{
	for(int i = 0; i < order; i++)
		swap(&arr[raw_a][i], &arr[raw_b][i]);
}

/***********************************************************************************************************************************************************
https://blog.csdn.net/Dream_wave/article/details/119192417
数学知识:
矩阵行列式的初等行变换：
1）换行变换：交换两行（行列式需变号）
2）倍法变换：将行列式的某一行（列）的所有元素同乘以数k（行列式需乘K倍）
3）消法变换：把行列式的某一行（列）的所有元素乘以一个数k并加到另一行（列）的对应元素上（行列式不变）

这里要用到几个性质：
1） 矩阵的某行或某列全部元素乘上一个常数，则行列式的值也乘上这个常数。
2） 矩阵的某行（列）全部加上另一行（列）的元素*常数，行列式的值不变。
3） 下（上）三角矩阵的行列式等于其对角线元素的乘积。
4） 矩阵的某行或某列全为零，行列式为零。
5） 转置不改变行列式。
6） 交换两行或两列，行列式取相反数。
7) 若行列式的两行或者两列成比例，则行列式为0.

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

方法二: 列主元 的消元法
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
5）每次进行高斯消去前都必须选择主元，计算n维的行列式，则需要进行n-1次主元选择.
*****************************************************************************************/
double DeterminantGaussColPrime(double **matrix, int order)
{
    int k;
    int maxrow;             // 暂存主元的行号
    double maxval;             // 暂存对角线及以下元素的最大值

	int sign = 0;			 // 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp = 0;			 // 暂存乘积因子
    double tmpv = 0;         // 暂存元素值
	double sum = 1.0;        // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("[exist.  file:%s,fun:%s, Line:%d,  ] \n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }


    //=======================================================
    // 为了消元过程不影响matrix, 先分配内存并拷贝数值;
    //=======================================================
    double **arr;
    arr = (double **)malloc(order * sizeof(double *));     // 每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double)); // 每一行一定连续
    }

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
    // printf("拷贝的 %d × %d 矩阵:\n",order,order);
    // Display2DFloatArray2DPoint(order, order, arr);

    //================================================================
    for(int i = 0; i < order - 1; ++i){// 遍历对角线, 消元是以对角线为主轴的.

        maxval = fabs(arr[i][i]);
        maxrow = i;
        for(int j = i + 1; j < order; ++j ){ // 寻找 第 i 列的 >= i+1 中的最大元素的行.
            if( fabs(arr[j][i]) > maxval ){
                maxrow = j;
                maxval = fabs(arr[j][i]);
            }
        }
        // printf("i = %d, maxrow = %d\n", i, maxrow);

        if(maxval == 0.0)
        {
            printf("zero colum\n");
            return 0;
        }
        if(maxrow > i){
            for(int j = 0; j < order; ++j) // 交换行
            {
                tmpv = arr[i][j];
                arr[i][j] = arr[maxrow][j];
                arr[maxrow][j] = tmpv;
            }
            sign++;
        }

        for(int k = i + 1; k < order; ++k) // 消元
        {
            if(arr[k][i] == 0.0){
                continue;
            }
            else{
                tmp = -(double)arr[k][i]/arr[i][i];;
                for(int j = i; j < order; ++j){
                    arr[k][j] += tmp*arr[i][j];
                }
            }
        }
    }

	for(int i = 0; i < order; i++)
		sum *= arr[i][i];
    sum = sum * pow(-1, sign); // 考虑列交换的次数


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


/***********************************************************************************************************************************************************
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是列主元 的消元法;

方法二: 列主元 的消元法
功能: 利用 列主元 的高斯消元法计算行列式：
整体流程与代码
1）判断传入指针是否为空
2）判断矩阵维数，判断是否为方阵
3）为临时矩阵开辟空间
4）将原矩阵数据拷贝到临时矩阵中（保护原矩阵）
5）选择主元：利用初等行变换，找出当前对角线元素右下角(包括自己)绝对值最大的数，与主元行互换（1.提高一定的精度 2.避免原函数主对角线有0）
6）利用初等行变换进行消0

*****************************************************************************************/
double DeterminantGaussGlobPrime(double **matrix, int order)
{
    int k;
    int maxrow;             // 暂存主元的行号
    int maxcol;             // 暂存主元的列号
    double maxval;             // 暂存对角线及以下元素的最大值

	int sign = 0;			// 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp = 0;			    // 暂存乘积因子
    double tmpv = 0;            // 暂存元素值
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
    arr = (double **)malloc(order * sizeof(double *));     // 每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double)); // 每一行一定连续
    }

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
    // printf("拷贝的 %d × %d 矩阵:\n",order,order);
    // Display2DFloatArray2DPoint(order, order, arr);

    //================================================================
    for(int i = 0; i < order - 1; ++i){// 遍历对角线, 消元是以对角线为主轴的.

        maxval = fabs(arr[i][i]);
        maxrow = i;
        maxcol = i;
        // 找到当前对角线主元右下角(包括自己)所有元素中的最大的元素的行和列
        for(int j = i; j < order; ++j ){
            for(int k = i; k < order; ++k){
                if( fabs(arr[j][k]) > maxval ){
                    maxrow = j;
                    maxcol = k;
                    maxval = fabs(arr[j][i]);
                }
            }
        }
        // printf("i = %d, maxrow = %d, maxcol = %d\n", i, maxrow, maxcol);

        if(maxval == 0.0)
        {
            // printf("max value is zero, exit \n");
            return 0;
        }
        // 交换行
        if(maxrow > i){
            for(int j = 0; j < order; ++j)
            {
                tmpv = arr[maxrow][j];
                arr[maxrow][j] = arr[i][j];
                arr[i][j] = tmpv;
            }
            sign++;
        }
        // 交换列
        if(maxcol > i){
            for(int j = 0; j < order; ++j)
            {
                tmpv = arr[j][maxcol];
                arr[j][maxcol] = arr[j][i];
                arr[j][i] = tmpv;
            }
            sign++;
        }

        for(int k = i + 1; k < order; ++k){
            if(arr[k][i] == 0.0){
                continue;
            }
            else{
                tmp = -(double)arr[k][i]/arr[i][i];;
                for(int j = i; j < order; ++j){
                    arr[k][j] += tmp*arr[i][j];
                }
            }
        }
    }

	for(int i = 0; i < order; i++)
		sum *= arr[i][i];
    sum = sum * pow(-1, sign); // 考虑列交换的次数


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



/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的逆
****************************************************************************************************************************************************************************/

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



/****************************************************************************************************************************************************************************
矩阵相关，解线性方程组
****************************************************************************************************************************************************************************/

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




/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 LU 分解
****************************************************************************************************************************************************************************/
void DecompositionCroutLU(double **arr, double **Larr, double Uarr, int order) //  矩阵的 LU 分解
{

}

/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 QR分解
****************************************************************************************************************************************************************************/

void DecompositionQR(double **arr, double **Qarr, double Rarr, int order) //  矩阵的 QR 分解
{

}


/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 SVD分解
****************************************************************************************************************************************************************************/


void DecompositionSVD(double **arr, double **Sarr, double Varr, double Darr,  int order) //  矩阵的 SVD 分解
{

}




