#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double MSE2Fig(double *uu_pix, double *uu_pix_hat, int len)
{
	double mse = 0.0;

	for(int i = 0; i < len; ++i){
		mse += pow( (uu_pix[i] -uu_pix_hat[i]), 2);
	}
	mse /= len;

	return mse;
}

double PSNR2Fig(double *uu_pix, double *uu_pix_hat, int len, int maxpixel)
{
	double psnr = 0.0, mse = 0.0;
	mse = MSE2Fig(uu_pix, uu_pix_hat, len);

	psnr = 20.0 * log10( (double) maxpixel/mse );

	return psnr;
}

void changeStrInFun(char *str, int len)
{
    for(int i = 0; i < len; ++i)
    {
        str[i] = 'a'+i;
    }
}

int main(int argc, char *argv[])
{
    double *arr;
    double *arr1;
    double mse, psnr;
    int len = 10;
    arr = (double *)malloc(len * sizeof(double));
    arr1 = (double *)malloc(len * sizeof(double));

    for(int i = 0; i < len; ++i)
    {
        arr[i] = (i + 1) * 1.0;
        arr1[i] = arr[i] ;
    }

    mse = MSE2Fig(arr, arr1, len);
    psnr = PSNR2Fig(arr, arr1, len, 255);

    printf("mse = %.4lf, psnar = %.4lf \n", mse, psnr);

    int m_pic_W = 1751, m_pic_H = 891, m_pic_C = 3;


    int MidH = 0, MidW = 0, MidC = 3;
	MidC = m_pic_C;

    int m_pic_pix_mid_len = 9360960; // 1572960  9360960

	double k  = 0;
	k = (double) m_pic_W/m_pic_H;




	MidH = (int) floor(sqrt((double) m_pic_pix_mid_len / (MidC * k)));
	MidW = (int) floor(k*MidH);


    printf("m_pic_H = %d, m_pic_W = %d, m_pic_C = %d\n", m_pic_H, m_pic_W, m_pic_C);
    printf("MidH = %d, MidW = %d, MidC = %d\n", MidH, MidW, MidC);

    char  MidBefDecSaveFilename[80];

    char MidAfEncSaveFilename[90];
	char  pic[20];
	char  name[20];
    double snr = 2.25;

    sprintf(pic, "Lena");
	sprintf(name, "lena");
    sprintf(MidAfEncSaveFilename, "./%s_AfEnc_MiddleResult/%s_AfEnc_Mid_SNR=%4.2f.txt", pic, name, snr);

    printf("\n\nMidAfEncSaveFilename = %s\n\n\n", MidAfEncSaveFilename);

    char Str[20];
    printf("Str = %s\n\n", Str);
    changeStrInFun(Str, 19);
    printf("Str = %s\n\n", Str);


    return 0;
}
