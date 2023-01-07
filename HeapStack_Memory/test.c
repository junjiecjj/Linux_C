#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/socket.h>
#include <stddef.h>
#include <locale.h>
#include <time.h>
#include <complex.h>

#define Len 20

char *strA()
{
    char * str ="hello world";
    return str;
}


int main(int argc, char *argv[])
{
    char *str = (char *) malloc(sizeof(char)*Len);
    //str = strA();
    //str = "hello,jack....";
    for(int i=0; i<Len; i++){
        str[i] = 'A'+i;
    }

    printf("%s\n", str);

    free(str);

    return 0;

}