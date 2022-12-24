#ifndef _COORDINATE_CJJ
#define _COORDINATE_CJJ

/*-包含头文件------------------------------------------------------------------------------------*/
#include "coordinate.h"
#include "Public.h"
#include "RamRefLib.h"


/************************************************************************
 *  Function Name:	hypot_3
 *
 *  Description:
 *
 *
 *
 *
 *  Return Value:	None.
 ***************************************************************************/
DOUBLE
hypot_3(
		DOUBLE       X,
		DOUBLE       Y,
		DOUBLE       Z
)
{
	DOUBLE Value = 0;

	Value = sqrt(X*X + Y*Y + Z*Z);

	return Value;
}

/************************************************************************
 *  Function Name:	dMyRand
 *
 *  Description:
 *					随机数发生器--产生0和1之间的随机数(32bit)
 *					64bit 需修改最大整数值
 *
 *
 *  Return Value:	None.
 ***************************************************************************/
DOUBLE dRand()
{
	DOUBLE Temp = 0;

	/*初始化*/
	/*	srand( (unsigned)time( NULL ) );*/

	/*随机数*/
	Temp = (DOUBLE)rand() / RAND_MAX;

	return Temp ;
}


/*****************************************************************************

函数名：	atan2XY

描述:		根据(x,y)计算角度

详细描述：
            根据(x,y)计算角度，单位为弧度


参数:		位置x,y

返回值：	角度0 -- 2π

注意事项:	无

函数定义:
 ******************************************************************************/
DOUBLE atan2XY(DOUBLE x, DOUBLE y)
{
	DOUBLE r;

	if((fabs(x) < ALMOST_ZERO) && (fabs(y) < ALMOST_ZERO))
		return	0;

	r = atan2(x,y);
	if(r < 0.0)
		r += M_2PI;

	return	r;
}

void Coordinate_GetInitationParas(double *a, double *b, double *f, double *e2, double *ep2, double *r0)
{
	*a = 6378137.0;
	*b = 6356752.3142;
	*f = ((*a)-(*b))/(*a);
	*e2 = 2*(*f)-(*f)*(*f);
	*ep2 = (*f)*(2-(*f))/((1-(*f))*(1-(*f)));
	*r0 = 6370.0*1000;

}


/*经纬高  --> 地心系x,y,z*/
void Coordinate_WGS84ToECEF(double Lon, double Lat, double Height, double *X, double *Y, double *Z);



/*Range:(m),Azimuth:(deg), Elevation:(deg)*/
void Coordinate_PolarToRightAngle(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z);


/*Xr, Yr, Zr, e, n, u:(m), refLat,refLon:(deg)*/
void Coordinate_ENUToECEF(double Xr, double Yr, double Zr, double e, double n, double u, double refLat, double refLon, double *x, double *y, double *z);

void Coordinate_ECEFToWGS84(double X, double Y, double Z, double *lamda, double *phi, double *h);



void Coordinate_PolarHToPolar(double Range, double Azimuth, double Height, double L, double B, double H, double *Range0, double *Azimuth0, double *Elevation0);


void Coordinate_PolarToWGS84(double Range, double Azimuth, double Height, double Plat, double Plon, double Pht, double *Tlat, double *Tlon, double *Th);

// 地心系(地心地固系)到大地系(东北天、站心系)
void Coordinate_ECEFToENU(double Xr, double Yr, double Zr, double X, double Y, double Z, double refLon, double refLat, double *e, double *n, double *u);

//大地系(东北天、站心系) x,y,z -->  方位俯仰
void Coordinate_RightAngleToPolar(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation);

void Coordinate_RightAngleToPolar_XX(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation);


void Coordinate_eplanexyzToaer_HJ(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation);


void Coordinate_ACUxyzToaer_HJ(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation);

// hj ACUxyz ---AER
void Coordinate_ACUxyzToaer_HJ_Pro(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation);

// hj ACU AER to xyz
void Coordinate_ACUaerToxyz_HJ_Pro(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z);

// hj eplane xyz to aer
void Coordinate_eplaneaerToxyz_HJ_Pro(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z);

// hj 阵面 AER ---xyz
void Coordinate_eplaneAerToXyz_HJ(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z);


void Coordinate_WGS84ToPolarE(double Lon, double Lat, double Height, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation);


void Coordinate_WGS84ToPolarPro(int mode,int i,double yaw,double X, double Y, double Z, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation);

// 数引，程引、同站数据处理
void Coordinate_HJWGS84ToPolarPro(int mode,int i,double yaw,double X, double Y, double Z, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation);



// 数引，程引、同站数据处理
void Coordinate_HJWGS84ToPolarPro2(int mode,int i,double yaw,double X, double Y, double Z, double Plat, double Plon, double Pht, double *Range1, double *Azimuth1, double *Elevation1);

void Coordinate_CarAERToENUAER_XX(int i,double yaw,double Range, double Azimuth, double Elevation, double *R, double *Az, double *Ele);

void Coordinate_ENUToWGS84(double e, double n, double u, double StaLong, double StaLat, double StaHeight, double *Tlat, double *Tlon, double *Th);



void Coordinate_WGS84ToPolarSTK(double Ranged, double Azimuthd, double Elevationd, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation);

/*
	double yaw 指北误差
	根据车头的指北误差, 将ENU坐标系转到车的坐标系下
 */
void Coordinate_ENUToCarPosition(double yaw1, double e, double n, double u, double *x, double *y, double *z);

/*Range:(m),Azimuth:(deg), Elevation:(deg)*/
void Coordinate_PolarToRightAngle_XX(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z);

void Coordinate_PolarToRightAngle_HJ(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z);

unsigned int beam_plane_calc(int mode,float x, float y);// x 方位, y 俯仰

// 绕Y轴逆时针旋转的矩阵
RMATRIX rotat_y_axis_matrix(double az);

// rot RMATRIX  绕Z轴逆时针旋转的矩阵
RMATRIX rotat_z_axis_matrix(double ele);

// rot RMATRIX  绕 横摇 旋转的矩阵
RMATRIX rotat_R_axis_matrix(double aR);

// rot RMATRIX  绕 纵摇 旋转的矩阵
RMATRIX rotat_P_axis_matrix(double aP);

// rot RMATRIX  绕 航向 旋转的矩阵
RMATRIX rotat_H_axis_matrix(double aH)
{
	RMATRIX			zdata;
	double RAzi = 0;
	RAzi = (aH * 1.0) / 180.0*ONEPI;

	//存储矩阵的行号和列号
	zdata.MatrixCol = 3;
	zdata.MatrixRow = 3;

	zdata.ArrayMatrix[0][0] = cos(RAzi);
	zdata.ArrayMatrix[0][1] = 0;
	zdata.ArrayMatrix[0][2] = sin(RAzi);

	zdata.ArrayMatrix[1][0] = 0;
	zdata.ArrayMatrix[1][1] = 1;
	zdata.ArrayMatrix[1][2] = 0;

	zdata.ArrayMatrix[2][0] = -sin(RAzi);
	zdata.ArrayMatrix[2][1] = 0;
	zdata.ArrayMatrix[2][2] = cos(RAzi);

	return zdata;
}


void Coordinate_ServoToCarPosition( double e, double n, double u, double *x, double *y, double *z) //sifu-->zhenmian
{

}

// XX
void Coordinate_XX_enuToCarPosition(double e, double n, double u, double *x, double *y, double *z) //sifu-->zhenmian
{
	// 惯导三角度 注意换算成弧度AAA
	double dRollAngle_rad = 0;
	double dPitchAngle_rad = 0;
	double dYawAngle_rad = 0;

	double fMatrix[3][3];
	double fMatrix2[3][3];
	double fX[3];
	double fX_c[3];
	double fX_c2[3];
	int i;
	int j;
	memset(fX_c,0,3*sizeof(double));
	memset(fX_c2,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));
	// 输入坐标---如果enu-xyz(伺服阵面）
	fX[0] = e;
	fX[1] = n;
	fX[2] = u;
	memset(fMatrix,0,9*sizeof(double));
	fMatrix[0][0] = cos(dYawAngle_rad)*cos(dPitchAngle_rad);
	fMatrix[0][1] = -sin(dYawAngle_rad)*cos(dPitchAngle_rad);
	fMatrix[0][2] = sin(dPitchAngle_rad);
	fMatrix[1][0] = cos(dYawAngle_rad)*sin(dPitchAngle_rad)*sin(dRollAngle_rad) + sin(dYawAngle_rad)*cos(dRollAngle_rad);
	fMatrix[1][1] = cos(dYawAngle_rad)*cos(dRollAngle_rad);
	fMatrix[1][2] = -cos(dPitchAngle_rad)*sin(dRollAngle_rad);
	fMatrix[2][0] = -cos(dYawAngle_rad)*sin(dPitchAngle_rad)*cos(dRollAngle_rad) + sin(dYawAngle_rad)*sin(dRollAngle_rad);
	fMatrix[2][1] = sin(dYawAngle_rad)*sin(dPitchAngle_rad)*cos(dRollAngle_rad)+ cos(dYawAngle_rad)*sin(dRollAngle_rad);
	fMatrix[2][2] = cos(dPitchAngle_rad)*cos(dRollAngle_rad);
	//坐标变换
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			// fX_c[i] += fMatrix[j][i]*fX[j];//乘矩阵的转置fMatrix[i][j]
			fX_c[i] += fMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}
	*x = fX_c[0];
	*y = fX_c[1];
	*z = fX_c[2];
}
//RollAngle横摇角,PitchAngle 纵摇角, YawAngle偏航角
/*! 从平台坐标转换为站心系RAE*/
void HJACUAERToENU(double range, double azi_rad,double ele_rad,
		double dRollAngle_rad,double dPitchAngle_rad,double dYawAngle_rad,
		double* e, double* n,double* u)
{
	double fMatrix[3][3];
	double fMatrix2[3][3];

	double fX[3];
	double fX_c[3];
	double fX_c2[3];
	int i;
	int j;

	memset(fX_c,0,3*sizeof(double));
	memset(fX_c2,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	// double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z
	Coordinate_PolarToRightAngle_HJ(range,azi_rad,ele_rad,&fX[1],&fX[0],&fX[2]);
	// RAE_radToXYZ(range,azi_rad,ele_rad,fX[1],fX[0],fX[2]);//range,azi_rad,ele_rad,fX[0],fX[1],fX[2]

	memset(fMatrix,0,9*sizeof(double));
	fMatrix[0][0] = cos(dYawAngle_rad)*cos(dPitchAngle_rad);
	fMatrix[0][1] = sin(dYawAngle_rad)*cos(dPitchAngle_rad);
	fMatrix[0][2] = -sin(dPitchAngle_rad);

	fMatrix[1][0] = cos(dYawAngle_rad)*sin(dPitchAngle_rad)*sin(dRollAngle_rad) - sin(dYawAngle_rad)*cos(dRollAngle_rad);
	fMatrix[1][1] = sin(dYawAngle_rad)*sin(dPitchAngle_rad)*sin(dRollAngle_rad) + cos(dYawAngle_rad)*cos(dRollAngle_rad);
	fMatrix[1][2] = cos(dPitchAngle_rad)*sin(dRollAngle_rad);

	fMatrix[2][0] = cos(dYawAngle_rad)*sin(dPitchAngle_rad)*cos(dRollAngle_rad) + sin(dYawAngle_rad)*sin(dRollAngle_rad);
	fMatrix[2][1] = sin(dYawAngle_rad)*sin(dPitchAngle_rad)*cos(dRollAngle_rad) - cos(dYawAngle_rad)*sin(dRollAngle_rad);
	fMatrix[2][2] = cos(dPitchAngle_rad)*cos(dRollAngle_rad);

	/*不考虑平台安装误差*/
#if 1
	//坐标变换
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			fX_c[i] += fMatrix[j][i]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}
#endif

	*e = fX_c[1];
	*n = fX_c[0];
	*u = fX_c[2];

	//方位仰角计算
	// XYZToRAE_rad(fX_c[1],fX_c[0],fX_c[2],rtemp,azitemp,elvtemp); //fX_c[0],fX_c[1],fX_c[2],range0,azi0_rad,ele0_rad 20190702

}

// hj  ACU to ePlane
void Coordinate_ACUxyzToePlanexyz_HJ(double x, double y, double z,  double Azimuth, double Elevation,double *ex, double *ey, double *ez)
{
	double RAzi = 0;
	double REle = 0;
	RAzi = (-1.0 * (180-Azimuth))/180.0*ONEPI;
	REle = (-1.0 * Elevation)/180.0*ONEPI;

	double fMatrix[3][3];

	double fX[3];
	double fX_c[3];

	int i;
	int j;

	memset(fX_c,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	fX[0] = x;
	fX[1] = y;
	fX[2] = z;

	memset(fMatrix,0,9*sizeof(double));
	fMatrix[0][0] = cos(REle)*cos(RAzi);
	fMatrix[0][1] = -sin(REle);
	fMatrix[0][2] = cos(REle) * sin(RAzi);

	fMatrix[1][0] = sin(REle)*cos(RAzi);
	fMatrix[1][1] = cos(REle);
	fMatrix[1][2] = sin(REle)*sin(RAzi);

	fMatrix[2][0] = -sin(RAzi);
	fMatrix[2][1] = 0;
	fMatrix[2][2] = cos(RAzi);

	/*不考虑平台安装误差*/

	//坐标变换
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			//printf("[ACU - eplant :]--i= %d,j= %d,ez = %f\n",i,j,fMatrix[i][j]);
			fX_c[i] += fMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}


	*ex = fX_c[0];
	*ey = fX_c[1];
	*ez = fX_c[2];
	//	printf("[ACU - eplant :]--ex= %f,ey= %f,ez = %f\n",fX_c[0],fX_c[1],fX_c[2]);

}


// hj ePlane to ACU
void Coordinate_ePlanexyzToACUxyz_HJ(double ex, double ey, double ez,  double Azimuth, double Elevation,double *x, double *y, double *z)
{
	double RAzi = 0;
	double REle = 0;
	RAzi = (-1.0 * (180-Azimuth))/180.0*ONEPI;
	REle = (-1.0 * Elevation)/180.0*ONEPI;

	double fMatrix[3][3];

	double fX[3];
	double fX_c[3];

	int i;
	int j;

	memset(fX_c,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	fX[0] = ex;
	fX[1] = ey;
	fX[2] = ez;

	memset(fMatrix,0,9*sizeof(double));

	fMatrix[0][0] = cos(REle)*cos(RAzi);
	fMatrix[0][1] = sin(REle)*cos(RAzi);
	fMatrix[0][2] = -sin(RAzi);

	fMatrix[1][0] = -sin(REle);
	fMatrix[1][1] = cos(REle);
	fMatrix[1][2] = 0;

	fMatrix[2][0] = cos(REle)*sin(RAzi);
	fMatrix[2][1] = sin(REle)*sin(RAzi);
	fMatrix[2][2] = cos(RAzi);


	//坐标变换
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			//printf("[ACU - eplant :]--i= %d,j= %d,ez = %f\n",i,j,fMatrix[i][j]);
			fX_c[i] += fMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}


	*x = fX_c[0];
	*y = fX_c[1];
	*z = fX_c[2];
	// printf("[eplant -  ACU:]--sx= %f,sy= %f,sz = %f\n",fX_c[0],fX_c[1],fX_c[2]);
}


// hj  ACU to ePlane
void Coordinate_ACUxyzToePlanexyz_HJPro(double x, double y, double z,  double Azimuth, double Elevation,double *ex, double *ey, double *ez)
{
	double RAzi = 0;
	double REle = 0;
	RMATRIX			TZ;
	RMATRIX			TY;
	RMATRIX			T1;
	RMATRIX			T2;
	RMATRIX			T3;

	RAzi =  -(180-Azimuth);
	REle =  -Elevation;
	double fMatrix[3][3];

	double fX[3];
	double fX_c[3];
	memset(fX_c,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	int i;
	int j;

	// rot RMATRIX  绕Z轴逆时针旋转的矩阵
	TZ =  rotat_z_axis_matrix(REle);

	// rot RMATRIX  绕Y轴逆时针旋转的矩阵
	TY =  rotat_y_axis_matrix(RAzi);

	T1 = real_matrix_multiper(TZ,TY);

	fX[0] = x;
	fX[1] = y;
	fX[2] = z;


	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			//printf("[ACU - eplant :]--i= %d,j= %d,ez = %f\n",i,j,fMatrix[i][j]);
			fX_c[i] += T1.ArrayMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}


	*ex = fX_c[0];
	*ey = fX_c[1];
	*ez = fX_c[2];

	// printf("[ACU -  eplant:]--ex= %f,ey= %f,ez = %f\n",fX_c[0],fX_c[1],fX_c[2]);
}

// hj ePlane to ACU
void Coordinate_ePlanexyzToACUxyz_HJPro(double ex, double ey, double ez,  double Azimuth, double Elevation,double *x, double *y, double *z)
{
	double RAzi = 0;
	double REle = 0;
	RMATRIX			TZ;
	RMATRIX			TY;
	RMATRIX			T1;
	RMATRIX			T2;
	RMATRIX			T3;

	RAzi =  180-Azimuth;
	REle =  Elevation;
	double fMatrix[3][3];

	double fX[3];
	double fX_c[3];
	memset(fX_c,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	int i;
	int j;

	// rot RMATRIX  绕Z轴逆时针旋转的矩阵
	TZ =  rotat_z_axis_matrix(REle);

	// rot RMATRIX  绕Y轴逆时针旋转的矩阵
	TY =  rotat_y_axis_matrix(RAzi);

	T1 = real_matrix_multiper(TY,TZ);

	fX[0] = ex;
	fX[1] = ey;
	fX[2] = ez;


	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			//printf("[ACU - eplant :]--i= %d,j= %d,ez = %f\n",i,j,fMatrix[i][j]);
			fX_c[i] += T1.ArrayMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}


	*x = fX_c[0];
	*y = fX_c[1];
	*z = fX_c[2];

	// printf("[eplant -  ACU:]--sx= %f,sy= %f,sz = %f\n",fX_c[0],fX_c[1],fX_c[2]);
}

// hj  ENU  to ACU
void Coordinate_ENUxyzToACUxyz_HJ(double x, double y, double z, double *ax, double *ay, double *az)
{

	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double fX[3];
	double fX_c[3];
	int i;
	int j;

	dRoll =  g_HJSysParm.roll;
	dPitch = g_HJSysParm.pitch;
	dYaw = g_HJSysParm.yaw;

	RMATRIX			TR;
	RMATRIX			TP;
	RMATRIX			TH;
	RMATRIX			TY;

	RMATRIX			T1;
	RMATRIX			T2;
	RMATRIX			T3;

	// rot RMATRIX  绕 横摇 旋转的矩阵
	TR =  rotat_R_axis_matrix(dRoll);

	// rot RMATRIX  绕 纵摇 旋转的矩阵
	TP = rotat_P_axis_matrix(dPitch);

	// rot RMATRIX  绕 航向 旋转的矩阵
	TH =  rotat_H_axis_matrix(dYaw);

	// rot RMATRIX  绕Y轴逆时针旋转的矩阵
	TY =  rotat_y_axis_matrix(90);

	T1 = real_matrix_multiper(TY,TR);
	T2 = real_matrix_multiper(T1,TP);
	T3 = real_matrix_multiper(T2,TH);

	memset(fX_c,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	fX[0] = x;
	fX[1] = y;
	fX[2] = z;


	//坐标变换
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			//printf("[ACU - eplant :]--i= %d,j= %d,ez = %f\n",i,j,fMatrix[i][j]);
			fX_c[i] += T3.ArrayMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}


	*ax = fX_c[0];
	*ay = fX_c[1];
	*az = fX_c[2];
	//printf("[ENU----ACU :]--ax= %f,ay= %f,az = %f\n",fX_c[0],fX_c[1],fX_c[2]);
}

// hj ACU to ENU
void Coordinate_ACUxyzToENUxyz_HJ(double ax, double ay, double az, double *x, double *y, double *z)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double fX[3];
	double fX_c[3];
	int i;
	int j;

	// dRoll =  g_HJSysParm.roll;
	// dPitch = g_HJSysParm.pitch;
	// dYaw = g_HJSysParm.yaw;

	dRoll =  g_ArrayAngleOut[0].roll;
	dPitch = g_ArrayAngleOut[0].pitch;
	dYaw = g_ArrayAngleOut[0].yaw;


	RMATRIX			TR;
	RMATRIX			TP;
	RMATRIX			TH;
	RMATRIX			TY;

	RMATRIX			T1;
	RMATRIX			T2;
	RMATRIX			T3;

	// rot RMATRIX  绕 横摇 旋转的矩阵
	TR =  rotat_R_axis_matrix(-dRoll);

	// rot RMATRIX  绕 纵摇 旋转的矩阵
	TP = rotat_P_axis_matrix(-dPitch);

	// rot RMATRIX  绕 航向 旋转的矩阵
	TH =  rotat_H_axis_matrix(-dYaw);

	// rot RMATRIX  绕Y轴逆时针旋转的矩阵
	TY =  rotat_y_axis_matrix(-90);

	T1 = real_matrix_multiper(TH,TP);
	T2 = real_matrix_multiper(T1,TR);
	T3 = real_matrix_multiper(T2,TY);

	memset(fX_c,0,3*sizeof(double));
	memset(fX,0,3*sizeof(double));

	fX[0] = ax;
	fX[1] = ay;
	fX[2] = az;


	//坐标变换
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			//printf("[ACU - eplant :]--i= %d,j= %d,ez = %f\n",i,j,fMatrix[i][j]);
			fX_c[i] += T3.ArrayMatrix[i][j]*fX[j];//乘矩阵的转置fMatrix[i][j]
		}
	}


	*x = fX_c[0];
	*y = fX_c[1];
	*z = fX_c[2];
	// printf("[ACU---- ENU:]--e= %f,n= %f,u = %f\n",fX_c[0],fX_c[1],fX_c[2]);
}

// hj ENU xyz ---AER
void Coordinate_ENUxyzToaer_HJ(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
	*Range = sqrt(X*X + Y*Y +Z*Z);
	*Azimuth = atan2XY(Z,X)*180.0/ONEPI;
	*Elevation = asin(Y/(*Range))*180.0/ONEPI;
#if 0
	double dRange = 0.0;
	double dAzimuth = 0.0;
	double dElevation = 0.0;
	dRange = sqrt(X*X + Y*Y +Z*Z);
	dAzimuth= atan2XY(Z,X)*180.0/ONEPI;
	dElevation = asin(Y/(dRange))*180.0/ONEPI;

	if(dAzimuth >= 359.999)
	{
		dAzimuth = 0;
	}
	// dAzimuth = dAzimuth - 90;
	if(dAzimuth >=360.0)
	{
		dAzimuth = dAzimuth - 360;
	}
	if(dAzimuth < 0.0)
	{
		dAzimuth = dAzimuth + 360;
	}
	dElevation = dElevation + 0.083; //修正
	if(dElevation > 270)
	{
		dElevation = dElevation - 90;
	}
	//printf("[ACU---- EAR:]--R= %f,A= %f,E = %f\n",dRange,dAzimuth,dElevation);
#endif
}

// hj ENU AER ---xyz
void Coordinate_ENUAerToXyz_HJ(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = (1.0 *Azimuth)/180.0*ONEPI;
	REle = (1.0 * Elevation)/180.0*ONEPI;

	*X = Range*cos(REle)*cos(RAzi);
	*Y = Range*sin(REle);
	*Z = Range*cos(REle)*sin(RAzi);
}

void testCoordinate_change()
{
	double ex = 0;
	double ey = 0;
	double ez = 0;
	double sx = 0;
	double sy = 0;
	double sz = 0;
	double x = 0;
	double y = 0;
	double z = 0;

	double Range = 0;
	double Azimuth = 0;
	double Elevation = 0;
	double ax = 0;
	double ay = 0;
	double az = 0;
	int j = 0;
	double eXp=0;
	double eYp=0;
	double eZp=0;
	double Xr=0;
	double Yr=0;
	double Zr=0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;
	double Xp = 7298653.338792;
	double Yp = 41474405.488343;
	double Zp = -2018484.959142;
	double e=0;
	double n=0;
	double u=0;
	// test
	// Xp = -1320854.043;
	// Yp = 4711684.322;
	// Zp = 4078819.724;

	// 天线转大地
	Coordinate_HJAnneToStation(1.933,17.0987, &Azimuth,&Elevation);
	// 大地转阵面
	HJ_ENUToACUGroundToMeasure(Azimuth,Elevation,&sAzimuth,&sElevation);
	printf("[ENU AE to eplant]Az= %f,ele = %f\n",sAzimuth,sElevation);

#if 0

	Xp = 7298653;
	Yp = 41474405;
	Zp = -2018484;

	Coordinate_WGS84ToECEF(121.266,38.803,17.28, &Xr, &Yr, &Zr);//pingtai Plon, Plat, Pht,
	Coordinate_ECEFToENU(Xr, Yr, Zr, Xp, Yp, Zp, 121.266,38.803, &e, &n, &u); // 平台,卫星,平台 ,enu  Plon, Plat,
	//Coordinate_ENUxyzToaer_HJ(e, n, u, &Range, &Azimuth,&Elevation);
	Coordinate_ENUxyzToaer_HJ(n, u, e, &Range, &Azimuth,&Elevation);
	printf("[enu - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);
	//Coordinate_RightAngleToPolar(e, n, u, &Range, &Azimuth,&Elevation);
	Coordinate_RightAngleToPolar(e, n, u,&Range, &Azimuth,&Elevation);
	printf("[enu - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);
	printf("[enu:]--e= %f,n= %f,u = %f\n",e,n,u);
	Coordinate_XYZToENUAER_ACU(Xr, Yr, Zr, Xp, Yp, Zp,121.266,38.803,17.28, &Range, &Azimuth,&Elevation);
	printf("[ACU----enu - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);

	x=-0.167313978626933;
	y=  0.041329838639424;
	z=-0.985036992703353;
	Azimuth= 278.999;
	Elevation = 90-2.3687;
	Coordinate_ACUxyzToePlanexyz_HJPro(x, y, z, Azimuth, Elevation,&ex, &ey, &ez);
	// hj ePlane to ACU
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez, Azimuth, Elevation,&x, &y, &z);



	Range = 1;
	Azimuth = 2.345;
	Elevation = 3.456;
	Coordinate_eplaneAerToXyz_HJ(Range, Azimuth,Elevation, &ex, &ey, &ez);
	//Coordinate_ePlanexyzToACUxyz_HJ(ex, ey,ez, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz);
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz);
	Coordinate_ACUxyzToENUxyz_HJ(sx, sy, sz, &e, &n, &u);
	Coordinate_ENUxyzToaer_HJ(e, n, u, &sRange, &sAzimuth,&sElevation);
	// Coordinate_ENUToECEF(Xr, Yr, Zr, e,  n,  u, pPlot->dplat, pPlot->dplon, &X, &Y, &Z); // lan lon
	// Coordinate_RightAngleToPolar(X,Y,Z, &Range, &Azimuth, &Elevation);

	printf("[move plat DXAER:]acuAz = %f,  acuEle = %f \n ",g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);
	printf("[move plat DXAER:]efRange = %f  eazi= %f  eele = %f\n",Range, Azimuth,Elevation);
	// printf("[move plat DXAER:]Xr = %f, Yr = %f ,Zr = %f\n ",Xr,Yr,Zr);
	// printf("[move plat DXAER:]X = %f,  Y = %f ,Z = %f \n ",X,Y,Z);
	printf("[move plat DXAER:]ex = %f,  ey = %f ,ez = %f \n ",ex,ey,ez);
	printf("[move plat DXAER:]sx = %f,  sy = %f ,sz = %f \n ",sx,sy,sz);
	printf("[move plat DXAER:]e = %f,  n = %f ,u = %f \n ",e,n,u);
	printf("[move plat DXAER]range = %f, azi= %f  ele = %f\n",sRange,sAzimuth,sElevation);


	Coordinate_ENUAerToXyz_HJ(sRange,sAzimuth,sElevation,&e, &n, &u);
	// add enu to aer
	// Coordinate_ENUxyzToaer_HJ(e, n, u, &Range, &Azimuth,&Elevation);
	Coordinate_ENUxyzToACUxyz_HJ(e, n, u, &ax, &ay, &az);
	//Coordinate_ACUxyzToePlanexyz_HJ(ax,ay,az, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&ex, &ey, &ez); // double Azimuth, double Elevation
	Coordinate_ACUxyzToePlanexyz_HJPro(ax,ay,az, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&ex, &ey, &ez);
	Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range0, &Azimuth0,&Elevation0);

	printf("[int mode of auto:]Range = %f,  Azi = %f ,Ele = %f \n ",sRange,sAzimuth,sElevation);
	//printf("[int mode of auto:]Xr = %f, Yr = %f ,Zr = %f\n ",Xr,Yr,Zr);
	//printf("[int mode of auto:]X = %f,  Y = %f ,Z = %f \n ",X,Y,Z);
	printf("[int mode of auto:]e = %f,  n = %f ,u = %f \n ",e,n,u);
	printf("[int mode of auto:]sx = %f, sy = %f ,sz = %f \n ",ax,ay,az);
	printf("[int mode of auto:]ex = %f, ey = %f ,ez = %f \n ",ex,ey,ez);
	printf("[int mode of auto:]efRange = %f,  eAzi = %f ,eEle = %f \n ",Range0,Azimuth0,Elevation0);
	printf("[int mode of auto:]acuaz = %f, acuele = %f\n ",g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);


	e = -8.381332990896729e+06;
	n = -2.186090308569187e+07;
	u = 2.870057897094902e+07;
	double yaw = 40;
	Coordinate_ENUToCarPosition(yaw, e,n, u, &x, &y, &z);
	Range = sqrt(x*x + y*y +z*z);
	Azimuth = atan2(y,x)*180.0/ONEPI;;
	Elevation = acos(z/(Range))*180.0/ONEPI;
	printf("[DY - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);

	double		bpAz[65] = {0};
	double		bpEle[65] = {0};
	//Coordinate_ACUxyzToePlanexyz_HJ(0.848048096156426,0,  0.529919264233205, 32,80,&ex, &ey, &ez);
	Coordinate_ACUxyzToePlanexyz_HJ(0.848048096156426,0,  0.529919264233205, 40,20,&ex, &ey, &ez);
	Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range, &Azimuth,&Elevation);
	//printf("[eplane - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);
	Coordinate_eplaneAerToXyz_HJ(Range, Azimuth,Elevation, &ex, &ey, &ez);
	//printf("[AER  - eplane:]--ex= %f,ey= %f,ez = %f\n",ex, ey,ez);
	Coordinate_ePlanexyzToACUxyz_HJ(ex, ey,ez, 40,20,&x, &y, &z);

	x = 0.747260947684137;
	y = 0.380748470258393;
	z = 0.544639035015027;
	Coordinate_ENUxyzToACUxyz_HJ(x, y, z, &ax, &ay, &az);
	Coordinate_ACUxyzToENUxyz_HJ(ax, ay, az, &x, &y, &z);

	// hj ENU xyz ---AER
	Coordinate_ENUxyzToaer_HJ(x, y, z, &Range, &Azimuth,&Elevation);
	//printf("[enu - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);
	// hj ENU AER ---xyz
	Coordinate_ENUAerToXyz_HJ(Range, Azimuth,Elevation, &x, &y, &z);
	//printf("[AER  - enu:]--e= %f,n= %f,u = %f\n",x, y,z);

	printf("cal scan mode pro [start]---------- time(ms) = %ld clock(us) = %ld\n",g_Time,m_BaseUTCClock_uSecond);
	// 东北天 ENU --AER send to ACU
	Xp = 7298653.338792;
	Yp = 41474405.488343;
	Zp = -2018484.959142;
	Coordinate_WGS84ToECEF(g_HJSysParm.longitude,g_HJSysParm.lat,g_HJSysParm.high, &Xr, &Yr, &Zr);//pingtai Plon, Plat, Pht,
	Coordinate_ECEFToENU(Xr, Yr, Zr, Xp, Yp, Zp, g_HJSysParm.longitude,g_HJSysParm.lat, &e, &n, &u); // 平台,卫星,平台 ,enu  Plon, Plat,
	Coordinate_ENUxyzToaer_HJ(e, n, u, &Range, &Azimuth,&Elevation);
	//printf("[enu - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);
	printf("[enu:]--e= %f,n= %f,u = %f\n",e,n,u);
	for(j = 0; j < 65; j++)
	{
		// 叠加 电波束的偏移角度
		Xp = Xp + eXp;
		Yp = Yp + eYp;
		Zp = Zp + eZp;
		Coordinate_ECEFToENU(Xr, Yr, Zr, Xp, Yp, Zp, g_HJSysParm.longitude,g_HJSysParm.lat, &e, &n, &u); // 平台,卫星,平台 ,enu  Plon, Plat,
		Coordinate_ENUxyzToACUxyz_HJ(e, n, u, &ax, &ay, &az);
		Coordinate_ACUxyzToePlanexyz_HJ(ax,ay,az, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&ex, &ey, &ez); // double Azimuth, double Elevation
		Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range, &Azimuth,&Elevation);

		bpAz[j] = Azimuth;
		bpEle[j] = Elevation;
	}

	printf("[MUI:]--roll= %f,pitch= %f,yaw = %f\n",g_HJSysParm.roll,g_HJSysParm.pitch,g_HJSysParm.yaw);
	printf("[ACU :]--ax= %f,ay= %f,az = %f\n",ax,ay,az);
	printf("[eplant :]--ex= %f,ey= %f,ez = %f\n",ex, ey, ez);
	printf("[eplant - AER :]--Range= %f,Az= %f,ele = %f,ACU_Azloc = %f, ACU_Eleloc = %f \n",Range, Azimuth,Elevation, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);
	printf("cal scan mode pro [end]---------- time(ms) = %ld clock(us) = %ld\n",g_Time,m_BaseUTCClock_uSecond);
	printf("\n");
#endif
}

//船站测量系－大地系转换（同样适用车载、机载）
//Head:航向角
//Roll：横摇角
//Pitch：纵摇角
//AZM,ELM:方位、俯仰角(函数调用时为测量系，同变量返回时为大地系转换结果)
//所有单位为度
void MeasureToGround(double AZM1,double ELM1,double Head,double Roll,double Pitch,double *AZM2,double *ELM2)
{
	double aSin, aCos;
	double AzTemp,ElTemp;
	double AZM;
	double ELM;

	AzTemp = AZM1*M_PI/180.0;
	ElTemp = ELM1*M_PI/180.0;

	if (ELM1 > 89.99999) //等于90度
	{
		ElTemp = 89.9999*M_PI/180.0; //89.9996*M_PI/180.0;
	}

	Head = Head*M_PI/180.0;
	Roll = Roll*M_PI/180.0;
	Pitch = Pitch*M_PI/180.0;

	aSin = sin(Head)*cos(Pitch)*cos(ElTemp)*cos(AzTemp) +
			(cos(Head)*sin(Roll) - sin(Head)*sin(Pitch)*cos(Roll))*sin(ElTemp) +
			(sin(Head)*sin(Pitch)*sin(Roll) + cos(Head)*cos(Roll))*cos(ElTemp)*sin(AzTemp);

	aCos = cos(Head)*cos(Pitch)*cos(ElTemp)*cos(AzTemp) -
			(cos(Head)*sin(Pitch)*cos(Roll) + sin(Head)*sin(Roll))*sin(ElTemp) +
			(cos(Head)*sin(Pitch)*sin(Roll) - sin(Head)*cos(Roll))*cos(ElTemp)*sin(AzTemp);

	if(fabs(aCos) < 0.0000001)    //如果分母近似为0 则方位结果为90或270度
	{
		if(aSin >= 0.0)
		{
			AZM = M_PI/2.0;
		}
		else
		{
			AZM = M_PI * 3.0/2.0;
		}
	}
	else
	{
		AZM = atan(fabs(aSin/aCos));

		if ((aSin >=0.0) && (aCos > 0.0))
		{
			AZM = AZM;
		}

		if ((aSin >=0.0) && (aCos < 0.0))
		{
			AZM = M_PI - AZM;
		}

		if ((aSin < 0.0) && (aCos < 0.0))
		{
			AZM= M_PI + AZM;
		}

		if ((aSin < 0.0) && (aCos > 0.0))
		{
			AZM= 2*M_PI - AZM;
		}
	}

	AZM = AZM*180.0/M_PI;

	if(AZM >= 359.999)
	{
		AZM = 0;
	}

	ELM = asin(sin(Pitch)*cos(ElTemp)*cos(AzTemp) +
			cos(Pitch)*cos(Roll)*sin(ElTemp)-
			cos(Pitch)*sin(Roll)*cos(ElTemp)*sin(AzTemp));

	ELM = ELM*180.0/M_PI;

	*AZM2 = AZM;
	*ELM2 = ELM;

}
// hj XYZ_ENUAER
void Coordinate_XYZToENUAER_ACU(double Xgp, double Ygp, double Zgp, double Xg, double Yg, double Zg, double Lon, double Lat, double Height, double *Range, double *Azimuth, double *Elevation)
{
	const double Re = 6378140.0;
	const double Eg2 = 0.006694385;

	double f0,A0;
	double Np;

	double SinLongitude;
	double SinLatitude;
	double CosLongitude;
	double CosLatitude;

	double Xgmp;
	double Ygmp;
	double Zgmp;

	double Xr;
	double Yr;
	double Zr;
	double R;

	double El = 0.0;
	double Az = 0.0;


	f0=0.0;
	A0=0.0;
	Np=0.0;

	SinLongitude=0.0;
	SinLatitude=0.0;
	CosLongitude=0.0;
	CosLatitude=0.0;

	Xgmp=0.0;
	Ygmp=0.0;
	Zgmp=0.0;

	SinLongitude = sin(Lon*PI/180.0);     //经度
	SinLatitude = sin(Lat*PI/180.0);       //纬度
	CosLongitude = cos(Lon*PI/180.0);     //经度
	CosLatitude = cos(Lat*PI/180.0);       //纬度

	f0=sqrt(1-Eg2*pow(SinLatitude,2.0));
	if(f0 < 0.000000000000001)       //防止除零错误
		f0=0.000000000000001;
	Np = Re/f0;

	Xgp = (Np + Height) * CosLatitude * CosLongitude;
	Ygp = (Np + Height) * CosLatitude * SinLongitude;
	Zgp = (Np * (1-Eg2) + Height) * SinLatitude;

	Xgmp = Xg-Xgp;
	Ygmp = Yg-Ygp;
	Zgmp = Zg-Zgp;

	Xr = -CosLongitude*SinLatitude*Xgmp - SinLongitude*SinLatitude*Ygmp + CosLatitude*Zgmp;
	Yr = CosLongitude*CosLatitude*Xgmp + SinLongitude*CosLatitude*Ygmp +SinLatitude*Zgmp;
	Zr = -SinLongitude*Xgmp + CosLongitude*Ygmp;

	R = sqrt( pow(Xr,2.0) + pow(Yr,2.0) + pow(Zr,2.0) );

	f0=sqrt( pow(Xr,2.0) + pow(Zr,2.0) );
	if(f0 < 0.000000000000001)       //防止除零错误
	{
		f0=0.000000000000001;
	}

	A0 = asin( Zr/f0 );

	if(R < 0.000000000000001)  //防止除零错误
	{
		R=0.000000000000001;
	}

	El = asin(Yr/R)*180.0/PI;

	if(El>=360.0)
	{
		El=El-360.0;
	}

	if(El<0.0)
	{
		//   El=El+360.0;
	}

	if ((Xr >=0) && (Zr>=0))
	{
		Az = A0;
	}

	if ((Xr >=0) && (Zr<0))
	{
		Az = A0 + 2*PI;
	}

	if (Xr<0)
	{
		Az = PI - A0;
	}

	Az=Az*180.0/PI;
	if(Az>=360.0)
	{
		Az=Az-360.0;
	}

	if(Az<0.0)
	{
		Az=Az+360.0;
	}

	*Range = R;
	*Azimuth = Az;
	*Elevation = El;
}

// hj 伺服当前角度信息
void Coordinate_ACUCURRENTToStation(double sAzimuth, double sElevation,  double *mAzimuth, double *mElevation)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;

	//dRoll = -1.0  * g_HJSysParm.roll;
	//dPitch =  -1.0  * g_HJSysParm.pitch;
	dRoll = 1.0  * g_HJSysParm.roll;
	dPitch =  1.0  * g_HJSysParm.pitch;
	dYaw = g_HJSysParm.yaw;

	double aAzimuth = 0;
	double aElevation = 0;

	sAzimuth = sAzimuth - 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	sElevation = sElevation + _ACU_ANGLE_ADD_ERROR; //0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&aAzimuth,&aElevation); // dadi
	*mAzimuth = aAzimuth;
	*mElevation = aElevation;

}


// hj 阵面转站心,也就是阵面转大地系，站心系=大地系
void Coordinate_HJAnneToStation(double Azimuth, double Elevation,  double *mAzimuth, double *mElevation)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;

	double dAzimuth = 0.0;
	double dElevation = 0.0;

	double ACU_Azloc = g_HJSysParm.ACU_Azloc;
	double ACU_Eleloc = 90-g_HJSysParm.ACU_Eleloc-0.083;

	dYaw = g_HJSysParm.yaw;
	//dRoll = -1.0  * g_HJSysParm.roll;
	//dPitch =  -1.0  * g_HJSysParm.pitch;

	dRoll = 1.0  * g_HJSysParm.roll;
	dPitch =  1.0  * g_HJSysParm.pitch;
	Coordinate_eplaneAerToXyz_HJ(1,Azimuth,Elevation, &ex, &ey, &ez); //zhenm
	// hj ePlane to ACU
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,ACU_Azloc,ACU_Eleloc,&sx, &sy, &sz); // 伺服角
	Coordinate_ACUxyzToaer_HJ_Pro(sx, sy, sz, &sRange, &sAzimuth,&sElevation);  // 20210415 修改

	sAzimuth = sAzimuth - 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// sElevation = sElevation + 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// hj ACU AE To MEA _AE  伺服转大地
	// 	HJ_ACUToMeasure_AE(sAzimuth,sElevation,&sAzimuth1,&sElevation1);

	// printf("[ACU AE ]Az= %f,ele = %f\n",sAzimuth,sElevation);
	MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
	*mAzimuth = dAzimuth;
	*mElevation = dElevation;
}


// hj 基带阵面转站心
void Coordinate_HJAnneToStation_band(double Azimuth, double Elevation, double dYaw,double dRoll,double dPitch ,double ACU_Eleloc,double ACU_Azloc,double *mAzimuth, double *mElevation)
{

	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;

	double dAzimuth = 0.0;
	double dElevation = 0.0;


	Coordinate_eplaneAerToXyz_HJ(1,Azimuth,Elevation, &ex, &ey, &ez); //zhenm
	// hj ePlane to ACU
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,ACU_Azloc,ACU_Eleloc,&sx, &sy, &sz); // 伺服角
	Coordinate_ACUxyzToaer_HJ_Pro(sx, sy, sz, &sRange, &sAzimuth,&sElevation);  // 20210415 修改

	sAzimuth = sAzimuth - 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// sElevation = sElevation + 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// hj ACU AE To MEA _AE  伺服转大地
	// 	HJ_ACUToMeasure_AE(sAzimuth,sElevation,&sAzimuth1,&sElevation1);

	// printf("[ACU AE ]Az= %f,ele = %f\n",sAzimuth,sElevation);
	MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
	*mAzimuth = dAzimuth;
	*mElevation = dElevation;
}

// hj 基带阵面转站心
void Coordinate_HJAnneToStation_band_1(double Azimuth, double Elevation,double *mAzimuth, double *mElevation)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;

	double dAzimuth = 0.0;
	double dElevation = 0.0;

	double ACU_Azloc = 0;
	double ACU_Eleloc = 0;

	// 滞后一级数据使用
	dYaw = g_ArrayAngleOut[0].yaw;
	dRoll = g_ArrayAngleOut[0].roll;
	dPitch =  g_ArrayAngleOut[0].pitch;
	ACU_Azloc = g_ArrayAngleOut[0].ACUaz;
	ACU_Eleloc = 90 - g_ArrayAngleOut[0].ACUele - 0.083;

	Coordinate_eplaneAerToXyz_HJ(1,Azimuth,Elevation, &ex, &ey, &ez); //zhenm
	// hj ePlane to ACU
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,ACU_Azloc,ACU_Eleloc,&sx, &sy, &sz); // 伺服角
	Coordinate_ACUxyzToaer_HJ_Pro(sx, sy, sz, &sRange, &sAzimuth,&sElevation);  // 20210415 修改

	sAzimuth = sAzimuth - 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// sElevation = sElevation + 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// hj ACU AE To MEA _AE  伺服转大地
	// 	HJ_ACUToMeasure_AE(sAzimuth,sElevation,&sAzimuth1,&sElevation1);

	// printf("[ACU AE ]Az= %f,ele = %f\n",sAzimuth,sElevation);
	MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
	*mAzimuth = dAzimuth;
	*mElevation = dElevation;

}

// hj 阵面转站心
void Coordinate_HJAnneToStation_IMU(IMU_MES imu_mes,double Azimuth, double Elevation,double *mAzimuth, double *mElevation)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;

	double dAzimuth = 0.0;
	double dElevation = 0.0;

	double ACU_Azloc = 0;
	double ACU_Eleloc = 0;

	// 滞后一级数据使用
	dYaw = imu_mes.yaw;
	dRoll = -1.0  * imu_mes.roll;
	dPitch =  -1.0  * imu_mes.pitch;
	ACU_Azloc = imu_mes.ACU_Azloc;
	ACU_Eleloc = 90 - imu_mes.ACU_Eleloc - 0.083;

	Coordinate_eplaneAerToXyz_HJ(1,Azimuth,Elevation, &ex, &ey, &ez); //zhenm
	// hj ePlane to ACU
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,ACU_Azloc,ACU_Eleloc,&sx, &sy, &sz); // 伺服角
	Coordinate_ACUxyzToaer_HJ_Pro(sx, sy, sz, &sRange, &sAzimuth,&sElevation);  // 20210415 修改

	sAzimuth = sAzimuth - 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// sElevation = sElevation + 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// hj ACU AE To MEA _AE  伺服转大地
	// 	HJ_ACUToMeasure_AE(sAzimuth,sElevation,&sAzimuth1,&sElevation1);

	// printf("[ACU AE ]Az= %f,ele = %f\n",sAzimuth,sElevation);
	MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
	*mAzimuth = dAzimuth;
	*mElevation = dElevation;

}

// hj 站心转阵面
void HJ_ENUToACUGroundToMeasure(double AZM1,double ELM1,double *AZM2,double *ELM2)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double ax = 0;
	double ay = 0;
	double az = 0;

	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;
	// dRoll =  g_HJSysParm.roll;
	// dPitch = g_HJSysParm.pitch;
	double ACU_Azloc = 0;
	double ACU_Eleloc = 0;

	dYaw = g_HJSysParm.yaw;
	//dRoll = -1.0  * g_HJSysParm.roll;
	//dPitch =  -1.0  * g_HJSysParm.pitch;
	dRoll = 1.0  * g_HJSysParm.roll;
	dPitch =  1.0  * g_HJSysParm.pitch;

	ACU_Azloc = g_HJSysParm.ACU_Azloc;
	ACU_Eleloc = 90 - g_HJSysParm.ACU_Eleloc - 0.083;

	// hj 站心转阵面
	GroundToMeasure(AZM1,ELM1,dYaw,dRoll,dPitch,&sAzimuth,&sElevation);

	// hj ACU AE To MEA _AE  伺服转大地
	sAzimuth = sAzimuth + 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// 	sElevation = sElevation - 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// printf("[re ENU AE]Az= %f,ele = %f\n",sAzimuth,sElevation);

	// 伺服角度
	Coordinate_ACUaerToxyz_HJ_Pro(1,sAzimuth,sElevation,&ax,&ay,&az);
	Coordinate_ACUxyzToePlanexyz_HJPro(ax,ay,az, ACU_Azloc,ACU_Eleloc,&ex, &ey, &ez);
	Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range0, &Azimuth0,&Elevation0);

	*AZM2 = Azimuth0;
	*ELM2 = Elevation0;
}

// hj 站心转阵面
void HJ_ENUToACUGroundToMeasure_IMU(IMU_MES imu_mes,double AZM1,double ELM1,double *AZM2,double *ELM2)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double ax = 0;
	double ay = 0;
	double az = 0;

	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;
	// dRoll =  g_HJSysParm.roll;
	// dPitch = g_HJSysParm.pitch;
	double ACU_Azloc = 0;
	double ACU_Eleloc = 0;



	dYaw = imu_mes.yaw;
	dRoll = -1.0  * imu_mes.roll;
	dPitch =  -1.0  * imu_mes.pitch;
	ACU_Azloc = imu_mes.ACU_Azloc;
	ACU_Eleloc = 90 - imu_mes.ACU_Eleloc - 0.083;

	// hj 站心转阵面
	GroundToMeasure(AZM1,ELM1,dYaw,dRoll,dPitch,&sAzimuth,&sElevation);

	// hj ACU AE To MEA _AE  伺服转大地
	sAzimuth = sAzimuth + 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// 	sElevation = sElevation - 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// printf("[re ENU AE]Az= %f,ele = %f\n",sAzimuth,sElevation);

	// 伺服角度
	Coordinate_ACUaerToxyz_HJ_Pro(1,sAzimuth,sElevation,&ax,&ay,&az);
	Coordinate_ACUxyzToePlanexyz_HJPro(ax,ay,az, ACU_Azloc,ACU_Eleloc,&ex, &ey, &ez);
	Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range0, &Azimuth0,&Elevation0);

	*AZM2 = Azimuth0;
	*ELM2 = Elevation0;
}

// hj 基带站心转阵面
void HJ_ENUToACUGroundToMeasure_band(double AZM1,double ELM1,double *AZM2,double *ELM2)
{
	double dRoll = 0;
	double dPitch = 0;
	double dYaw = 0;
	double ax = 0;
	double ay = 0;
	double az = 0;

	double ex = 0;
	double ey = 0;
	double ez = 0;

	double sx = 0;
	double sy = 0;
	double sz = 0;

	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double sRange = 0;
	double sAzimuth = 0;
	double sElevation = 0;

	double sAzimuth1 = 0;
	double sElevation1 = 0;
	// dRoll =  g_HJSysParm.roll;
	// dPitch = g_HJSysParm.pitch;
	double ACU_Azloc = 0;
	double ACU_Eleloc = 0;


	dYaw = g_ArrayAngleOut[0].yaw;
	dRoll = -1.0  * g_ArrayAngleOut[0].roll;
	dPitch =  -1.0  * g_ArrayAngleOut[0].pitch;
	ACU_Azloc = g_ArrayAngleOut[0].ACUaz;
	ACU_Eleloc = 90 - g_ArrayAngleOut[0].ACUele - 0.083;

	// hj 站心转阵面
	GroundToMeasure(AZM1,ELM1,dYaw,dRoll,dPitch,&sAzimuth,&sElevation);

	// hj ACU AE To MEA _AE  伺服转大地
	sAzimuth = sAzimuth + 90;
	if(sAzimuth >=360.0)
	{
		sAzimuth = sAzimuth - 360;
	}
	if(sAzimuth < 0.0)
	{
		sAzimuth = sAzimuth + 360;
	}
	// 	sElevation = sElevation - 0.083; //修正
	if(sElevation >= 360)
	{
		sElevation = sElevation -360;
	}
	if(sElevation < 0)
	{
		sElevation = sElevation + 360;
	}
	if(sElevation > 270)
	{
		sElevation = sElevation - 360;
	}

	// printf("[re ENU AE]Az= %f,ele = %f\n",sAzimuth,sElevation);

	// 伺服角度
	Coordinate_ACUaerToxyz_HJ_Pro(1,sAzimuth,sElevation,&ax,&ay,&az);
	Coordinate_ACUxyzToePlanexyz_HJPro(ax,ay,az, ACU_Azloc,ACU_Eleloc,&ex, &ey, &ez);
	Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range0, &Azimuth0,&Elevation0);

	*AZM2 = Azimuth0;
	*ELM2 = Elevation0;
}
// hj ACU AE To MEA _AE  伺服转大地
void HJ_ACUToMeasure_AE(double AZM1,double ELM1,double *AZM2,double *ELM2)
{
	double  AzTemp = AZM1*M_PI/180.0;
	double  ElTemp = ELM1*M_PI/180.0;
	double X = 0;
	double Y = 0;
	double Z = 0;

	double R = 0;
	double Range = 0;

	X = cos(ELM1) * cos(AZM1);
	Y = sin(ELM1);
	Z = cos(ELM1) * sin(AZM1);

	Range = sqrt(X*X + Y*Y +Z*Z);
	*AZM2 = atan2XY(X,Y)*180.0/ONEPI;
	*ELM2 = asin(Z/(Range))*180.0/ONEPI;
}



// hj ACU AE To MEA _AE 大地转伺服
void HJ_ACU_Measure_RETURE_AE(double AZM1,double ELM1,double *AZM2,double *ELM2)
{
	double  AzTemp = AZM1*M_PI/180.0;
	double  ElTemp = ELM1*M_PI/180.0;
	double X = 0;
	double Y = 0;
	double Z = 0;

	double R = 0;
	double Range = 0;

	X = cos(ELM1) * sin(AZM1);
	Y = cos(ELM1) * cos(AZM1);
	Z = sin(ELM1);

	Range = sqrt(X*X + Y*Y +Z*Z);
	*AZM2 = atan2XY(Z,X)*180.0/ONEPI;
	*ELM2 = asin(Y/(Range))*180.0/ONEPI;
}


// void GroundToMeasure(double &AZ,double &EL,double Head,double Roll,double Pitch)
void GroundToMeasure(double AZ,double EL,double Head,double Roll,double Pitch,double *AZM2,double *ELM2)
{
	double aSin, aCos;
	double AzTemp,ElTemp;

	AzTemp = AZ*M_PI/180.0;
	ElTemp = EL*M_PI/180.0;

	if (EL > 89.99999) //大于90度
		ElTemp = 89.9996*M_PI/180.0;

	Head = Head*M_PI/180.0;
	Roll = Roll*M_PI/180.0;
	Pitch = Pitch*M_PI/180.0;

	aSin = sin(Roll)*sin(Pitch)*cos(ElTemp)*cos(AzTemp-Head) +
			cos(Roll)*cos(ElTemp)*sin(AzTemp-Head) -
			sin(Roll)*cos(Pitch)*sin(ElTemp);


	aCos = cos(Pitch)*cos(ElTemp)*cos(AzTemp-Head) + sin(Pitch)*sin(ElTemp);

	if(fabs(aCos) < 0.0000001)    //如果分母近似为0 则方位结果为90或270度
	{
		if(aSin >= 0.0)
		{
			AZ = M_PI/2.0;
		}
		else
		{
			AZ = M_PI * 3.0/2.0;
		}
	}
	else
	{
		AZ = atan(fabs(aSin/aCos));

		if ((aSin >=0.0) && (aCos > 0.0))
		{
			AZ = AZ;
		}

		if ((aSin >=0.0) && (aCos < 0.0))
		{
			AZ = M_PI - AZ;
		}

		if ((aSin < 0.0) && (aCos < 0.0))
		{
			AZ= M_PI + AZ;
		}

		if ((aSin < 0.0) && (aCos > 0.0))
		{
			AZ= 2*M_PI - AZ;
		}
	}

	AZ = AZ*180.0/M_PI;

	if(AZ >= 359.999)
	{
		AZ = 0;
	}

	*AZM2 = AZ;
	EL = -1.0*cos(Roll)*sin(Pitch)*cos(ElTemp)*cos(AzTemp-Head) +
			sin(Roll)*cos(ElTemp)*sin(AzTemp-Head)+
			cos(Roll)*cos(Pitch)*sin(ElTemp);

	EL = asin(EL);

	*ELM2 = EL*180.0/M_PI;

}


#endif // _COORDINATE_CJJ

