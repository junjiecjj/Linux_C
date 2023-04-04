#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void changeStrInFun(char *str, int len)
{
    for(int i = 0; i < len; ++i)
    {
        str[i] = 'a'+i;
    }
}

int main(int argc, char *argv[])
{

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
