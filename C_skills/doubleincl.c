// doubincl.c -- include header twice
#include <stdio.h>
#include "names.h"


int main()
{
    names winner = {"Less", "Ismoor"};
    printf("The winner is %s %s.\n", winner.first,
           winner.last);
    return 0;
}
