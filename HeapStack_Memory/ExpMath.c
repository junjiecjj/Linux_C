#include "ExpMath.h"

//===============================================================================================================
//定义基本函数
//===============================================================================================================
float float_round(float x, float y)
{

	float idx;

	idx =floor(x/y+0.5f);

	return idx;
}

int floatint_round(float x, float y)
{

	int    id;

	id=(int) floor(x/y+0.5);

	return id;
}

float float_min(float x, float y)
{
	if(x>y)
	{
		return y;
	}
	else
	{
		return x;
	}

}

float float_max(float x, float y)
{
	if(x>y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

double double_min(double x, double y)
{
	if(x>y)
	{
		return y;
	}
	else
	{
		return x;
	}

}

double double_max(double x, double y)
{
	if(x>y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

float MeanUpdata(float mean_old, float samp_new,  unsigned int N)
{
	float k;
	float mean_temp_old;
	float mean_temp_new;

	k=(float)N;
	mean_temp_old=mean_old;

	mean_temp_new=mean_temp_old*(k-1)/k+samp_new/k;

	return mean_temp_new;
}

float StdUpdata(float mean_old, float std_old, float samp_new,  unsigned int N)
{
	float k;
	float mean_temp_old, std_temp_old, var_temp_old;
	float var_temp_new;
	float temp;

	k=(float)N;
	mean_temp_old=mean_old;
	std_temp_old =std_old;

	var_temp_old=std_temp_old*std_temp_old;

	temp=(mean_temp_old-samp_new)*(mean_temp_old-samp_new)*(k-1)/(k*k);

	var_temp_new=var_temp_old*(k-1)/k+temp;


	std_temp_old=(float) sqrt(var_temp_new);

	return std_temp_old;
}


void Quick_sort(float *input, unsigned int first,unsigned int end,unsigned int *idx)
{
	unsigned int i,j,Itemp;
	float Ftemp;

	i=first;  j=end;
	Ftemp=input[i];
	Itemp=idx[i];

	while(i<j)
	{
		while(i<j && Ftemp<input[j])
		{
			j--;
		}
		input[i]=input[j];  idx[i]=idx[j];

		while(i<j && input[i]<=Ftemp)
		{
			i++;
		}
		input[j]=input[i];  idx[j]=idx[i];

	}
	input[i]=Ftemp;     idx[i]=Itemp;


	if(first<i-1 && i>=1)
	{
		Quick_sort(input,first,i-1,idx);
	}

	if(i+1<end)
	{
		Quick_sort(input,i+1,end,idx);
	}

	return;
}


void Quick_sort_noidx(float *input, unsigned int first, unsigned int end)
{
	unsigned int i,j;
	float Ftemp;

	i=first;  j=end;
	Ftemp=input[i];

	while(i<j)
	{
		while(i<j && Ftemp<input[j])
		{
	    	j--;
		}
		input[i]=input[j];

	    while(i<j && input[i]<=Ftemp)
	    {
	    	i++;
	    }
	    input[j]=input[i];

	}
	input[i]=Ftemp;


	if(first<i-1 && i>=1)
	{
	    Quick_sort_noidx(input,first,i-1);
	}

	if(i+1<end)
	{
	    Quick_sort_noidx(input,i+1,end);
	}

	return;
}

void Quick_sort_int(unsigned int *input, unsigned int first,unsigned int end)
{
	unsigned int i,j;
	unsigned int Ftemp;

	i=first;  j=end;
	Ftemp=input[i];

	while(i<j)
	{
		while(i<j && Ftemp<input[j])
		{
			j--;
		}
		input[i]=input[j];

		while(i<j && input[i]<=Ftemp)
		{
			i++;
		}
		input[j]=input[i];

	}
	input[i]=Ftemp;


	if(first<i-1 && i>=1)
	{
		Quick_sort_int(input,first,i-1);
	}

	if(i+1<end)
	{
		Quick_sort_int(input,i+1,end);
	}

	return;
}

void double_qsort_noidx(double *input,unsigned int first,unsigned int end)
{
	unsigned int i,j;

	double Ftemp;

	i=first;  j=end;
	Ftemp=input[i];

	while(i<j)
	{
		while(i<j && Ftemp<input[j])
		{
			j--;
		}
		input[i]=input[j];

		while(i<j && input[i]<=Ftemp)
		{
			i++;
		}
		input[j]=input[i];

	}
	input[i]=Ftemp;


	if(first<i-1 && i>=1)
	{
		double_qsort_noidx(input,first,i-1);
	}

	if(i+1<end)
	{
		double_qsort_noidx(input,i+1,end);
	}

}


float float_median(float *input, unsigned int N)
{
	float			temp;

	unsigned int	id;

	float			idx =N/2;

	Quick_sort_noidx(input, 0, N-1);

	id=( unsigned int) floor(idx);  //中值索引

	temp=input[id];

	return temp;
}


double double_median(double *input,  unsigned int N)
{
	double		temp;

	unsigned int id;

	double		idx = N/2;

	double_qsort_noidx(input, 0, N-1);

	id=( unsigned int) floor(idx);  //中值索引

	temp=input[id];

	return temp;
}



float float_mean(float *input, unsigned int N)
{
	 unsigned int i;
	float temp;

	temp=0;
	for(i=0;i<N;i++)
	{
	    temp=temp+input[i];
	}
	temp=temp/N;

	return temp;
}

float float_std(float *input,  unsigned int N, float fmean)
{
	unsigned int i;
	float temp;

	temp=0;
	for(i=0;i<N;i++)
	{
	    temp=temp+(input[i]-fmean)*(input[i]-fmean);
	}
	temp=(float) sqrt(temp/N);

	return temp;
}


float float_robust_mean(float *input,unsigned int N)
{
//	unsigned int i;
	float temp;

	temp=float_median(input,N);

	return temp;
}


float float_robust_std(float *input, unsigned int N)
{
	unsigned int i;

	float temp;

	float diff[VECTER_COMPUT_MAX_LEN];

	temp=float_median(input,N);		 //计算均值

	for(i=0;i<N;i++)
	{
		diff[i]=fabs(input[i]-temp);
	}

	temp=float_median(diff, N)/0.6745f;

	return temp;
}

float double_robust_mean(double *input,unsigned int N)
{
	float temp;

	temp=(float) double_median(input,N);

	return temp;
}


float double_robust_std(double *input, unsigned int N)
{
	unsigned int i;

	float temp;

	double diff[VECTER_COMPUT_MAX_LEN];

	temp=(float) double_median(input,N);		 //计算均值

	for(i=0;i<N;i++)
	{
		diff[i]=fabs(input[i]-temp);
	}

	temp=(float) double_median(diff, N)/0.6745f;

	return temp;
}


float float_vector_min(float *input, unsigned int N)
{
	unsigned int i;
	float temp;

	temp=input[0];
	for(i=1;i<N;i++)
	{
		if(temp>input[i])
		{
			temp=input[i];
		}
	}
	return temp;
}

float float_vector_max(float *input, unsigned int N)
{
	unsigned int i;
	float temp;

	temp=input[0];
	for(i=1;i<N;i++)
	{
		if(temp<input[i])
		{
			temp=input[i];
		}
	}
	return temp;
}

double double_vector_min(double *input, unsigned int N)
{
	unsigned int i;
	double temp;

	temp=input[0];
	for(i=1;i<N;i++)
	{
		if(temp>input[i])
		{
			temp=input[i];
		}
	}
	return temp;
}

double double_vector_max(double *input, unsigned int N)
{
	unsigned int i;
	double temp;

	temp=input[0];
	for(i=1;i<N;i++)
	{
		if(temp<input[i])
		{
			temp=input[i];
		}
	}
	return temp;
}


float VecMeanUpdata(float mean_old, unsigned int M, float mean_new, unsigned int N)
{
	float mean_temp_new;

	mean_temp_new=mean_old*M/(M+N)+mean_new*N/(M+N);
	return mean_temp_new;
}

float VecStdUpdata(float mean_old, float std_old,unsigned int M, float mean_new,float std_new, unsigned int N)
{

	float var_old, var_new;;
	float var_temp_new;
	float new_std;
	float temp;

	var_old=std_old*std_old;

	var_new=std_new*std_new;

	temp=(mean_old-mean_new)*(mean_old-mean_new)*M*N/((M+N)*(M+N));

	var_temp_new=var_old*M/(M+N)+var_new*N/(M+N)+temp;

	new_std=(float) sqrt(var_temp_new);

	return new_std;
}


unsigned int vector_min(float *input, unsigned int N)
{
	unsigned int i,idx;
	float temp;

	temp=input[0];
	idx=0;
	for(i=1;i<N;i++)
	{
		if(temp>input[i])
		{
			temp=input[i];
			idx=i;
		}
	}
	return idx;
}

unsigned int vector_max(double *input, unsigned int N)
{
	unsigned int i,idx;
	double temp;

	temp=input[0];
	idx=0;
	for(i=1;i<N;i++)
	{
		if(temp<input[i])
		{
			temp=input[i];
			idx=i;
		}
	}
	return idx;
}

 /**********************************************************************************************************
 程序说明：复数的基本运算
 函数形式：

	COMPLEX complex_adder(COMPLEX xdata, COMPLEX ydata)

	COMPLEX complex_diff(COMPLEX xdata, COMPLEX ydata)

	COMPLEX complex_multiper(COMPLEX xdata, COMPLEX ydata)

	COMPLEX complex_divider(COMPLEX xdata, COMPLEX ydata)

	float	complex_abs(COMPLEX xdata)

	float	complex_conj(COMPLEX xdata)

	float	complex_phase(COMPLEX xdata)

	COMPLEX complex_conj_multiper(COMPLEX xdata, COMPLEX ydata)

 *********************************************************************************************************/
COMPLEX complex_adder(COMPLEX xdata, COMPLEX ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			yreal = ydata.real;

	float			yimag = ydata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;

	//加法
	zreal = xreal + yreal;

	zimag = ximag + yimag;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}

COMPLEX complex_diff(COMPLEX xdata, COMPLEX ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			yreal = ydata.real;

	float			yimag = ydata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;

	//减法
	zreal = xreal - yreal;

	zimag = ximag - yimag;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}

COMPLEX complex_multiper(COMPLEX xdata, COMPLEX ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			yreal = ydata.real;

	float			yimag = ydata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;

	//乘法
	zreal = xreal * yreal - ximag * yimag;

	zimag = xreal * yimag + ximag * yreal;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}

float	complex_abs(COMPLEX xdata)
{
	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			amp_sqr	= 0.0;

	//求模
	amp_sqr = sqrt(xreal * xreal + ximag * ximag);

	return	amp_sqr;

}

COMPLEX	complex_conj(COMPLEX xdata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	zdata.real	= xreal;

	zdata.imag	= -1.0 * ximag;

	return  zdata;
}


COMPLEX complex_divider(COMPLEX xdata, COMPLEX ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			yreal = ydata.real;

	float			yimag = ydata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;

	float			amp_sqrt = 0.0;

	//除法
	amp_sqrt	=	complex_abs(ydata);

	zreal = xreal * yreal + ximag * yimag;

	zimag = ximag * yreal - xreal * yimag;

	zdata.real = zreal / (amp_sqrt * amp_sqrt);

	zdata.imag = zimag / (amp_sqrt * amp_sqrt);

	return  zdata;
}

float complex_phase(COMPLEX xdata)
{
	float			phase = 0.0;

	//相位
	phase = atan2( xdata.imag, xdata.real );

	return  phase;
}

COMPLEX complex_conj_multiper(COMPLEX xdata, COMPLEX ydata)
{
	COMPLEX			zdata;

	COMPLEX			mdata;


	//共轭乘法
	mdata = complex_conj(ydata);

	zdata = complex_multiper(xdata, mdata);

	return  zdata;
}

/**********************************************************************************************************
 程序说明：复数与实数的基本运算
 函数形式：

	COMPLEX complex_float_adder(COMPLEX xdata, float ydata)

	COMPLEX complex_float_diff(COMPLEX xdata,  float ydata)

	COMPLEX complex_float_multiper(COMPLEX xdata, float ydata)

	COMPLEX complex_float_divider(COMPLEX xdata, float ydata)

  	COMPLEX float_complex_divider(float xdata, COMPLEX ydata)
 *********************************************************************************************************/
COMPLEX complex_float_adder(COMPLEX xdata, float ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;

	//加法
	zreal = xreal + ydata;

	zimag = ximag + ydata;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}

COMPLEX complex_float_diff(COMPLEX xdata, float ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;


	float			zreal = 0.0;

	float			zimag = 0.0;

	//减法
	zreal = xreal - ydata;

	zimag = ximag - ydata;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}

COMPLEX complex_float_multiper(COMPLEX xdata, float ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;


	float			zreal = 0.0;

	float			zimag = 0.0;

	//乘法
	zreal = xreal * ydata;

	zimag = ximag * ydata;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}



COMPLEX complex_float_divider(COMPLEX xdata, float ydata)
{
	COMPLEX			zdata;

	float			xreal = xdata.real;

	float			ximag = xdata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;


	//除法
	zreal = xreal / ydata;

	zimag = ximag / ydata;

	zdata.real = zreal;

	zdata.imag = zimag;

	return  zdata;
}

COMPLEX float_complex_divider(float xdata, COMPLEX ydata)
{
	COMPLEX			zdata;

	float			yreal = ydata.real;

	float			yimag = ydata.imag;

	float			zreal = 0.0;

	float			zimag = 0.0;

	float			amp_sqrt = 0.0;

	//除法
	amp_sqrt	=	complex_abs(ydata);

	zreal =		 xdata * yreal;

	zimag = -1 * xdata * yimag;

	zdata.real = zreal / (amp_sqrt * amp_sqrt);

	zdata.imag = zimag / (amp_sqrt * amp_sqrt);

	return  zdata;
}


/**********************************************************************************************************
 程序说明：复数矩阵的基本运算
 函数形式：

	CMATRIX complex_matrix_adder(CMATRIX xdata, CMATRIX ydata)

	CMATRIX complex_matrix_diff(CMATRIX xdata,  CMATRIX ydata)

	CMATRIX complex_matrix_multiper(CMATRIX xdata, CMATRIX ydata)

	CMATRIX complex_matrix_point_multiper(CMATRIX xdata, CMATRIX ydata)

  	CMATRIX complex_matrix_point_divider(CMATRIX xdata, CMATRIX ydata)
 *********************************************************************************************************/
 CMATRIX complex_matrix_adder(CMATRIX xdata, CMATRIX ydata)
 {
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	CMATRIX				zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

//	unsigned int		yMatrixRow = ydata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

//	unsigned int		yMatrixCol = ydata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixRow;

	zdata.MatrixRow = xMatrixCol;

	//计算矩阵和
	for (knum=0; knum< xMatrixCol; knum++)
	{
		for (gnum=0; gnum<xMatrixRow; gnum++)
		{
			zdata.ArrayMatrix[knum][gnum] = complex_adder(xdata.ArrayMatrix[knum][gnum], ydata.ArrayMatrix[knum][gnum]);
		}
	}

	return zdata;
 }


 CMATRIX complex_matrix_diff(CMATRIX xdata, CMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 CMATRIX				zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

//	 unsigned int		yMatrixRow = ydata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;

//	 unsigned int		yMatrixCol = ydata.MatrixCol;

	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixRow;

	 zdata.MatrixRow = xMatrixCol;

	 //计算矩阵差
	 for (knum=0; knum< xMatrixCol; knum++)
	 {
		 for (gnum=0; gnum<xMatrixRow; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum] = complex_diff(xdata.ArrayMatrix[knum][gnum], ydata.ArrayMatrix[knum][gnum]);
		 }
	 }

	 return zdata;
 }

 //Z=X*Y
 CMATRIX complex_matrix_multiper(CMATRIX xdata, CMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 unsigned int		fnum = 0;

	 CMATRIX			zdata;

	 COMPLEX			temp;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

//	 unsigned int		yMatrixRow = ydata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;

	 unsigned int		yMatrixCol = ydata.MatrixCol;

	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixRow;

	 zdata.MatrixRow = yMatrixCol;

	 //计算矩阵乘法
	 for (knum=0; knum< xMatrixRow; knum++)
	 {
		 for (gnum=0; gnum<yMatrixCol; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum].real = 0.0;

			 zdata.ArrayMatrix[knum][gnum].imag = 0.0;

			 for (fnum =0 ; fnum<xMatrixCol; fnum++)
			 {
				 temp = complex_multiper(xdata.ArrayMatrix[knum][fnum], ydata.ArrayMatrix[fnum][gnum]);

				 zdata.ArrayMatrix[knum][gnum] = complex_adder(temp, zdata.ArrayMatrix[knum][gnum]);
			 }
		 }
	 }

	 return zdata;
 }

//Z = X .* Y
CMATRIX complex_matrix_point_multiper(CMATRIX xdata, CMATRIX ydata)
{
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	CMATRIX				zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

//	unsigned int		yMatrixRow = ydata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

//	unsigned int		yMatrixCol = ydata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixCol;

	zdata.MatrixRow = xMatrixRow;

	//计算矩阵差
	for (knum=0; knum< xMatrixCol; knum++)
	{
		for (gnum=0; gnum<xMatrixRow; gnum++)
		{
			zdata.ArrayMatrix[gnum][knum] = complex_multiper(xdata.ArrayMatrix[gnum][knum], ydata.ArrayMatrix[gnum][knum]);
		}
	}

	return zdata;
}


//Z = X ./ Y
CMATRIX complex_matrix_point_divider(CMATRIX xdata, CMATRIX ydata)
{
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	CMATRIX				zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

//	unsigned int		yMatrixRow = ydata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

//	unsigned int		yMatrixCol = ydata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixCol;

	zdata.MatrixRow = xMatrixRow;

	//计算矩阵差
	for (knum=0; knum< xMatrixCol; knum++)
	{
		for (gnum=0; gnum<xMatrixRow; gnum++)
		{
			zdata.ArrayMatrix[gnum][knum] = complex_divider(xdata.ArrayMatrix[gnum][knum], ydata.ArrayMatrix[gnum][knum]);
		}
	}

	return zdata;
}

/**********************************************************************************************************
 程序说明：复数矩阵与复数常数的基本运算
 函数形式：

		CMATRIX	complex_matrix_constant_adder(CMATRIX xdata, COMPLEX ydata);

		CMATRIX complex_matrix_constant_diff(CMATRIX xdata, COMPLEX ydata);

		CMATRIX complex_matrix_constant_multiper(CMATRIX xdata, COMPLEX ydata);


 运行平台：MPC8640D
 版本号  ：1.0
 编写作者：贾可新
 编写日期：2015.03.28
 *********************************************************************************************************/
 CMATRIX complex_matrix_constant_adder(CMATRIX xdata, COMPLEX ydata)
 {
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	CMATRIX				zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixRow;

	zdata.MatrixRow = xMatrixCol;

	//计算矩阵和
	for (knum=0; knum< xMatrixCol; knum++)
	{
		for (gnum=0; gnum<xMatrixRow; gnum++)
		{
			zdata.ArrayMatrix[knum][gnum] = complex_adder(xdata.ArrayMatrix[knum][gnum], ydata);
		}
	}

	return zdata;
 }


 CMATRIX complex_matrix_constant_diff(CMATRIX xdata, COMPLEX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 CMATRIX			zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;

	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixRow;

	 zdata.MatrixRow = xMatrixCol;

	 //计算矩阵差
	 for (knum=0; knum< xMatrixCol; knum++)
	 {
		 for (gnum=0; gnum<xMatrixRow; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum] = complex_diff(xdata.ArrayMatrix[knum][gnum], ydata);
		 }
	 }

	 return zdata;
 }

 //Z=X*Y
 CMATRIX complex_matrix_constant_multiper(CMATRIX xdata, COMPLEX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

//	 unsigned int		fnum = 0;

	 CMATRIX			zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;

	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixCol;

	 zdata.MatrixRow = xMatrixRow;

	 //计算矩阵乘法
	 for (knum=0; knum< xMatrixRow; knum++)
	 {
		 for (gnum=0; gnum<xMatrixCol; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum] = complex_multiper(xdata.ArrayMatrix[knum][gnum] , ydata);
		 }
	 }

	 return zdata;
 }

 /**********************************************************************************************************
  程序说明：本程序用于将浮点型频率值转换为定点型频率值
  函数形式：

	 int radio_freq_translate(float RadioFreq, unsigned int QuanBit, float SampFreq);


  运行平台：MPC8640D
  版本号  ：1.0
  编写作者：贾可新
  编写日期：2015.03.28
  *********************************************************************************************************/
 int radio_freq_translate(float RadioFreq, unsigned int QuanBit, float SampFreq)
 {
	 unsigned int	QuanPowMax = (unsigned int) pow(2.0f, (int)QuanBit);

	 int			iRadioFreq = 0;


	 if(RadioFreq>0)
	 {
		 iRadioFreq = floatint_round(QuanPowMax * RadioFreq, SampFreq);
	 }
	 else
	 {
		 iRadioFreq =QuanPowMax - floatint_round(QuanPowMax * fabs(RadioFreq), SampFreq);
	 }


	 return iRadioFreq;

 }

 /**********************************************************************************************************
 程序说明：实数矩阵的基本运算
 函数形式：

 RMATRIX real_matrix_adder(RMATRIX xdata, RMATRIX ydata);

 RMATRIX real_matrix_diff(RMATRIX xdata,  RMATRIX ydata);

 RMATRIX real_matrix_multiper(RMATRIX xdata, RMATRIX ydata);

 RMATRIX real_matrix_point_multiper(RMATRIX xdata, RMATRIX ydata);

 RMATRIX real_matrix_point_divider(RMATRIX xdata, RMATRIX ydata);


 运行平台：DSP
 版本号  ：1.0
 编写作者：贾可新
 编写日期：2016.07.05
 *********************************************************************************************************/
 RMATRIX real_matrix_adder(RMATRIX xdata, RMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 RMATRIX			zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;


	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixRow;

	 zdata.MatrixRow = xMatrixCol;

	 //计算矩阵和
	 for (knum=0; knum< xMatrixCol; knum++)
	 {
		 for (gnum=0; gnum<xMatrixRow; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum] = xdata.ArrayMatrix[knum][gnum] + ydata.ArrayMatrix[knum][gnum];
		 }
	 }

	 return zdata;
 }


 RMATRIX real_matrix_diff(RMATRIX xdata, RMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 RMATRIX			zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;


	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixRow;

	 zdata.MatrixRow = xMatrixCol;

	 //计算矩阵差
	 for (knum=0; knum< xMatrixCol; knum++)
	 {
		 for (gnum=0; gnum<xMatrixRow; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum] = xdata.ArrayMatrix[knum][gnum] - ydata.ArrayMatrix[knum][gnum];
		 }
	 }

	 return zdata;
 }

 //Z=X*Y
 RMATRIX real_matrix_multiper(RMATRIX xdata, RMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 unsigned int		fnum = 0;

	 RMATRIX			zdata;

	 float				temp;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;

	 unsigned int		yMatrixCol = ydata.MatrixCol;

	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixRow;

	 zdata.MatrixRow = yMatrixCol;

	 //计算矩阵乘法
	 for (knum=0; knum< xMatrixRow; knum++)
	 {
		 for (gnum=0; gnum<yMatrixCol; gnum++)
		 {
			 zdata.ArrayMatrix[knum][gnum] = 0.0;

			 for (fnum =0 ; fnum<xMatrixCol; fnum++)
			 {
				 temp = xdata.ArrayMatrix[knum][fnum] * ydata.ArrayMatrix[fnum][gnum];

				 zdata.ArrayMatrix[knum][gnum] = temp + zdata.ArrayMatrix[knum][gnum];
			 }
		 }
	 }

	 return zdata;
 }

 //Z = X .* Y
 RMATRIX real_matrix_point_multiper(RMATRIX xdata, RMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 RMATRIX				zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;

	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixCol;

	 zdata.MatrixRow = xMatrixRow;

	 //计算矩阵差
	 for (knum=0; knum< xMatrixCol; knum++)
	 {
		 for (gnum=0; gnum<xMatrixRow; gnum++)
		 {
			 zdata.ArrayMatrix[gnum][knum] = xdata.ArrayMatrix[gnum][knum] * ydata.ArrayMatrix[gnum][knum];
		 }
	 }

	 return zdata;
 }


 //Z = X ./ Y
 RMATRIX real_matrix_point_divider(RMATRIX xdata, RMATRIX ydata)
 {
	 unsigned int		knum = 0;

	 unsigned int		gnum = 0;

	 RMATRIX				zdata;

	 //提取行号
	 unsigned int		xMatrixRow = xdata.MatrixRow;

	 //提取列号
	 unsigned int		xMatrixCol = xdata.MatrixCol;


	 //存储矩阵的行号和列号
	 zdata.MatrixCol = xMatrixCol;

	 zdata.MatrixRow = xMatrixRow;

	 //计算矩阵差
	 for (knum=0; knum< xMatrixCol; knum++)
	 {
		 for (gnum=0; gnum<xMatrixRow; gnum++)
		 {
			 zdata.ArrayMatrix[gnum][knum] = xdata.ArrayMatrix[gnum][knum] / ydata.ArrayMatrix[gnum][knum];
		 }
	 }

	 return zdata;
 }

 /**********************************************************************************************************
 程序说明：实数矩阵与常数的基本运算
 函数形式：

 RMATRIX	real_matrix_constant_adder(RMATRIX xdata, float ydata);

 RMATRIX	real_matrix_constant_diff(RMATRIX xdata, float ydata);

 RMATRIX	real_matrix_constant_multiper(RMATRIX xdata, float ydata);


 运行平台：DSP
 版本号  ：1.0
 编写作者：贾可新
 编写日期：2016.07.05
 *********************************************************************************************************/
RMATRIX real_matrix_constant_adder(RMATRIX xdata, float ydata)
{
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	RMATRIX			zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixRow;

	zdata.MatrixRow = xMatrixCol;

	 //计算矩阵和
	for (knum=0; knum< xMatrixCol; knum++)
	{
		for (gnum=0; gnum<xMatrixRow; gnum++)
		{
			zdata.ArrayMatrix[knum][gnum] = xdata.ArrayMatrix[knum][gnum] + ydata;
		}
	}

	return zdata;
}


RMATRIX real_matrix_constant_diff(RMATRIX xdata, float ydata)
{
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	RMATRIX			zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixRow;

	zdata.MatrixRow = xMatrixCol;

	 //计算矩阵差
	for (knum=0; knum< xMatrixCol; knum++)
	{
		for (gnum=0; gnum<xMatrixRow; gnum++)
		{
			zdata.ArrayMatrix[knum][gnum] = xdata.ArrayMatrix[knum][gnum] - ydata;
		}
	}

	return zdata;
}

 //Z=X*Y
RMATRIX real_matrix_constant_multiper(RMATRIX xdata, float ydata)
{
	unsigned int		knum = 0;

	unsigned int		gnum = 0;


	RMATRIX			zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixCol;

	zdata.MatrixRow = xMatrixRow;

	//计算矩阵乘法
	for (knum=0; knum< xMatrixRow; knum++)
	{
		for (gnum=0; gnum<xMatrixCol; gnum++)
		{
			zdata.ArrayMatrix[knum][gnum] = xdata.ArrayMatrix[knum][gnum] * ydata;
		}
	}

	return zdata;
}
 //求解矩阵行列式的值
float Matrix_Determinant(RMATRIX arcs,int n)//按第一行展开计算|A|
{

	if(n==1)
		return arcs.ArrayMatrix[0][0];

	float ans = 0.0;

	RMATRIX  temp;

	temp.MatrixRow = n;
	temp.MatrixCol = n;

	int i,j,k;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n-1; j++)
		{
			for(k = 0;k < n -1; k++)
			{
				temp.ArrayMatrix[j][k] = arcs.ArrayMatrix[j+1][(k>=i)?k+1:k];
			}
		}
		float t = Matrix_Determinant(temp,n-1);
		if(i%2 == 0)
		{
			ans += arcs.ArrayMatrix[0][i]*t;
		}
		else
			ans -= arcs.ArrayMatrix[0][i]*t;
	}
	return  ans;
}
  //Z=X/Y
RMATRIX real_matrix_constant_divider(RMATRIX xdata, float ydata)
{
	unsigned int		knum = 0;

	unsigned int		gnum = 0;

	RMATRIX			zdata;

	//提取行号
	unsigned int		xMatrixRow = xdata.MatrixRow;

	//提取列号
	unsigned int		xMatrixCol = xdata.MatrixCol;

	//存储矩阵的行号和列号
	zdata.MatrixCol = xMatrixCol;

	zdata.MatrixRow = xMatrixRow;

	//计算矩阵乘法
	for (knum=0; knum< xMatrixRow; knum++)
	{
		for (gnum=0; gnum<xMatrixCol; gnum++)
		{
			zdata.ArrayMatrix[knum][gnum] = xdata.ArrayMatrix[knum][gnum] / ydata;
		}
	}

	return zdata;
}
 //A-1
RMATRIX Matrix_Invers(RMATRIX acr,int n)
{
	float r = Matrix_Determinant( acr, n);

	RMATRIX result,invers;

	Matrix_Adjoint(acr,n,&result);

	invers = real_matrix_constant_divider(result,r);

	return invers;
}

//求解矩阵的伴随矩阵
void Matrix_Adjoint(RMATRIX arcs,int n,RMATRIX *ans)//计算每一行每一列的每个元素所对应的余子式，组成A*
{
	ans->MatrixCol = arcs.MatrixCol;
	ans->MatrixRow = arcs.MatrixRow;

	if(n == 1)
	{
		ans->ArrayMatrix[0][0] = 1;
		return;
	}

	int i,j,k,t;
	RMATRIX temp;

	temp.MatrixCol = arcs.MatrixCol;
	temp.MatrixRow = arcs.MatrixRow;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n-1;k++)
			{
				for(t=0;t<n-1;t++)
				{
					temp.ArrayMatrix[k][t] = arcs.ArrayMatrix[k>=i?k+1:k][t>=j?t+1:t];
				}
			}
			ans->ArrayMatrix[j][i] = Matrix_Determinant(temp,n-1);
			if((i+j)%2 ==  1)
				ans->ArrayMatrix[j][i] = -ans->ArrayMatrix[j][i];
		}
	}
}

void find_max_ID_In_Matrix(RMATRIX *arcs,int *rMaxId,int *cMaxId)
{
	int		cID = 0,rID = 0;

    int		i = 0;
    int     j = 0;

	int		cnum = arcs->MatrixCol;	//行号

	int		rnum = arcs->MatrixRow;	//列号

	float	Temp = arcs->ArrayMatrix[0][0];

    for(i = 0; i < rnum; i++)
	{
        for(j = 0; j < cnum; j++)
		{
			if(arcs->ArrayMatrix[rnum][cnum] > Temp)
			{
				Temp = arcs->ArrayMatrix[rnum][cnum];

				cID = cnum;

				rID = rnum;
			}
		}
	}

	*cMaxId = cnum;

	*rMaxId = rnum;
}

/**********************************************************************************************************
程序说明：寻找value在长度为dlen的序列dmin:dstep:dmax中位置，注意，在matlab中数组从1开始，不是零
函数形式：
		void find_local_comput(float value,float dmax,float dmin, float dstep, unsigned short dlen, unsigned short *local)
参数说明：
		*local ：value值的索引值

 *********************************************************************************************************/
void find_local_comput(float value,float dmax,float dmin, float dstep, unsigned short dlen, unsigned short *local)
{
	//printf("vRead_Sum_Diff_Table %ld %ld %ld %u %ld\n", g_DBFSumDiffTable.FreqMax, g_DBFSumDiffTable.FreqMin, g_DBFSumDiffTable.FreqStep, g_DBFSumDiffTable.FreqLen,g_HJSysParm.f0);

	if(value >= dmax)
		*local = dlen;
	else if(value <= dmin)
		*local = 1;
	else
		*local = (int)((float)(value-dmin)/dstep+1 + 0.5);

}
unsigned short find_local_comput_HJ(long value,long dmax,long dmin, double dstep, unsigned short dlen)
{
	// printf("vRead_Sum_Diff_Table %ld %ld %ld\n", value, dmax,dmin);
	unsigned short local = 0;
	if(value >= dmax)
	{
		local = dlen-1;

	}
	else if(value <= dmin)
	{
		local = 1;
	}
	else
	{
		local = (int)((double)(value-dmin)/dstep + 0.5);
	}

	return local;
}


/*****************************************************************************
函数名：    dCalDeltaAzimuth
描述:        计算两方位夹角
详细描述：    计算两方位之间的夹角
参数:        方位1，方位2
返回值：    夹角
注意事项:    无
函数定义:
******************************************************************************/
double dCalDeltaAzimuth(double Course1,double Course2)
{
    /*! @par 处理步骤 */
    double DeltaC;

    /*! -# 计算方位夹角*/
    DeltaC = fabs(Course1 - Course2);

    /*! -# 对方位夹角做归一化处理*/
    if(DeltaC > 180)
    {
        DeltaC = 360 - DeltaC;
    }

    return DeltaC;
}
