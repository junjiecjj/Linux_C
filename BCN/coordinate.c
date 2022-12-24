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


/*Lon,Lat:(deg), Height:(m)*/
//惯导经纬高----> 船的地心系xyz
void Coordinate_WGS84ToECEF(double Lon, double Lat, double Height, double *X, double *Y, double *Z)
{
	double a = 0;
	double b = 0;
	double f = 0;
	double e2 = 0;
	double ep2 = 0;
	double r0 = 0;

	double Rlat = 0;
	double Rlon = 0;
	double chi = 0;

	Coordinate_GetInitationParas(&a, &b, &f, &e2, &ep2, &r0);

	Rlat = Lat/180.0*ONEPI;
	Rlon = Lon/180.0*ONEPI;
	chi = sqrt(1-e2*sin(Rlat)*sin(Rlat));

	*X = (a/chi+Height)*cos(Rlat)*cos(Rlon);
	*Y = (a/chi+Height)*cos(Rlat)*sin(Rlon);
	*Z = (a/chi*(1-e2)+Height)*sin(Rlat);

}


/*Range:(m),Azimuth:(deg), Elevation:(deg)*/
void Coordinate_PolarToRightAngle(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = Azimuth/180.0*ONEPI;
	REle = Elevation/180.0*ONEPI;

	*X = Range*cos(REle)*sin(RAzi);
	*Y = Range*cos(REle)*cos(RAzi);
	*Z = Range*sin(REle);

}


/*Xr, Yr, Zr, e, n, u:(m), refLat,refLon:(deg)*/
void Coordinate_ENUToECEF(double Xr, double Yr, double Zr, double e, double n, double u, double refLat, double refLon, double *x, double *y, double *z)
{
	double phiP=0;
	//	double rLat=0;
	double rLon=0;

	phiP = refLat/180.0*ONEPI;
	rLon = refLon/180*ONEPI;
	*x = -sin(rLon)*e-cos(rLon)*sin(phiP)*n+cos(rLon)*cos(phiP)*u+Xr;
	*y = cos(rLon)*e-sin(rLon)*sin(phiP)*n+cos(phiP)*sin(rLon)*u+Yr;
	*z = cos(phiP)*n+sin(phiP)*u+Zr;

}

void Coordinate_ECEFToWGS84(double X, double Y, double Z, double *lamda, double *phi, double *h)
{
	double a = 0;
	double b = 0;
	double f = 0;
	double e2 = 0;
	double ep2 = 0;
	double r0 = 0;

	double r2 = 0;
	double r = 0;
	double E2 = 0;
	double F = 0;
	double G = 0;
	double c = 0;
	double s = 0;
	double P = 0;
	double Q = 0;
	double ro = 0;
	double tmp = 0;
	double U = 0;
	double V = 0;
	double zo = 0;


	Coordinate_GetInitationParas(&a, &b, &f, &e2, &ep2, &r0);

	r2 = X*X+Y*Y;
	r = sqrt(r2);
	E2 = a*a - b*b;
	F = 54*b*b*Z*Z;
	G = r2 + (1-e2)*Z*Z - e2*E2;
	c = (e2*e2*F*r2)/(G*G*G);
	s = pow((1 + c + sqrt(c*c+2*c)),1/3);
	P = F/(3*(s+1/s+1)*(s+1/s+1)*G*G);
	Q = sqrt(1+2*e2*e2*P);
	ro = -(e2*P*r)/(1+Q)+sqrt((a*a/2)*(1+1/Q)-((1-e2)*P*Z*Z)/(Q*(1+Q))-P*r2/2);
	tmp = (r-e2*ro)*(r-e2*ro);
	U = sqrt(tmp+Z*Z);
	V = sqrt(tmp+(1-e2)*Z*Z);
	zo = (b*b*Z)/(a*V);

	*h = U*(1-b*b/(a*V));
	*phi = atan((Z+ep2*zo)/r)*180/ONEPI;
	*lamda = atan2(Y,X)*180/ONEPI;

}


void Coordinate_PolarHToPolar(double Range, double Azimuth, double Height, double L, double B, double H, double *Range0, double *Azimuth0, double *Elevation0)
{
	double a = 0;
	double b = 0;
	double f = 0;
	double e2 = 0;
	double ep2 = 0;
	double r0 = 0;

	double latRad = 0;
	double N = 0;
	double R0 = 0;
	double Ap = 0;
	double Bp = 0;
	double Cp = 0;

	Coordinate_GetInitationParas(&a, &b, &f, &e2, &ep2, &r0);

	*Range0 = Range;
	*Azimuth0 = Azimuth;
	latRad = B*ONEPI/180;

	N = a/sqrt(1-e2*sin(latRad)*sin(latRad));
	R0 = N*sqrt(cos(latRad)*cos(latRad) + (1-e2)*(1-e2)*sin(latRad)*sin(latRad));

	Ap = R0 + H;
	Bp = Range;
	Cp = R0 + Height;

	if(Bp<0 || Ap<0)
	{
		*Elevation0 = 0;
	}
	else
	{
		*Elevation0 = -asin((Ap*Ap+Bp*Bp-Cp*Cp)/(2*Ap*Bp))/ONEPI*180;
	}

}


void Coordinate_PolarToWGS84(double Range, double Azimuth, double Height, double Plat, double Plon, double Pht, double *Tlat, double *Tlon, double *Th)
{
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;
	double e=0;
	double n=0;
	double u=0;
	double Xr=0;
	double Yr=0;
	double Zr=0;
	double X=0;
	double Y=0;
	double Z=0;
	double lamda=0;
	double phi=0;
	double h=0;

	Coordinate_PolarHToPolar(Range, Azimuth, Height, Plon, Plat, Pht, &Range0, &Azimuth0, &Elevation0);

	Coordinate_PolarToRightAngle(Range0, Azimuth0, Elevation0, &e, &n, &u);

	Coordinate_WGS84ToECEF(Plon, Plat, Pht, &Xr, &Yr, &Zr);

	Coordinate_ENUToECEF(Xr, Yr, Zr, e, n, u, Plat, Plon, &X, &Y, &Z);

	Coordinate_ECEFToWGS84(X, Y, Z, &lamda, &phi, &h);

	*Tlon = lamda;
	*Tlat = phi;
	*Th = h;

}

// 平台,dan,平台 ,enu  Plon, Plat,
//地心系船的xyz+目标地心系xyz+船的经纬高 --->  目标大地系的xyz
void Coordinate_ECEFToENU(double Xr, double Yr, double Zr, double X, double Y, double Z, double refLon, double refLat, double *e, double *n, double *u)
{
	double phiP=0;
	double lambda=0;

	phiP = refLat*ONEPI/180.0;
	lambda = refLon*ONEPI/180.0;

	*e = -sin(lambda)*(X-Xr) + cos(lambda)*(Y-Yr);
	*n = -sin(phiP)*cos(lambda)*(X-Xr) - sin(phiP)*sin(lambda)*(Y-Yr) + cos(phiP)*(Z-Zr);
	*u = cos(phiP)*cos(lambda)*(X-Xr) + cos(phiP)*sin(lambda)*(Y-Yr) + sin(phiP)*(Z-Zr);
}

// 目标大地系的xyz- ---> 目标大地系的方位俯仰
void Coordinate_RightAngleToPolar(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
	*Range = sqrt(X*X + Y*Y +Z*Z);
	*Azimuth = atan2XY(X,Y)*180.0/ONEPI;
	*Elevation = asin(Z/(*Range))*180.0/ONEPI;
}

void Coordinate_RightAngleToPolar_XX(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
	double azi = 0;
	*Range = sqrt(X*X + Y*Y +Z*Z);
	azi = atan2(X,Z)*180.0/ONEPI; // 
	*Elevation = asin(Y/(*Range))*180.0/ONEPI;
	if(azi < -90)
	{
		*Azimuth  = azi + 180;
	}
	else if(azi > 90)
	{
		*Azimuth  = azi - 180;
	}
	else
	{
		*Azimuth  = azi;
	}
	// printf("----azi = %f  ele = %f\n",azi,asin(Y/(*Range))*180.0/ONEPI);
}


void Coordinate_eplanexyzToaer_HJ(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
	double azi = 0;
	*Range = sqrt(X*X + Y*Y +Z*Z);
	azi = atan2(X,Y)*180.0/ONEPI; // 
	*Elevation = asin(Z/(*Range))*180.0/ONEPI;
	if(azi < -90)
	{
		*Azimuth  = azi + 180;
	}
	else if(azi > 90)
	{
		*Azimuth  = azi - 180;
	}
	else
	{
		*Azimuth  = azi;
	}
}


void Coordinate_ACUxyzToaer_HJ(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
	double azi = 0;
	double ele = 0;
	*Range = sqrt(X*X + Y*Y +Z*Z);
	azi = atan2(Z,X)*180.0/ONEPI; // 
	ele = acos(Y/(*Range))*180.0/ONEPI;
	if(azi < 0)
	{
		*Azimuth  = azi + 360;
	}
	else
	{
		*Azimuth  = azi;
	}
	if(ele > 90)
	{
		*Elevation  = 90 - ele ;
	}
	else
	{
		*Elevation  = ele;
	}
}

// 目标在伺服系xyz ---->  目标在伺服系方位、俯仰
void Coordinate_ACUxyzToaer_HJ_Pro(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
	double azi = 0;
	double ele = 0;
	*Range = sqrt(X*X + Y*Y +Z*Z);
	azi = atan2(Z,X)*180.0/ONEPI; // 
	ele = asin(Y/(*Range))*180.0/ONEPI;
	if(azi < 0)
	{
		*Azimuth  = azi + 360;
	}
	else
	{
		*Azimuth  = azi;
	}

	*Elevation  = ele;  
}

// hj ACU AER to xyz
void Coordinate_ACUaerToxyz_HJ_Pro(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = (1.0 *Azimuth)/180.0*ONEPI;
	REle = (1.0 * Elevation)/180.0*ONEPI;

	*X = Range*cos(REle)*cos(RAzi);
	*Y = Range*sin(REle);
	*Z = Range*cos(REle)*sin(RAzi);
}

// hj eplane xyz to aer
void Coordinate_eplaneaerToxyz_HJ_Pro(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = (1.0 *Azimuth)/180.0*ONEPI;
	REle = (1.0 * Elevation)/180.0*ONEPI;

	*X = Range*cos(REle)*cos(RAzi);
	*Y = Range*sin(REle);
	*Z = Range*cos(REle)*sin(RAzi);
}

// 目标在阵面系 方位俯仰--> 目标在阵面系 x,y,z
void Coordinate_eplaneAerToXyz_HJ(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = Azimuth/180.0*ONEPI;
	REle = Elevation/180.0*ONEPI;

	*X = Range*cos(REle)*sin(RAzi);
	*Y = Range*cos(REle)*cos(RAzi);
	*Z = Range*sin(REle);
}


void Coordinate_WGS84ToPolarE(double Lon, double Lat, double Height, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation)
{
	double Xr=0;
	double Yr=0;
	double Zr=0;
	double X=0;
	double Y=0;
	double Z=0;
	double e=0;
	double n=0;
	double u=0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	Coordinate_WGS84ToECEF(Plon, Plat, Pht, &Xr, &Yr, &Zr);

	Coordinate_WGS84ToECEF(Lon, Lat, Height, &X, &Y, &Z);

	Coordinate_ECEFToENU(Xr, Yr, Zr, X, Y, Z, Plon, Plat, &e, &n, &u);

	Coordinate_RightAngleToPolar(e, n, u, &Range0, &Azimuth0, &Elevation0);

	*Range = Range0;
	*Azimuth = Azimuth0;
	*Elevation = Elevation0;

}


void Coordinate_WGS84ToPolarPro(int mode,int i,double yaw,double X, double Y, double Z, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation)
{
	double Xr=0;
	double Yr=0;
	double Zr=0;

	double e=0;
	double n=0;
	double u=0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double Range1 = 0;
	double Azimuth1 = 0;
	double Elevation1 = 0;

	double x=0;
	double y=0;
	double z=0;

	Coordinate_WGS84ToECEF(Plon, Plat, Pht, &Xr, &Yr, &Zr);//pingtai
	Coordinate_ECEFToENU(Xr, Yr, Zr, X, Y, Z, Plon, Plat, &e, &n, &u); // 平台,卫星,平台 ,enu
	Coordinate_ENUToCarPosition(yaw, e, n,u, &x, &y,&z);
	Coordinate_RightAngleToPolar(x, y, z, &Range1, &Azimuth1, &Elevation1);
	Coordinate_RightAngleToPolar(e, n, u, &Range0, &Azimuth0, &Elevation0);
	//Coordinate_RightAngleToPolar(X, Y, Z, &Range0, &Azimuth0, &Elevation0);
	if(mode == ENUM_DIGIT_MODE)
	{
		if(g_SysParm[i].AngleCheck == 1 || g_SysParm[i].AngleCheck == 3 )
		{
			g_HJSysParm.DigleadAziM = (int)((Azimuth1 + g_HJSysParm.ferrAzi) *1000.0);
			g_HJSysParm.DigleadElevM = (int)((Elevation1 + g_HJSysParm.ferrEle) *1000.0);
			printf("[DIGIT check:]--Azi = %d,Elev = %d,Azimuth1 = %f ,Elevation1= %f\n",g_HJSysParm.DigleadAziM,g_HJSysParm.DigleadElevM,Azimuth1,Elevation1);
		}
		else
		{
			//g_SysParm[i].DigleadAzi = (int)(Azimuth1 *1000.0);
			//g_SysParm[i].DigleadElev = (int)(Elevation1 *1000.0);
			g_HJSysParm.DigleadAzi = (int)(Azimuth0 *1000.0);
			g_HJSysParm.DigleadElev = (int)(Elevation0 *1000.0);
			g_HJSysParm.DigleadAziM = (int)(Azimuth1 *1000.0);
			g_HJSysParm.DigleadElevM = (int)(Elevation1 *1000.0);
		}

		if(g_HJSysParm.CurWorkType == ENUM_DIGIT_MODE)
		{
			//g_HJSysParm.RealTGroundAzi = (int)(Azimuth0 *1000.0);
			//g_HJSysParm.RealTGroundElev = (int)(Elevation0 *1000.0);
			//g_HJSysParm.RealTMeasureAzi = (int)(Azimuth1 *1000.0);
			//g_HJSysParm.RealTMeasureElev = (int)(Elevation1 *1000.0);
		}
	}

	if(mode == ENUM_PROGR_MODE)
	{
		if(g_SysParm[i].AngleCheck == 1 || g_SysParm[i].AngleCheck == 3 )
		{
			g_HJSysParm.ProgramAziM = (int)((Azimuth1 + g_HJSysParm.ferrAzi) *1000.0);
			g_HJSysParm.ProgramElevM = (int)((Elevation1 + g_HJSysParm.ferrEle) *1000.0);
			printf("[PROGR check:]--Azi = %d,Elev = %d,Azimuth1 = %f ,Elevation1= %f\n",g_HJSysParm.ProgramAziM,g_HJSysParm.ProgramElevM,Azimuth1,Elevation1);
		}
		else
		{
			g_HJSysParm.ProgramAzi = (int)(Azimuth0 *1000.0);
			g_HJSysParm.ProgramElev = (int)(Elevation0 *1000.0);
			g_HJSysParm.ProgramAziM = (int)(Azimuth1 *1000.0);
			g_HJSysParm.ProgramElevM = (int)(Elevation1 *1000.0);
		}

		if(g_HJSysParm.CurWorkType == ENUM_PROGR_MODE)
		{
			//g_HJSysParm.RealTGroundAzi = (int)(Azimuth0 *1000.0);
			//g_HJSysParm.RealTGroundElev = (int)(Elevation0 *1000.0);
			//g_HJSysParm.RealTMeasureAzi = (int)(Azimuth1 *1000.0);
			//g_HJSysParm.RealTMeasureElev = (int)(Elevation1 *1000.0);
		}
	}



	//printf("[report :]--X= %f,Y = %f,Z = %f ,lan= %f,lon = %f,high = %f ,azi= %f  ele = %f \n",x,y,z,Plat, Plon, Pht,Azimuth1,Elevation1);
	Coordinate_RightAngleToPolar_XX(x, y, z, &Range0, &Azimuth0, &Elevation0);
	*Range = Range0;
	*Azimuth = Azimuth0;
	*Elevation = Elevation0;

	// printf("[report :]--X= %f,Y = %f,Z = %f ,lan= %f,lon = %f,high = %f ,azi= %f  ele = %f \n",x,y,z,Plat, Plon, Pht,Azimuth0,Elevation0);
}

// 数引，程引、同站数据处理
void Coordinate_HJWGS84ToPolarPro(int mode,int i,double yaw,double X, double Y, double Z, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation)
{
	double Xr=0;
	double Yr=0;
	double Zr=0;

	double e=0;
	double n=0;
	double u=0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double Range1 = 0;
	double Azimuth1 = 0;
	double Elevation1 = 0;

	double x=0;
	double y=0;
	double z=0;
	double ax=0;
	double ay=0;
	double az=0;
	double ex=0;
	double ey=0;
	double ez=0;

	double sx = 0;
	double sy = 0;
	double sz = 0;
	double sRange = 0;
	double sAzimuth= 0;
	double sElevation = 0;

	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,g_HJSysParm.ACU_Azloc,90-g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz); // 伺服角


	Coordinate_WGS84ToECEF(Plon, Plat, Pht, &Xr, &Yr, &Zr);//pingtai
	Coordinate_ECEFToENU(Xr, Yr, Zr, X, Y, Z, Plon, Plat, &e, &n, &u); // 平台,卫星,平台 ,enu
	Coordinate_ENUxyzToaer_HJ(e, n, u, &Range0, &Azimuth0,&Elevation0);

	//printf("[enu - AER :]--Range= %f,Az= %f,ele = %f\n",Range, Azimuth,Elevation);
	Coordinate_ENUxyzToACUxyz_HJ(e, n, u, &ax, &ay, &az);
	Coordinate_ACUxyzToePlanexyz_HJPro(ax,ay,az, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&ex, &ey, &ez); // double Azimuth, double Elevation
	Coordinate_eplanexyzToaer_HJ(ex, ey, ez,&Range1, &Azimuth1,&Elevation1);  // zhenmian

	if(mode == ENUM_DIGIT_MODE)
	{
		if(g_SysParm[i].AngleCheck == 1 || g_SysParm[i].AngleCheck == 3 )
		{
			g_HJSysParm.DigleadAziM = (int)((Azimuth1 + g_HJSysParm.ferrAzi) *1000.0);
			g_HJSysParm.DigleadElevM = (int)((Elevation1 + g_HJSysParm.ferrEle) *1000.0);
			printf("[DIGIT check:]--Azi = %d,Elev = %d,Azimuth1 = %f ,Elevation1= %f\n",g_HJSysParm.DigleadAziM,g_HJSysParm.DigleadElevM,Azimuth1,Elevation1);
		}
		else
		{
			//g_SysParm[i].DigleadAzi = (int)(Azimuth1 *1000.0);
			//g_SysParm[i].DigleadElev = (int)(Elevation1 *1000.0);
			g_HJSysParm.DigleadAzi = (int)(Azimuth1 *1000.0);
			g_HJSysParm.DigleadElev = (int)(Elevation1 *1000.0);
			g_HJSysParm.DigleadAziM = (int)(Azimuth0 *1000.0);
			g_HJSysParm.DigleadElevM = (int)(Elevation0 *1000.0);
		}

		if(g_HJSysParm.CurWorkType == ENUM_DIGIT_MODE)
		{
			g_HJSysParm.RealTGroundAzi = (int)(Azimuth0 *1000.0);
			g_HJSysParm.RealTGroundElev = (int)(Elevation0 *1000.0);
			g_HJSysParm.RealTMeasureAzi = (int)(Azimuth1 *1000.0);
			g_HJSysParm.RealTMeasureElev = (int)(Elevation1 *1000.0);

			//	g_HJSysParm.ACU_Azloc = Azimuth0;
			//	g_HJSysParm.ACU_Eleloc = Elevation0;

			double dRoll = 0;
			double dPitch = 0;
			double dYaw = 0;
			double dAzimuth = 0.0;
			double dElevation = 0.0;
			dRoll =  g_HJSysParm.roll;
			dPitch = g_HJSysParm.pitch;
			dYaw = g_HJSysParm.yaw;

			Coordinate_eplaneAerToXyz_HJ(1,Azimuth1,Elevation1, &ex, &ey, &ez); //zhenm 
			//Coordinate_ePlanexyzToACUxyz_HJ(ex, ey,ez, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz);
			// hj ePlane to ACU
			Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,g_HJSysParm.ACU_Azloc,90-g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz); // 伺服角
			Coordinate_ACUxyzToaer_HJ_Pro(sx, sy, sz, &sRange, &sAzimuth,&sElevation);  // ACU 

#if 0 
			MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
			dAzimuth = dAzimuth - 90;
			if(dAzimuth >=360.0)
			{
				dAzimuth = dAzimuth - 360;
			}
			if(dAzimuth < 0.0)
			{
				dAzimuth = dAzimuth + 360;
			}
			// dElevation = dElevation + g_HJParmContrl.ACUModifyParm; //修正
			if(dElevation > 270)
			{
				dElevation = dElevation - 90;
			}
			//Coordinate_ACUxyzToENUxyz_HJ(sx, sy, sz, &e, &n, &u);
			//Coordinate_ENUxyzToaer_HJ(e, n, u, &Range, &Azimuth,&Elevation);  //
#endif
			sAzimuth = sAzimuth - 90;
			if(sAzimuth >=360.0)
			{
				sAzimuth = sAzimuth - 360;
			}
			if(sAzimuth < 0.0)
			{
				sAzimuth = sAzimuth + 360;
			}
			sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //修正
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

			MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi

			g_HJSysParm.ACU_AzEcef = dAzimuth;
			g_HJSysParm.ACU_EleEcef = dElevation;

			// printf("[end to ACU---filter after:]Azimuth0= %f,Elevation0 = %f,ACU_Azloc = %f,  ACU_Eleloc = %f  ",Azimuth0,Elevation0,g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);
			printf("[%s]Sazi = %f,Sele = %f,Maz = %f,Mele = %f\n",__func__,sAzimuth,sElevation,dAzimuth,dElevation);

		}
	}

	if(mode == ENUM_PROGR_MODE)
	{
		if(g_SysParm[i].AngleCheck == 1 || g_SysParm[i].AngleCheck == 3 )
		{
			g_HJSysParm.ProgramAziM = (int)((Azimuth1 + g_HJSysParm.ferrAzi) *1000.0);
			g_HJSysParm.ProgramElevM = (int)((Elevation1 + g_HJSysParm.ferrEle) *1000.0);
			printf("[PROGR check:]--Azi = %d,Elev = %d,Azimuth1 = %f ,Elevation1= %f\n",g_HJSysParm.ProgramAziM,g_HJSysParm.ProgramElevM,Azimuth1,Elevation1);
		}
		else
		{
			g_HJSysParm.ProgramAzi = (int)(Azimuth0 *1000.0);
			g_HJSysParm.ProgramElev = (int)(Elevation0 *1000.0);
			g_HJSysParm.ProgramAziM = (int)(Azimuth1 *1000.0);
			g_HJSysParm.ProgramElevM = (int)(Elevation1 *1000.0);
		}

		if(g_HJSysParm.CurWorkType == ENUM_PROGR_MODE)
		{
			g_HJSysParm.RealTGroundAzi = (int)(Azimuth0 *1000.0);
			g_HJSysParm.RealTGroundElev = (int)(Elevation0 *1000.0);
			g_HJSysParm.RealTMeasureAzi = (int)(Azimuth1 *1000.0);
			g_HJSysParm.RealTMeasureElev = (int)(Elevation1 *1000.0);
			//	g_HJSysParm.ACU_Azloc = Azimuth0;
			//	g_HJSysParm.ACU_Eleloc = Elevation0;


			double dRoll = 0;
			double dPitch = 0;
			double dYaw = 0;
			double dAzimuth = 0.0;
			double dElevation = 0.0;
			dRoll =  g_HJSysParm.roll;
			dPitch = g_HJSysParm.pitch;
			dYaw = g_HJSysParm.yaw;

			Coordinate_eplaneAerToXyz_HJ(1,Azimuth1,Elevation1, &ex, &ey, &ez); //zhenm 
			//Coordinate_ePlanexyzToACUxyz_HJ(ex, ey,ez, g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz);
			// hj ePlane to ACU
			Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,g_HJSysParm.ACU_Azloc,90-g_HJSysParm.ACU_Eleloc,&sx, &sy, &sz); // 伺服角
			Coordinate_ACUxyzToaer_HJ_Pro(sx, sy, sz, &sRange, &sAzimuth,&sElevation);  // ACU 
#if 0 
			MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
			dAzimuth = dAzimuth - 90;
			if(dAzimuth >=360.0)
			{
				dAzimuth = dAzimuth - 360;
			}
			if(dAzimuth < 0.0)
			{
				dAzimuth = dAzimuth + 360;
			}
			// dElevation = dElevation + g_HJParmContrl.ACUModifyParm; //修正
			if(dElevation > 270)
			{
				dElevation = dElevation - 90;
			}
			//Coordinate_ACUxyzToENUxyz_HJ(sx, sy, sz, &e, &n, &u);
			//Coordinate_ENUxyzToaer_HJ(e, n, u, &Range, &Azimuth,&Elevation);  //
#endif
			sAzimuth = sAzimuth - 90;
			if(sAzimuth >=360.0)
			{
				sAzimuth = sAzimuth - 360;
			}
			if(sAzimuth < 0.0)
			{
				sAzimuth = sAzimuth + 360;
			}
			// sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //修正
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

			MeasureToGround(sAzimuth,sElevation,dYaw,dRoll,dPitch,&dAzimuth,&dElevation); // dadi
			g_HJSysParm.ACU_AzEcef = dAzimuth;
			g_HJSysParm.ACU_EleEcef = dElevation;

			// printf("[end to ACU---filter after:]Azimuth0= %f,Elevation0 = %f,ACU_Azloc = %f,  ACU_Eleloc = %f  ",Azimuth0,Elevation0,g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);
			printf("Saz = %f,  Sele = %f Maz = %f,  Mele = %f\n",sAzimuth,sElevation,dAzimuth,dElevation);

		}
	}

	//printf("[report :]--X= %f,Y = %f,Z = %f ,lan= %f,lon = %f,high = %f ,azi= %f  ele = %f \n",x,y,z,Plat, Plon, Pht,Azimuth1,Elevation1);
	//Coordinate_RightAngleToPolar_XX(x, y, z, &Range0, &Azimuth0, &Elevation0);
	*Range = Range1;
	*Azimuth = Azimuth1;
	*Elevation = Elevation1;

	// printf("[report :]--X= %f,Y = %f,Z = %f ,lan= %f,lon = %f,high = %f ,azi= %f  ele = %f \n",x,y,z,Plat, Plon, Pht,Azimuth0,Elevation0);
}



// 数引，程引、同站数据处理
void Coordinate_HJWGS84ToPolarPro2(int mode,int i,double yaw,double X, double Y, double Z, double Plat, double Plon, double Pht, double *Range1, double *Azimuth1, double *Elevation1)
{
	double Xr=0;
	double Yr=0;
	double Zr=0;

	double e=0;
	double n=0;
	double u=0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double Range = 0;
	double Azimuth = 0;
	double Elevation = 0;

	double x=0;
	double y=0;
	double z=0;
	double ax=0;
	double ay=0;
	double az=0;
	double ex=0;
	double ey=0;
	double ez=0;

	double sx = 0;
	double sy = 0;
	double sz = 0;
	double sRange = 0;
	double sAzimuth= 0;
	double sElevation = 0;

	Coordinate_WGS84ToECEF(Plon, Plat, Pht, &Xr, &Yr, &Zr);//pingtai
	Coordinate_ECEFToENU(Xr, Yr, Zr, X, Y, Z, Plon, Plat, &e, &n, &u); // 平台,卫星,平台 ,enu
	Coordinate_RightAngleToPolar(e, n, u,&Range, &Azimuth,&Elevation);  // 大地角度

	/* 数引*/
	if(mode == ENUM_DIGIT_MODE && fabs(X) > 0.0001 && fabs(Y) > 0.0001 && fabs(Z) > 0.0001)
	{
		/*
		1：未修正
		2：叠加时间偏置
		3：叠加角度偏置
		4：叠加时间和角度偏置
		 */
		if(g_SysParm[i].AngleCheck > 1)
		{
			g_HJSysParm.DigleadAziM = (int)((Azimuth + g_HJSysParm.ferrAzi) *1000.0);
			g_HJSysParm.DigleadElevM = (int)((Elevation + g_HJSysParm.ferrEle) *1000.0);
			printf("[DIGIT check:]--Azi = %d,Elev = %d,Azimuth1 = %f ,Elevation1= %f\n",g_HJSysParm.DigleadAziM,g_HJSysParm.DigleadElevM,Azimuth,Elevation);
		}
		else
		{
			g_HJSysParm.DigleadAzi = (int)(Azimuth *1000.0);
			g_HJSysParm.DigleadElev = (int)(Elevation *1000.0);
			g_HJSysParm.DigleadAziM = (int)(Azimuth *1000.0);
			g_HJSysParm.DigleadElevM = (int)(Elevation *1000.0);
		}

		if(g_HJSysParm.CurWorkType == ENUM_DIGIT_MODE)
		{
			g_HJSysParm.RealTGroundAzi = (int)(Azimuth *1000.0);
			g_HJSysParm.RealTGroundElev = (int)(Elevation *1000.0);
			HJ_GroundToMeasure(Azimuth,Elevation,&sAzimuth,&sElevation);
			g_HJSysParm.RealTMeasureAzi = (int)(sAzimuth *1000.0);
			g_HJSysParm.RealTMeasureElev = (int)(sElevation *1000.0);

			g_HJSysParm.ACU_AzEcef = Azimuth;
			g_HJSysParm.ACU_EleEcef = Elevation;

			//g_HJTrack_Report.Rplot.AzimuthENU = Azimuth; //站心系方位向
			//g_HJTrack_Report.Rplot.ElevationENU = Elevation; //站心系俯仰向

			//printf("[end to ACU---filter after:]Azimuth0= %f,Elevation0 = %f,ACU_Azloc = %f,  ACU_Eleloc = %f  ",Azimuth,Elevation,g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);
			//printf("Saz = %f,  Sele = %f Maz = %f,  Mele = %f\n",sAzimuth,sElevation,dAzimuth,dElevation);
		}
		g_HJSysParm.SR = sqrt(e*e + n*n + u*u);
		g_HJSysParm.SRTime = g_Time;  	// 数引R的时间
		g_HJSysParm.SRFlag = true; 	// 数引R有效标识
	}
	/* 程引*/
	else if(mode == ENUM_PROGR_MODE)
	{
		if(g_SysParm[i].AngleCheck > 1)
		{
			g_HJSysParm.ProgramAziM = (int)((Azimuth + g_HJSysParm.ferrAzi) *1000.0);
			g_HJSysParm.ProgramElevM = (int)((Elevation + g_HJSysParm.ferrEle) *1000.0);
			printf("[PROGR check:]--Azi = %d,Elev = %d,Azimuth1 = %f ,Elevation1= %f\n",g_HJSysParm.ProgramAziM,g_HJSysParm.ProgramElevM,Azimuth1,Elevation1);
		}
		else
		{
			g_HJSysParm.ProgramAzi = (int)(Azimuth *1000.0);
			g_HJSysParm.ProgramElev = (int)(Elevation *1000.0);
		}

		if(g_HJSysParm.CurWorkType == ENUM_PROGR_MODE)
		{
			g_HJSysParm.ACU_AzEcef = Azimuth;
			g_HJSysParm.ACU_EleEcef = Elevation;
			//g_HJTrack_Report.Rplot.AzimuthENU = Azimuth; //站心系方位向
			//g_HJTrack_Report.Rplot.ElevationENU = Elevation; //站心系俯仰向
			// 	 printf("[end to ACU---filter after:]Azimuth0= %f,Elevation0 = %f,ACU_Azloc = %f,  ACU_Eleloc = %f  \n",Azimuth,Elevation,g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);
			//printf("Saz = %f,  Sele = %f Maz = %f,  Mele = %f\n",sAzimuth,sElevation,dAzimuth,dElevation);

		}
	
		g_HJSysParm.CR = sqrt(e*e + n*n + u*u);
		g_HJSysParm.CRTime = g_Time;  	// 程引R的时间
		g_HJSysParm.CRFlag = true; 	// 程引R有效标识
	}
	//printf("[pro mode  to ACU:]Azimuth= %f,Elevation = %f,ACU_Azloc = %f,  ACU_Eleloc = %f \n",Azimuth,Elevation,g_HJSysParm.ACU_Azloc,g_HJSysParm.ACU_Eleloc);

	//printf("[report :]--X= %f,Y = %f,Z = %f ,lan= %f,lon = %f,high = %f ,azi= %f  ele = %f \n",x,y,z,Plat, Plon, Pht,Azimuth1,Elevation1);
	//Coordinate_RightAngleToPolar_XX(x, y, z, &Range0, &Azimuth0, &Elevation0);
	*Range1 = Range;
	*Azimuth1 = Azimuth                                                                                                                                                                                                                                                                                                ;
	*Elevation1 = Elevation;

	// printf("[report :]--X= %f,Y = %f,Z = %f ,lan= %f,lon = %f,high = %f ,azi= %f  ele = %f \n",x,y,z,Plat, Plon, Pht,Azimuth0,Elevation0);
}


void Coordinate_CarAERToENUAER_XX(int i,double yaw,double Range, double Azimuth, double Elevation, double *R, double *Az, double *Ele)
{
	double e=0;
	double n=0;
	double u=0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	double x=0;
	double y=0;
	double z=0;

	Coordinate_PolarToRightAngle_XX(Range,Azimuth,Elevation, &x, &y, &z);
	Coordinate_ENUToCarPosition(yaw, x,y,z, &e,&n,&u);   //test  xiangdui 
	Coordinate_RightAngleToPolar(e, n, u, &Range0, &Azimuth0, &Elevation0);

	g_SysParm[i].CurAzi = (int)(Azimuth0 *1000.0);
	g_SysParm[i].CurElev = (int)(Elevation0 *1000.0);
	g_SysParm[i].CmdAzi = (int)(Azimuth0 *1000.0);
	g_SysParm[i].CmdElev = (int)(Elevation0 *1000.0);

	printf("[report :]--YAW= %f,carR= %f,carA = %f, carE = %f ,ENUR= %f,ENUA = %f,ENYE = %f \n",yaw,Range,Azimuth,Elevation,Range0, Azimuth0, Elevation0);
	*R = Range0;
	*Az = Azimuth0;
	*Ele = Elevation0;
}

void Coordinate_ENUToWGS84(double e, double n, double u, double StaLong, double StaLat, double StaHeight, double *Tlat, double *Tlon, double *Th)
{
	double Xr=0;
	double Yr=0;
	double Zr=0;
	double X=0;
	double Y=0;
	double Z=0;
	double lamda=0;
	double phi=0;
	double h=0;

	Coordinate_WGS84ToECEF(StaLong, StaLat, StaHeight, &Xr, &Yr, &Zr);

	Coordinate_ENUToECEF(Xr,Yr,Zr,e,n,u,StaLat,StaLong,&X,&Y,&Z);

	Coordinate_ECEFToWGS84(X,Y,Z,&lamda,&phi,&h);

	*Tlon = lamda;
	*Tlat = phi;
	*Th = h;

}



void Coordinate_WGS84ToPolarSTK(double Ranged, double Azimuthd, double Elevationd, double Plat, double Plon, double Pht, double *Range, double *Azimuth, double *Elevation)
{
	double Xr=0;
	double Yr=0;
	double Zr=0;
	double X=0;
	double Y=0;
	double Z=0;
	double e=0;
	double n=0;
	double u=0;
	double Range0 = 0;
	double Azimuth0 = 0;
	double Elevation0 = 0;

	Coordinate_WGS84ToECEF(Plon, Plat, Pht, &Xr, &Yr, &Zr);  // ping tai

	Coordinate_PolarToRightAngle(Ranged, Azimuthd, Elevationd, &X, &Y, &Z);  //mubiao aer---XYZ

	Coordinate_ECEFToENU(Xr, Yr, Zr, X, Y, Z, Plon, Plat, &e, &n, &u);

	Coordinate_RightAngleToPolar(e, n, u, &Range0, &Azimuth0, &Elevation0);

	*Range = Range0;
	*Azimuth = Azimuth0;
	*Elevation = Elevation0;
}

/*
	double yaw 指北误差
	根据车头的指北误差, 将ENU坐标系转到车的坐标系下
 */
void Coordinate_ENUToCarPosition(double yaw1, double e, double n, double u, double *x, double *y, double *z)
{
	double yaw = 0;
	yaw = yaw1/180.0*ONEPI;

	// *x = cos(yaw) * e + sin(yaw) * n;
	// *y = -sin(yaw) * e + cos(yaw) * n;
	// *z = u;

	*x = cos(yaw) * e - sin(yaw) * n;
	*y = sin(yaw) * e + cos(yaw) * n;
	*z = u;
}

/*Range:(m),Azimuth:(deg), Elevation:(deg)*/
void Coordinate_PolarToRightAngle_XX(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = Azimuth/180.0*ONEPI;
	REle = Elevation/180.0*ONEPI;

	*X = Range*cos(REle)*sin(RAzi);
	*Y = Range*sin(REle);
	*Z = Range*cos(REle)*cos(RAzi);

}

void Coordinate_PolarToRightAngle_HJ(double Range, double Azimuth, double Elevation, double *X, double *Y, double *Z)
{
	double RAzi = 0;
	double REle = 0;

	RAzi = Azimuth/180.0*ONEPI;
	REle = Elevation/180.0*ONEPI;

	*X = Range*sin(REle)*cos(RAzi);
	*Y = Range*sin(REle)*sin(RAzi);
	*Z = Range*cos(REle);
}
unsigned int beam_plane_calc(int mode,float x, float y)// x 方位, y 俯仰
{
	int beamNum = 0;

	if(mode == 1)
	{
		if((x >= -80 ) && (x < -60))
		{
			beamNum = 1;
		}
		else if(x >= -60 && x < -20){
			beamNum = 2;
		}
		else if(x >= -20 && x < 20){
			beamNum = 3;
		}
		else if(x >= 20 && x < 60){
			beamNum =4;
		}
		else if(x >= 60 && x < 80){
			beamNum =5;
		}
	}
	else if(mode == 2)
	{
		if((x >= -80 ) && (x < -60))
		{
			beamNum = 6;
		}
		else if(x >= -60 && x < -30){
			beamNum = 7;
		}
		else if(x >= -30 && x < 30){
			beamNum = 8;
		}
		else if(x >= 30 && x < 60){
			beamNum =9;
		}
		else if(x >= 60 && x < 80){
			beamNum =10;
		}
	}
	return beamNum;

}

// 绕Y轴逆时针旋转的矩阵
RMATRIX rotat_y_axis_matrix(double az)
{
	RMATRIX			zdata;
	double RAzi = 0;
	RAzi = (az * 1.0) / 180.0*ONEPI;

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

// rot RMATRIX  绕Z轴逆时针旋转的矩阵
RMATRIX rotat_z_axis_matrix(double ele)
{
	RMATRIX			zdata;
	double RAzi = 0;
	RAzi = (ele * 1.0) / 180.0*ONEPI;

	//存储矩阵的行号和列号
	zdata.MatrixCol = 3;
	zdata.MatrixRow = 3;

	zdata.ArrayMatrix[0][0] = cos(RAzi);
	zdata.ArrayMatrix[0][1] = -sin(RAzi);
	zdata.ArrayMatrix[0][2] = 0;

	zdata.ArrayMatrix[1][0] = sin(RAzi);
	zdata.ArrayMatrix[1][1] = cos(RAzi);
	zdata.ArrayMatrix[1][2] = 0;

	zdata.ArrayMatrix[2][0] = 0;
	zdata.ArrayMatrix[2][1] = 0;
	zdata.ArrayMatrix[2][2] = 1;


	return zdata;	
}

// rot RMATRIX  绕 横摇 旋转的矩阵
RMATRIX rotat_R_axis_matrix(double aR)
{
	RMATRIX			zdata;
	double RAzi = 0;
	RAzi = (aR * 1.0)  / 180.0*ONEPI;

	//存储矩阵的行号和列号
	zdata.MatrixCol = 3;
	zdata.MatrixRow = 3;

	zdata.ArrayMatrix[0][0] = 1;
	zdata.ArrayMatrix[0][1] = 0;
	zdata.ArrayMatrix[0][2] = 0;

	zdata.ArrayMatrix[1][0] = 0;
	zdata.ArrayMatrix[1][1] = cos(RAzi);
	zdata.ArrayMatrix[1][2] = sin(RAzi);

	zdata.ArrayMatrix[2][0] = 0;
	zdata.ArrayMatrix[2][1] = -sin(RAzi);
	zdata.ArrayMatrix[2][2] = cos(RAzi);


	return zdata;	
}

// rot RMATRIX  绕 纵摇 旋转的矩阵
RMATRIX rotat_P_axis_matrix(double aP)
{
	RMATRIX			zdata;
	double RAzi = 0;
	RAzi = (1.0 * aP) / 180.0*ONEPI;

	//存储矩阵的行号和列号
	zdata.MatrixCol = 3;
	zdata.MatrixRow = 3;

	zdata.ArrayMatrix[0][0] = cos(RAzi);
	zdata.ArrayMatrix[0][1] = sin(RAzi);
	zdata.ArrayMatrix[0][2] = 0;

	zdata.ArrayMatrix[1][0] = -sin(RAzi);
	zdata.ArrayMatrix[1][1] = cos(RAzi);
	zdata.ArrayMatrix[1][2] = 0;

	zdata.ArrayMatrix[2][0] = 0;
	zdata.ArrayMatrix[2][1] = 0;
	zdata.ArrayMatrix[2][2] = 1;

	return zdata;	
}

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

// 目标在阵面系 x,y,z + 伺服编码角方位、俯仰 --->  目标在伺服系xyz
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
	dElevation = dElevation + g_HJParmContrl.ACUModifyParm; //修正
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
//所有单位为度，
//目标在伺服系方位、俯仰  + 惯导航向、横纵摇  ----->  目标再在大地系方位、俯仰
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

// hj 伺服方位俯仰 + 惯导的航向、横纵摇--->  大地系方位俯仰
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
	sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //g_HJParmContrl.ACUModifyParm; //修正
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


//目标在阵面系方位、俯仰 转为 目标在站心(大地系)方位、俯仰
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

	double ACU_Azloc = g_HJSysParm.ACU_Azloc;  //从ACU读取的方位角
	double ACU_Eleloc = 90-g_HJSysParm.ACU_Eleloc-g_HJParmContrl.ACUModifyParm;//从ACU读取的方俯仰

	dYaw = g_HJSysParm.yaw;
	//dRoll = -1.0  * g_HJSysParm.roll;
	//dPitch =  -1.0  * g_HJSysParm.pitch;

	dRoll = 1.0  * g_HJSysParm.roll;
	dPitch =  1.0  * g_HJSysParm.pitch;
	// 目标在阵面系 方位俯仰--> 目标在阵面系 x,y,z
	Coordinate_eplaneAerToXyz_HJ(1,Azimuth,Elevation, &ex, &ey, &ez); //阵面
	// 目标在阵面系 x,y,z + 伺服编码角方位、俯仰 --->  目标在伺服系xyz
	Coordinate_ePlanexyzToACUxyz_HJPro(ex, ey,ez,ACU_Azloc,ACU_Eleloc,&sx, &sy, &sz); // 伺服角
	// 目标在伺服系xyz ---->  目标在伺服系方位、俯仰
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
	// sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //修正
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
	//目标在伺服系方位、俯仰  + 惯导航向、横纵摇  ----->  目标再在大地系方位、俯仰
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
	// sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //修正
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
	ACU_Eleloc = 90 - g_ArrayAngleOut[0].ACUele - g_HJParmContrl.ACUModifyParm;
	
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
	// sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //修正
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
	ACU_Eleloc = 90 - imu_mes.ACU_Eleloc - g_HJParmContrl.ACUModifyParm;
	
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
	// sElevation = sElevation + g_HJParmContrl.ACUModifyParm; //修正
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
	ACU_Eleloc = 90 - g_HJSysParm.ACU_Eleloc - g_HJParmContrl.ACUModifyParm;

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
	// 	sElevation = sElevation - g_HJParmContrl.ACUModifyParm; //修正
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
	ACU_Eleloc = 90 - imu_mes.ACU_Eleloc - g_HJParmContrl.ACUModifyParm;

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
	// 	sElevation = sElevation - g_HJParmContrl.ACUModifyParm; //修正
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
	ACU_Eleloc = 90 - g_ArrayAngleOut[0].ACUele - g_HJParmContrl.ACUModifyParm;

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
	// 	sElevation = sElevation - g_HJParmContrl.ACUModifyParm; //修正
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


// hj大地转测量
void HJ_GroundToMeasure(double AZM1,double ELM1,double *AZM2,double *ELM2)
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

	double ACU_Azloc = 0;
	double ACU_Eleloc = 0;

	dYaw = g_HJSysParm.yaw;
	dRoll = 1.0  * g_HJSysParm.roll;
	dPitch =  1.0  * g_HJSysParm.pitch;
	
	ACU_Azloc = g_HJSysParm.ACU_Azloc;
	ACU_Eleloc = 90 - g_HJSysParm.ACU_Eleloc - g_HJParmContrl.ACUModifyParm;

	// hj 站心转测量
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
	// 	sElevation = sElevation - g_HJParmContrl.ACUModifyParm; //修正
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

	*AZM2 = sAzimuth;
	*ELM2 = sElevation;
}

// hj 东北天速转ECEF速度
void ENUToECEF_V(double Lon, double Lat, double vx_enu, double vy_enu, double vz_enu,double *vx_ecef, double *vy_ecef, double  *vz_ecef)
{
	double m_H[3][3];                                     // 用于 ENU-》ECEF速度转换矩阵
	double latitude_rad, longtitude_rad;
    double m_sinLatOfRadar;                               // 雷达站址，纬度sin值
    double m_cosLatOfRadar;                               // 雷达站址，纬度cos值
    double m_sinLongOfRadar;                              // 雷达站址，经度sin值
    double m_cosLongOfRadar;                              // 雷达站址，经度cos值
    
    latitude_rad = Lat * CVTA_DegreeRadian; //converting to radians
    longtitude_rad = Lon * CVTA_DegreeRadian; //converting to radians

    m_sinLatOfRadar = sin(latitude_rad);
    m_cosLatOfRadar = cos(latitude_rad);
    m_sinLongOfRadar = sin(longtitude_rad);
    m_cosLongOfRadar = cos(longtitude_rad);

    m_H[0][0] = -m_sinLongOfRadar;
    m_H[0][1] = -m_sinLatOfRadar * m_cosLongOfRadar;
    m_H[0][2] = m_cosLatOfRadar * m_cosLongOfRadar;

    m_H[1][0] = m_cosLongOfRadar;
    m_H[1][1] = -m_sinLatOfRadar * m_sinLongOfRadar;
    m_H[1][2] = m_cosLatOfRadar * m_sinLongOfRadar;

    m_H[2][0] = 0;
    m_H[2][1] = m_cosLatOfRadar;
    m_H[2][2] = m_sinLatOfRadar;
    //     V = H*uM(4:6);
    *vx_ecef = m_H[0][0] * vx_enu + m_H[0][1] * vy_enu + m_H[0][2] * vz_enu;
    *vy_ecef = m_H[1][0] * vx_enu + m_H[1][1] * vy_enu + m_H[1][2] * vz_enu;
    *vz_ecef = m_H[2][0] * vx_enu + m_H[2][1] * vy_enu + m_H[2][2] * vz_enu;
}

