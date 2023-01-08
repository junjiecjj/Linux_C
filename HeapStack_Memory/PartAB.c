


#include "PartAB.h"


int count = 0;       // 文件作用域，外部链接，静态变量


//================================ 综合演示：静态变量(外部链接(文件作用域)、内部链接(文件作用域)、无链接(块作用域)), 寄存器变量，自动变量 ===========================================


static int total = 0;   //静态存储期，内部链接，文件作用域，


int Partab(void)
{
    int value;       // automatic variable
    register int i;  // register variable

    printf("Enter a positive integer (0 to quit): ");
    while (scanf("%d", &value) == 1 && value > 0)
    {
        ++count;     // use file scope variable
        for (i = value; i >= 0; i--)
            accumulate(i);
        printf("Enter a positive integer (0 to quit): ");
    }
    report_count();

    return 0;
}

void report_count()
{
    printf("Loop executed %d times\n", count);
}

void accumulate(int k)  // k是块作用域，无链接
{
    static int subtotal = 0;  //无链接，块作用域的静态变量，静态存储期，

    if (k <= 0)
    {
        printf("loop cycle: %d\n", count);
        printf("subtotal: %d; total: %d\n", subtotal, total);
        subtotal = 0;
    }
    else
    {
        subtotal += k;
        total += k;
    }
}
