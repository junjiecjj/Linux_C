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

    return 0;
}