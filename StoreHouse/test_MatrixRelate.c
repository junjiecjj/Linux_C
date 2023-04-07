


#include "StdAfx.h"
#include "Utility.h"
#include "SortAlgorithms.h"
#include "MatrixAnalysis.h"

// #include "MatrixAnalysis.h"




int mainMatrix( )
{
    //=========================================================================================================

    int order;
    FILE *fp;

	printf("请输入行列式阶数：");
	scanf("%d", &order);
    double **matrix;
    // 分配内存
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
    //=====================================  行列式 =================================================
    printf("读取的 %d × %d 矩阵:\n",order,order);
    Display2DDoubleArray2DPoint(order, order, matrix);

    // 计算行列式 测试程序
    printf("行列式为: %.10lf \n", DeterminantGaussNormal(matrix, order));
    printf("行列式为: %.10lf \n", DeterminantGaussColPrime(matrix, order));
    printf("行列式为: %.10lf \n", DeterminantGaussGlobPrime(matrix, order));
    // // printf("行列式为: %f\n", Determinant(matrix, order));
    // // printf("原来的 %d × %d 矩阵:\n",order,order);
    // // Display2DDoubleArray2DPoint(order, order, matrix);

    //======================================  求逆 =================================================
    // 计算矩阵的逆矩阵 测试程序
    double **Inverse;
    // 分配内存
    Inverse = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        Inverse[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }

    InverseGauss(matrix, Inverse, order);
    printf("矩阵的逆矩阵为:\n");
    Display2DDoubleArray2DPoint(order, order, Inverse);

    double **recover;
    // 分配内存
    recover = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        recover[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }

    MatrixMultiplyDouble(matrix, order, order, Inverse, order, order, recover);
    printf("矩阵 x 矩阵的逆 为 :\n");
    Display2DDoubleArray2DPoint(order, order, recover);


    Matrix_Free_2DDouble(recover, order, order);
    Matrix_Free_2DDouble(Inverse, order, order);
    //=====================================  LU 分解 =================================================
    double **larr;
    // 分配内存
    larr = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        larr[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }

    double **uarr;
    // 分配内存
    uarr = (double **)malloc(order * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        uarr[i] = (double *)malloc(order * sizeof(double)); //每一行一定连续
    }

    DecompositionLU_Crout(matrix, larr, uarr, order);
    printf("Crout分解, L 矩阵为:\n");
    Display2DDoubleArray2DPoint(order, order, larr);
    printf("U 矩阵为:\n");
    Display2DDoubleArray2DPoint(order, order, uarr);

    DecompositionLU_Doolittle(matrix, larr, uarr, order);
    printf("Doolittle分解, L 矩阵为:\n");
    Display2DDoubleArray2DPoint(order, order, larr);
    printf("U 矩阵为:\n");
    Display2DDoubleArray2DPoint(order, order, uarr);

    Matrix_Free_2DDouble(uarr, order, order);
    Matrix_Free_2DDouble(larr, order, order);
    //=====================================  实对称矩阵的特征值特征向量 =================================================
    printf("=====================================  实对称矩阵的特征值特征向量 =================================================\n");
    double **matrix1;
    int order1 = 4;
    // 分配内存
    matrix1 = (double **)malloc(order1 * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order1; i++)
    {
        matrix1[i] = (double *)malloc(order1 * sizeof(double)); //每一行一定连续
    }


	if ((fp = fopen("/home/jack/snap/Matrix1.txt", "r")) == NULL){
			fprintf(stderr, "\n Cannot open the file!!!\n");
			exit(1);
	}

	for (int a = 0; a < order1; a++) {
		for (int b = 0; b < order1; b++) {
			fscanf(fp, "%lf", &matrix1[a][b]);
		}
	}
    fclose(fp);
    printf("读取的 %d × %d 矩阵:\n",order1,order1);
    Display2DDoubleArray2DPoint(order1, order1, matrix1);

    double **eigenVec;
    // 分配内存
    eigenVec = (double **)malloc(order1 * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order1; i++)
    {
        eigenVec[i] = (double *)malloc(order1 * sizeof(double)); //每一行一定连续
    }

    double *eigenVal;
    // 分配内存
    eigenVal = (double *)malloc(order1 * sizeof(double));  //每一行的首地址分配内存，不一定连续
    double eps = 1e-40;//误差
    int iter_max_num = 10000;//迭代总次数

    EigenValueVectors_Jacobi(matrix1, eigenVal, eigenVec, order1, eps, iter_max_num);

    printf("main 特征值:\n");
    Display1DDoubleArray1DPoint(order1, eigenVal);

    printf("main 特征向量为:\n");
    Display2DDoubleArray2DPoint(order1, order1, eigenVec);


    Matrix_Free_2DDouble(matrix1, order1, order1);
    Matrix_Free_2DDouble(eigenVec, order1, order1);
    Matrix_Free_1DDouble(eigenVal, order1 );


    printf("=====================================  SVD分解 =================================================\n");

    double **matrix2;
    int row = 5;
    int col = 4;
    // 分配内存
    matrix2 = (double **)malloc(row * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < row; i++)
    {
        matrix2[i] = (double *)malloc(col * sizeof(double)); //每一行一定连续
    }


	if ((fp = fopen("/home/jack/snap/MatrixSVD1.txt", "r")) == NULL){
			fprintf(stderr, "\n Cannot open the file!!!\n");
			exit(1);
	}

	for (int a = 0; a < row; a++) {
		for (int b = 0; b < col; b++) {
			fscanf(fp, "%lf", &matrix2[a][b]);
		}
	}


    double **Uarr;
    Uarr = (double **)malloc(row * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < row; i++)
    {
        Uarr[i] = (double *)malloc(row * sizeof(double)); //每一行一定连续
    }


    double **Sigma;
    Sigma = (double **)malloc(row * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < row; i++)
    {
        Sigma[i] = (double *)malloc(col * sizeof(double)); //每一行一定连续
    }


    double **Varr;
    Varr = (double **)malloc(col * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < col; i++)
    {
        Varr[i] = (double *)malloc(col * sizeof(double)); //每一行一定连续
    }

    int nozero = DecompositionSVD(matrix2, Uarr, Sigma, Varr, row, col);

    printf("非零特征值的个数:%d\n", nozero);

    printf("Uarr 为:\n");
    Display2DDoubleArray2DPoint(row, row, Uarr);


    printf("Sigma 为:\n");
    Display2DDoubleArray2DPoint(row , col , Sigma);


    printf("V 的转置为:\n");
    Display2DDoubleArray2DPoint(col , col , Varr);

    Matrix_Free_2DDouble(matrix2, row, col);
    Matrix_Free_2DDouble(Uarr, row, row);
    Matrix_Free_2DDouble(Sigma, row, col);
    Matrix_Free_2DDouble(Varr, col, col);
    //====================================== 释放内存 ================================================
    // for(int i = 0;  i < order; ++i){
    //     free(Inverse[i]);
    //     Inverse[i] = NULL;
    // }
    // free(Inverse);

    // // 释放内存
    // for(int i = 0;  i < order; ++i){
    //     free(matrix[i]);
    //     matrix[i] = NULL;
    // }
    // free(matrix);

    // // 释放内存
    // for(int i = 0;  i < order; ++i){
    //     free(larr[i]);
    //     larr[i] = NULL;
    // }
    // free(larr);

    // // 释放内存
    // for(int i = 0;  i < order; ++i){
    //     free(uarr[i]);
    //     uarr[i] = NULL;
    // }
    // free(uarr);

    // Matrix_Free_2DDouble(matrix, order, order);


    //========================================================================================================

//=======================================================

    return 0;
}


int mainSignal()
{

}


int main(int argc, char *argv[]){

    mainMatrix();

    return 0;
}