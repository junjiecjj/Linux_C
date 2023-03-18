#include <iostream>
using namespace std;
#include <cstdio>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

#define   LEN  8

void Int2Binary(int x, int *bin)
{

    for(int i=0; i<LEN; ++i)
    {
        bin[LEN-1-i]  = (x>>i) %2;
    }
    for(int i=0;  i<LEN; ++i)
    {
        printf("%d ", bin[i]);
    }
    printf("Int2Binary\n");
}

void Dec2Bin(int d, int *b, int len_b)
{
	int i;

	for (i = 0; i < len_b; i++)
		b[len_b-i-1] = (d >> i) % 2;

	return;
}

void SeqDec2Bin(int *bin, int *dec, int len_dec, int len_symbol)
{
	int i, j, t;

	t = 0;
	for (i = 0; i < len_dec; i++){
		for (j = 0; j < len_symbol; j++){
			bin[t] = (dec[i] >> (len_symbol-1-j)) & 1;
			t++;
		}
	}

	return;
}

int Bin2Dec(int *bin, int len_bin)
{
	int i, j, t;
	int dec = 0;

	for (i = 0; i < len_bin; i++) {
		dec += bin[i] * pow(2, len_bin-1-i);
	}

	return dec;
}

void SeqBin2Dec(int *bin, int *dec, int len_dec, int len_symbol)
{
	int i, j, t;

	t = 0;
	for (i = 0; i < len_dec; i++){
		dec[i] = 0;
		for (j = 0; j < len_symbol; j++){
			dec[i] = (dec[i] << 1) ^ bin[t];
			t++;
		}
	}

	return;
}

int main(int argc, char *argv[])
{
    printf("=================== Dec2Bin和Dec2Bin ====================\n");
    int Int = 255;
    int *Bin;
    Bin = new int[LEN];
    for(int i=0;  i<LEN; ++i)
    {
        printf("%d ", Bin[i]);
    }
    printf("main1\n");
    // Int2Binary(Int, Bin);
    Dec2Bin(Int, Bin, LEN);

    for(int i=0;  i<LEN; ++i)
    {
        printf("%d ", Bin[i]);
    }
    printf("main2\n");

    int dec = 0;
    dec = Bin2Dec(Bin, LEN);

    printf("dec = %d\n",dec);
    delete []Bin;
    printf("===================== SeqDec2Bin和SeqBin2Dec ==================\n");

    int *seqdec;
    int *seqbin;
    int n = 2;
    seqbin = new int[LEN*n];
    seqdec = new int[n];
    seqdec[0] = 255;
    seqdec[1] = 7;

    SeqDec2Bin(seqbin, seqdec, n, LEN);

    for(int i=0; i<LEN*n; ++i)
    {
        printf("%d ", seqbin[i]);
    }
    printf("\n");

    int *seqdeC;
    seqdeC = new int[n];
    SeqBin2Dec(seqbin, seqdeC, n, LEN);

    for(int i=0; i<n; ++i)
    {
        printf("%d ", seqdeC[i]);
    }

    delete []seqdec;
    delete []seqbin;

    return 0;
}