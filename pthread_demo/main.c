#include <stdio.h>
#include <stdlib.h>
#define	ONEPI				3.14159265358979323846f 	/* 180 degree				*/
#define M_2PI  6.28318530717958647692f
#define	ALMOST_ZERO			1.0e-15


/* 零值 */
double atan2XY(double x, double y)
{
    double r;

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

// WGS 84坐标系到XYZ
/*Lon,Lat:(deg), Height:(m)*/
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

//XYZ到东北天
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
// 东北天--》角度
void Coordinate_ENUxyzToaer_HJ(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
{
    *Range = sqrt(X*X + Y*Y +Z*Z);
    *Azimuth = atan2XY(Z,X)*180.0/ONEPI;
    *Elevation = asin(Y/(*Range))*180.0/ONEPI;
}
void Coordinate_RightAngleToPolar(double X, double Y, double Z, double *Range, double *Azimuth, double *Elevation)
    {
        *Range = sqrt(X*X + Y*Y +Z*Z);
        *Azimuth = atan2XY(X,Y)*180.0/ONEPI;
        *Elevation = asin(Z/(*Range))*180.0/ONEPI;
    }

void TXT_FileMake(double X,double Y,double Z,int num)//生成弹道轨迹TXT文本
{
    int count=0;
    double i_x=800;//m
    double i_y=2000;//m
    double i_z=500;//m
    int Rtime=0;
    FILE *fp;
    fp=fopen("track","w+");
    fprintf(fp,"%c\t%c\t%c\t%c\t\n",'T','X','Y','Z');
    fprintf(fp,"%d\t%lf\t%lf\t%lf\t\n",Rtime,X,Y,Z);

    for(count;count<num;count++)
    {
        Rtime=Rtime+1;
        X=X+i_x;
        Y=Y+i_y;
        Z=Z+i_z;
        fprintf(fp,"%d\t%lf\t%lf\t%lf\t\n",Rtime,X,Y,Z);
    }

    fclose(fp);

}

int main()
{
    double WGS_Lon=117.20936207;//目标所在地心坐标系下的经度
    double WGS_Lat=31.000556;//目标所在地心坐标系下的纬度
    double WGS_Height=5000.89;//目标高度
    double STA_Lon=117.20936207;//站心所在地心坐标系下的经度
    double STA_Lat=32.04974846;//站心所在地心坐标系下的纬度
    double STA_Height=72.63000000;//站心高度
    double WGS_X=0;//目标所在地心坐标系下的X轴数值
    double WGS_Y=0;//目标所在地心坐标系下的Y轴数值
    double WGS_Z=0;//目标所在地心坐标系下的Z轴数值
    double WGS_Xr=0;//站心设备所在地心坐标系下的X轴数值
    double WGS_Yr=0;//站心设备所在地心坐标系下的Y轴数值
    double WGS_Zr=0;//站心设备所在地心坐标系下的Z轴数值
    double RefLon=117.20936207;//站心设备所在地心坐标系下的经度
    double RefLat=32.04974846;//站心设备所在地心坐标系下的纬度
    double ENU_e=0;//目标所在大地坐标系下的X轴数值
    double ENU_n=0;//目标所在大地坐标系下的Y轴数值
    double ENU_u=0;//目标所在大地坐标系下的Z轴数值
    double ENU_Ran=0;//目标所在大地坐标系下的距离
    double ENU_Azi=0;//目标所在大地坐标系下的方位角
    double ENU_Ele=0;//目标所在大地坐标系下的俯仰角


    Coordinate_WGS84ToECEF(WGS_Lon, WGS_Lat, WGS_Height, &WGS_X, &WGS_Y, &WGS_Z);//目标在地心坐标系经纬高转换为XYZ坐标系
    Coordinate_WGS84ToECEF(STA_Lon, STA_Lat, STA_Height, &WGS_Xr, &WGS_Yr, &WGS_Zr);//站心在地心坐标系经纬高转换为XYZ坐标系
    Coordinate_ECEFToENU(WGS_Xr,WGS_Yr,WGS_Zr,WGS_X,WGS_Y,WGS_Z,RefLon,RefLat,&ENU_e,&ENU_n,&ENU_u);
   // Coordinate_ENUxyzToaer_HJ(ENU_e,ENU_n,ENU_u,&ENU_Ran,&ENU_Azi,&ENU_Ele);
    Coordinate_RightAngleToPolar(ENU_e,ENU_n,ENU_u,&ENU_Ran,&ENU_Azi,&ENU_Ele);
    printf("WGS84 To ECEF Result:\n");
    printf("WGS_X：%lf\nWGS_Y：%lf\nWGS_Z：%lf\n ",WGS_X,WGS_Y,WGS_Z);
    printf("ENUxyz To Toaer_HJ Result:\n");
    printf("ENU_Ran：%lf\nENU_Azi：%lf\nENU_Ele：%lf\n ",ENU_Ran,ENU_Azi,ENU_Ele);


    TXT_FileMake(WGS_X,WGS_Y,WGS_Z,10);

    return 0;
}
