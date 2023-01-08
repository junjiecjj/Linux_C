#ifndef _VARIABLE_H
#define _VARIABLE_H

/*********************************定义系统常数*************************************************************/
#define				PI            3.141592653589793f
#define             BEAM_NUM      3	//波束个数


/******************************************定义复数结构体类型****************************************************/

//定义浮点型-实部和虚部-复数结构体表示
typedef struct _COMPLEX
{
	float	real; //实部

	float	imag; //虚部

} COMPLEX;

//定义16bit定点型-实部和虚部-复数结构体表示
typedef struct _COMPLEX_INT16
{
	short	imag; //虚部

	short	real; //实部

} COMPLEX_INT16;

//定义32bit定点型-实部和虚部-复数结构体表示
typedef struct _COMPLEX_INT32
{
	int		imag; //虚部

	int		real; //实部

} COMPLEX_INT32;

//定义复数矩阵运算的结构体
typedef struct _CMATRIX
{
	unsigned int	MatrixRow;		//行数

	unsigned int	MatrixCol;		//列数

	COMPLEX			ArrayMatrix[BEAM_NUM][BEAM_NUM];//矩阵

} CMATRIX;

//定义实数矩阵运算结构体
typedef struct _RMATRIX
{
	unsigned int	MatrixRow;		//行数

	unsigned int	MatrixCol;		//列数

	float			ArrayMatrix[BEAM_NUM][BEAM_NUM];//矩阵

} RMATRIX;

/******************************************定义控制参数格式****************************************************/



#endif
