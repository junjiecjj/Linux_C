#include<stdio.h>
#include<stdlib.h>
#include "DOA.h"
#include "Net.h"
#include "Globle.h"
#include "Define.h"
#include "Struct.h"
#include "FormatTransfer.h"

STR2  BCN;
//extern const double PI;

int main(int argc, char *argv[])
{
	BCN.a = 1;
	BCN.b = 12.12;
	BCN.c = 13.13;
	BCN.d = 19;
	showstr(&BCN);

	byby();

	printf("***************** sizeof() ******************************\n");
	double A[4] = {12.12, 13.13, 14.14, 15.15};

	int    B[4] = {12 , 13 , 14 , 15 };

	float  C[4] = {12.21 , 13.31 , 14.41 , 15.51 };

	char    D[4] = {'a' , 'b' , 'c' , 'd' };

	unsigned int     E[4] = {12 , 13 , 14 , 15 };

    short int     F[4] = {12 , 13 , 14 , 15 };

    unsigned short int G[4] = {12 , 13 , 14 , 15 };

    long int H[4] = {12 , 13 , 14 , 15 };

    unsigned long int I[4] = {12 , 13 , 14 , 15 };

    long long int J[4] = {12 , 13 , 14 , 15 };

    unsigned long long int K[4] = {12 , 13 , 14 , 15 };

	printf("sizeof(A) = %d\n", sizeof(A));
	printf("sizeof(double) = %d\n", sizeof(double));


	printf("sizeof(B) = %d\n", sizeof(B));
	printf("sizeof(int) = %d\n", sizeof(int));


	printf("sizeof(C) = %d\n", sizeof(C));
	printf("sizeof(float) = %d\n", sizeof(float));


	printf("sizeof(D) = %d\n", sizeof(D));
	printf("sizeof(char) = %d\n", sizeof(char));


	printf("sizeof(E) = %d\n", sizeof(E));
	printf("sizeof(unsigned int) = %d\n", sizeof(unsigned int));


	printf("sizeof(F) = %d\n", sizeof(F));
	printf("sizeof(short int) = %d\n", sizeof(short int));

 	printf("sizeof(G) = %d\n", sizeof(G));
	printf("sizeof(unsigned short int) = %d\n", sizeof(unsigned short int));

	printf("sizeof(H) = %d\n", sizeof(G));
    printf("sizeof(long int) = %d\n", sizeof(long int));

	printf("sizeof(I) = %d\n", sizeof(H));
	printf("sizeof(unsigned long int) = %d\n", sizeof(unsigned long int));

	printf("sizeof(J) = %d\n", sizeof(I));
	printf("sizeof(long long int) = %d\n", sizeof(long long int));

	printf("sizeof(K) = %d\n", sizeof(J));
	printf("sizeof(unsigned long long int) = %d\n", sizeof(unsigned long long int));




    printf("sizeof(TAP_HJSYS_PARM_MANAGE) = %d\n", sizeof(TAP_HJSYS_PARM_MANAGE));  //系统工作参数

	printf("sizeof(TAP_HJ_ABTION_BAND_DATA_MSG) = %d\n", sizeof(TAP_HJ_ABTION_BAND_DATA_MSG));// 基带发给BCN结构体
	printf("sizeof(TAP_HJ_GET_FM_FPGA_DATA_MSG) = %d\n", sizeof(TAP_HJ_GET_FM_FPGA_DATA_MSG));// DBF发给BCN的调频结构体
	printf("sizeof(TAP_HJ_GET_SM_FPGA_DATA_MSG) = %d\n", sizeof(TAP_HJ_GET_SM_FPGA_DATA_MSG));// DBF发给BCN的单频结构体
	printf("sizeof(TAP_HJ_GET_SUMDIFF_FPGA_DATA_MSG) = %d\n", sizeof(TAP_HJ_GET_SUMDIFF_FPGA_DATA_MSG));// DBF发给BCN的和差结构体
    printf("sizeof(TAP_HJ_GET_SUMAMP_FPGA_DATA_MSG) = %d\n", sizeof(TAP_HJ_GET_SUMAMP_FPGA_DATA_MSG));// DBF发给BCN的9波束结构体
	printf("sizeof(TAP_ABTION_RAPIDIO_DATA_MSG) = %d\n", sizeof(TAP_ABTION_RAPIDIO_DATA_MSG));   //
	printf("sizeof(DirectionPLOTIQ) = %d\n", sizeof(DirectionPLOTIQ));

	printf("*****************  enum ****************************\n");
    int a = ENUM_SCAN_SCAN;

    if(a == 1)
    {
        printf("a == ENUM_SCAN_SCAN \n");
    }

	printf("*****************  struct ****************************\n");
	STR1 S1;
	S1.a = 12;
	S1.b = 12.12;
	S1.c = 13.13;
	S1.d = 14;
	S1.e = 101;
	S1.f = 111;

	STR2 *p2 = &S1;

	showstr(p2);
	//free(p2);

	printf("***************** static ****************************\n");

	int i = 3;
	printf("Pi = %10.8lf\n", PI);
	printf("MONTHS[%d] = %s\n",i, MONTHS[i]);

	printf("***************** Define ****************************\n");
	printf("MAX_L = %d\n", MAX_L);


    printf("***************** FormatTransfer.h  ****************************\n");

    Formattransfer_test();









    return 0;
}
