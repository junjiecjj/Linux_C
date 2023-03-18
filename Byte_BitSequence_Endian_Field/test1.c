#include <stdio.h>
#include <stdlib.h>



void Int2Binary(int x, int *bin)
{
    int LEN = 8;
    int a = 4;
    int bin[8] = {};
    for(int i=0; i<LEN; ++i)
    {
        bin[LEN-1-i]  = (a>>i) %2;
    }
    for(int i;  i<LEN; ++i)
    {
        printf("%d ", bin[i]);
    }

    return 0;

}



int main(int argc, char *argv[])
{
    int LEN = 8;
    int a = 4;
    int bin[8] = {};
    for(int i=0; i<LEN; ++i)
    {
        bin[LEN-1-i]  = (a>>i) %2;
    }
    for(int i;  i<LEN; ++i)
    {
        printf("%d ", bin[i]);
    }

    int Int = 7;
    int *Bin;
    Bin = new int[LEN];

    return 0;

}
