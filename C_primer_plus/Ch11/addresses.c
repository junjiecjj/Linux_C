//  addresses.c  -- addresses of strings
#define MSG "I'm special"

#include <stdio.h>
int main()
{
    char ar[] = "I'm special";
    const char *pt = "I'm special";
    printf("address of \"I'm special\": %p \n", "I'm special");
    printf("              address ar: %p\n", ar);
    printf("              address pt: %p\n", pt);
    printf("          address of MSG: %p\n", MSG);
    printf("address of \"I'm special\": %p \n", "I'm special");

    return 0;
}
