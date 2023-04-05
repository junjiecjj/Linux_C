#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float** Matrix_Jac_Eig(float **array, int n, float *eig);
int Matrix_Free(float **tmp, int m, int n);



int main(void)
{
	int n;
	printf("请输入矩阵维度:\n");
	scanf("%d", &n);
	float **array = (float **)malloc(n * sizeof(float *));
	if (array == NULL)
	{
		printf("error :申请数组内存空间失败\n");
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		array[i] = (float *)malloc(n * sizeof(float));
		if (array[i] == NULL)
		{
			printf("error :申请数组子内存空间失败\n");
			return -1;
		}
	}
	printf("请输入矩阵元素:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%f", &array[i][j]);
		}
	}
	float *eig = (float *)malloc(n * sizeof(float));
	float **Result = Matrix_Jac_Eig(array, n, eig);
	printf("特征矩阵元素:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f ", Result[i][j]);
		}
		printf("\n");
	}
	printf("特征矩阵元素:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%f \n", eig[i]);
	}
	Matrix_Free(Result, n, n);
	free(eig);
	eig = NULL;
	return 0;
}
float** Matrix_Jac_Eig(float **array, int n, float *eig)
{
	//先copy一份array在temp_mat中，因为我实在堆区申请的空间,在对其进行处理
	//的过程中会修改原矩阵的值,因此要存储起来,到最后函数返回的
	//时候再重新赋值
	int i, j, flag, k;
	flag = 0;
	k = 0;
	float sum = 0;
	float **temp_mat = (float **)malloc(n * sizeof(float *));
	for (i = 0; i < n; i++)
	{
		temp_mat[i] = (float *)malloc(n * sizeof(float));
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			temp_mat[i][j] = array[i][j];
		}
	}
	//判断是否为对称矩阵
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			if (array[i][j] != array[j][i])
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag == 1)
	{
		printf("error in Matrix_Eig: 输入并非是对称矩阵:\n");
		return NULL;
	}
	else
	{
		//开始执行算法
		int p, q;
		float thresh = 0.0000000001;
		float max = array[0][1];
		float tan_angle, sin_angle, cos_angle;
		float **result = (float **)malloc(n * sizeof(float *));
		if (result == NULL)
		{
			printf("error in Matrix_Eig:申请空间失败\n");
			return NULL;
		}
		float **result_temp = (float **)malloc(n * sizeof(float *));
		if (result_temp == NULL)
		{
			printf("error in Matrix_Eig:申请空间失败\n");
			return NULL;
		}
		float **rot = (float **)malloc(n * sizeof(float *));
		if (rot == NULL)
		{
			printf("error in Matrix_Eig:申请空间失败\n");
			return NULL;
		}
		float **mat = (float **)malloc(n * sizeof(float *));
		if (mat == NULL)
		{
			printf("error in Matrix_Eig:申请空间失败\n");
			return NULL;
		}
		for (i = 0; i < n; i++)
		{
			result[i] = (float *)malloc(n * sizeof(float));
			if (result[i] == NULL)
			{
				printf("error in Matrix_Eig:申请子空间失败\n");
				return NULL;
			}
			result_temp[i] = (float *)malloc(n * sizeof(float));
			if (result_temp[i] == NULL)
			{
				printf("error in Matrix_Eig:申请子空间失败\n");
				return NULL;
			}
			rot[i] = (float *)malloc(n * sizeof(float));
			if (rot[i] == NULL)
			{
				printf("error in Matrix_Eig:申请子空间失败\n");
				return NULL;
			}
			mat[i] = (float *)malloc(n * sizeof(float));
			if (mat[i] == NULL)
			{
				printf("error in Matrix_Eig:申请子空间失败\n");
				return NULL;
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == j)
				{
					result[i][j] = 1;
				}
				else
				{
					result[i][j] = 0;
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == j)
				{
					mat[i][j] = 1;
				}
				else
				{
					mat[i][j] = 0;
				}
			}
		}
		max = array[0][1];
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == j)
				{
					continue;
				}
				else
				{
					if (fabs(array[i][j]) >= fabs(max))
					{
						max = array[i][j];
						p = i;
						q = j;
					}
					else
					{
						continue;
					}
				}
			}
		}
		while (fabs(max) > thresh)
		{
			if (fabs(max) < thresh)
			{
				break;
			}
			tan_angle = -2 * array[p][q] / (array[q][q] - array[p][p]);
			sin_angle = sin(0.5*atan(tan_angle));
			cos_angle = cos(0.5*atan(tan_angle));
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{

					if (i == j)
					{
						mat[i][j] = 1;
					}
					else
					{
						mat[i][j] = 0;
					}
				}
			}
			mat[p][p] = cos_angle;
			mat[q][q] = cos_angle;
			mat[q][p] = sin_angle;
			mat[p][q] = -sin_angle;
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					rot[i][j] = array[i][j];
				}
			}
			for (j = 0; j < n; j++)
			{
				rot[p][j] = cos_angle*array[p][j] + sin_angle*array[q][j];
				rot[q][j] = -sin_angle*array[p][j] + cos_angle*array[q][j];
				rot[j][p] = cos_angle*array[j][p] + sin_angle*array[j][q];
				rot[j][q] = -sin_angle*array[j][p] + cos_angle*array[j][q];
			}
			rot[p][p] = array[p][p] * cos_angle*cos_angle + array[q][q] * sin_angle*sin_angle + 2 * array[p][q] * cos_angle*sin_angle;
			rot[q][q] = array[q][q] * cos_angle*cos_angle + array[p][p] * sin_angle*sin_angle - 2 * array[p][q] * cos_angle*sin_angle;
			rot[p][q] = 0.5*(array[q][q] - array[p][p]) * 2 * sin_angle*cos_angle + array[p][q] * (2 * cos_angle*cos_angle - 1);
			rot[q][p] = 0.5*(array[q][q] - array[p][p]) * 2 * sin_angle*cos_angle + array[p][q] * (2 * cos_angle*cos_angle - 1);
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					array[i][j] = rot[i][j];
				}
			}
			max = array[0][1];
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					if (i == j)
					{
						continue;
					}
					else
					{
						if (fabs(array[i][j]) >= fabs(max))
						{
							max = array[i][j];
							p = i;
							q = j;
						}
						else
						{
							continue;
						}
					}
				}
			}
			for (i = 0; i < n; i++)
			{
				eig[i] = array[i][i];
			}
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					sum = 0;
					for (k = 0; k < n; k++)
					{
						sum = sum + result[i][k] * mat[k][j];
					}
					result_temp[i][j] = sum;
				}
			}
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					result[i][j] = result_temp[i][j];
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				array[i][j] = temp_mat[i][j];
			}
		}
		Matrix_Free(result_temp, n, n);
		Matrix_Free(rot, n, n);
		Matrix_Free(mat, n, n);
		Matrix_Free(temp_mat, n, n);
		return result;
	}
}
int Matrix_Free(float **tmp, int m, int n)
{
	int i, j;
	if (tmp == NULL)
	{
		return(1);
	}
	for (i = 0; i < m; i++)
	{
		if (tmp[i] != NULL)
		{
			free(tmp[i]);
			tmp[i] = NULL;
		}
	}
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	return(0);
}
