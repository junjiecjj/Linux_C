

#include "ArrayPoint.h"

//演示数组元素的地址和指针+1的含义
int pnt_addr(void)
{
    short dates [SIZE];
    short * pti;
    short index;
    double bills[SIZE];
    double * ptf;

    pti = dates;    // assign address of array to pointer
    ptf = bills;
    printf("%23s %15s\n", "short", "double");
    for (index = 0; index < SIZE; index ++)
        printf("pointers + %d: %10p %10p\n",  index, pti + index, ptf + index);

    return 0;
}


/*
用栈声明的时候很明显，都是连续的。
在堆上的时候，由于是分批次分配内存（首先new出或malloc多少行，然后每一行再分别new），因此其存放是平行的几条连续存储，每一行是连续的，行与行之间并不连续。为此，我们尝试创建一个2X4的二维矩阵如下:
*/
// 测试C语言的栈内存分配
void C_stack(){
    printf("====== C stack ======\n");
    char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }
    printf("=====================\n\n");
}
// 测试C语言的堆内存分配
void C_malloc(){
    printf("====== C malloc ======\n");

    char **str = (char **)malloc(2*sizeof(char *));

    for (int i = 0; i < 2; i++)
        str[i] = (char*)malloc(4*sizeof(char));
    char s = 'A';
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            str[i][j] = s++;
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++)
        free(str[i]);
    free(str);
    printf("====================\n\n");
}


// void CXX_stack(){
//     cout<<"====== Cpp stack ======"<<endl;
//     char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
//     for(int i = 0; i < 2; i++){
//         for(int j = 0; j < 4; j++){
//             cout<<"["<<str[i][j]<<"]"<<(void *)&str[i][j]<<"\t";
//         }
//         cout<<endl;
//     }
//     cout<<"======================"<<endl<<endl;
// }
// void CXX_new(){
//     cout<<"====== Cpp new ======"<<endl;

//     char **str = new char *[2];
//     for (int i = 0; i < 2; i++)
//         str[i] = new char [4];
//     char s = 'A';
//     for (int i = 0; i < 2; i++){
//         for(int j = 0; j < 4; j++){
//             str[i][j] = s++;
//             cout<<"["<<str[i][j]<<"]"<<(void *)&str[i][j]<<"\t";
//         }
//         cout<<endl;
//     }

//     for (int i = 0; i < 2; i++)
//         delete []str[i];
//     delete str;
//     cout<<"===================="<<endl;
// }

// 打印一维数组
void Show1DArrayKindsOfWays(void)
{
    printf("**********************************************************************************\n");
    printf("***************************** 申明、分配、打印一维数组 ******************\n");
    printf("**********************************************************************************\n\n");

    int len  = 5;
    int Arr[len];
    for(int i=0; i<len; ++i)
    {
        Arr[i] = i+1;
    }
    Display1DIntArray(Arr, 5);
    Display1DIntArray2(Arr, 5);
    Display1DIntArray3(Arr, 5);
    Display1DIntArray4(Arr, 5);

    int sum1 = Sum1DIntArray1(Arr,len);
    int sum2 = Sum1DIntArray2(Arr,Arr+len);
    printf("一维数组求和, sum1 = %d, sum2 = %d\n",sum1,  sum2);
}


void Show2DArrayKindsOfWaysC(void)
{
    printf("**********************************************************************************\n");
    printf("***************************** 申明、分配、打印二维数组 ******************\n");
    printf("**********************************************************************************\n");
    int m = 5, n = 10;
    printf("================== A[m][n]的方式申请数组=============================\n");

    int A[m][n]; // 这样的内存一定是是连续的；用栈声明的时候很明显，都是连续的
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i * n + j;
        }
    }
    // printf("打印A[m][n]方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&A[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("打印数组A第一次......\n");
    Display2DIntArray(m, n, A);  //ok

    printf("打印数组A第二次......\n");
    Display2DIntArray1(m, n, A);  //ok


    printf("打印数组A第三次......\n");
    Display2DIntArrayNorm(m, n, A);  //ok


    printf("打印数组A第四次......\n");
    //  Display2DIntArray2DPoint(m, n, &A[0][0]); //不能这么用
    //  Display2DIntArray2DPoint(m, n, A); //不能这么用

    printf("打印数组A第五次......\n");
    Display2DIntArrayUse1D(m, n, &A[0][0]); //ok，因为这样的分配是连续的，所以当成一维数组没问题

    printf("================== int **D 的方式申请数组,不连续分配=============================\n");

    int **D;
    //这样分配内存不连续,行内连续，行间不一定连续，
    D = (int **)malloc(m * sizeof(int *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < m; i++)
    {
        D[i] = (int *)malloc(n * sizeof(int)); //每一行一定连续
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = i * n + j;
        }
    }

    // printf("打印**D方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&D[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("打印**D方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&D[i*n+j]);
    //     }
    //     printf("\n");
    // }

    printf("打印数组D第一次......\n");
    printf("D = %p\n",D);
    printf("D[0] = %p\n",D[0]);
    printf("D[0][0] = %p\n",&D[0][0]);
    //Display2DIntArray(m, n,&D[0]); //这样编译不会出错，但是结果不对
    printf("\n");
    //Display2DIntArray(m, n, D); //这样编译不会出错，但是结果不对
    printf("\n");
    //Display2DIntArray(m, n, D[0]); //这样编译不会出错，但是结果不对

    printf("打印数组D第二次......\n");
    //Display2DIntArray1(m, n, D); //这样编译不会出错，但是结果不对

    printf("打印数组D第三次......\n");
    //Display2DIntArrayNorm(m, n, D); //这样编译不会出错，但是结果不对

    printf("打印数组D第四次......\n");
    //Display2DIntArrayUse1D(m, n, &D[0][0]); //这样编译不会出错，但是结果不对
    //Display2DIntArrayUse1D(m, n, D);        //这样编译不会出错，但是结果不对

    printf("打印数组D第五次......\n");
    Display2DIntArray2DPoint(m, n, D); //正确的方式，推荐

    Free2DMatrix(D, m, n);
    // for(int i=0; i<m; i++)
    // {
    //     free(D[i]);
    // }
    // free(D);


    printf("================== int **E 的方式申请数组,连续分配=============================\n");

    int **E;
    E = (int **)malloc(sizeof(int *) * m);    //分配指针数组
    E[0] = (int *)malloc(sizeof(int) * m * n);//一次性分配所有空间
    for(int i=1; i<m; i++)
    {
        E[i] = E[i-1] + n;
    }//采用如上内存分配方法，意味着将E的值初始化为m*n的二维数组首地址,且这块内存连续

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            E[i][j] =  i * n + j;
        }
    }
    // printf("打印**E方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&E[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("E[1][2] = %d\n", E[1][2]);


    printf("打印数组E第一次......\n");
    //Display2DIntArray(m, n, E[0]); //这样编译不会出错，但是结果不对

    printf("打印数组E第二次......\n");
    //Display2DIntArray1(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第三次......\n");
    //Display2DIntArrayNorm(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第四次......\n");
    Display2DIntArrayUse1D(m, n, &E[0][0]); //这样可以，把内存连续分配的二维数组当做一维打印
    printf("\n");
    Display2DIntArrayUse1D(m, n, E[0]); //这样可以，把内存连续分配的二维数组当做一维打印
    printf("\n");
    //Display2DIntArrayUse1D(m, n, &E[0]); //这样编译不会出错，但是结果不对
    printf("\n");
    // Display2DIntArrayUse1D(m, n, E[0][0]); //  段错误
    printf("\n");
    //Display2DIntArrayUse1D(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第五次......\n");
    Display2DIntArray2DPoint(m, n, E); //正确的方式


    printf("%ld\n", sizeof(E));    //8，指针
    printf("%ld\n", sizeof(E[0])); //8，指针

    free(E[0]);  //
    // for(int i=0; i<m; i++)
    // {  段错误
    //     free(E[i]);
    // }
    free(E); E = NULL;
}



/*********************************************************************
下面分别描述了指针变量的基本操作。
·赋值：可以把地址赋给指针。例如，用数组名、带地址运算符（&）的变量名、另一个指针进行赋值。在该例中，把urn数组的首地址赋给了ptr1，该地址的编号恰好是0x7fff5fbff8d0。变量ptr2获得数组urn的第3个元素（urn[2]）的地址。注意，地址应该和指针类型兼容。也就是说，不能把double类型的地址赋给指向int的指针，至少要避免不明智的类型转换。C99/C11已经强制不允许这样做。
·解引用：*运算符给出指针指向地址上存储的值。因此，*ptr1的初值是100，该值存储在编号为0x7fff5fbff8d0的地址上。

·取址：和所有变量一样，指针变量也有自己的地址和值。对指针而言，&运算符给出指针本身的地址。本例中，ptr1存储在内存编号为0x7fff5fbff8c8的地址上，该存储单元存储的内容是0x7fff5fbff8d0，即urn的地址。因此&ptr1是指向ptr1的指针，而ptr1是指向utn[0]的指针。

·指针与整数相加：可以使用+运算符把指针与整数相加，或整数与指针相加。无论哪种情况，整数都会和指针所指向类型的大小（以字节为单位）相乘，然后把结果与初始地址相加。因此ptr1+4与&urn[4]等价。如果相加的结果超出了初始指针指向的数组范围，计算结果则是未定义的。除非正好超过数组末尾第一个位置，C保证该指针有效。

·递增指针：递增指向数组元素的指针可以让该指针移动至数组的下一个元素。因此，ptr1++相当于把ptr1的值加上4（我们的系统中int为4字节），ptr1指向urn[1]（见图10.4，该图中使用了简化的地址）。现在ptr1的值是0x7fff5fbff8d4（数组的下一个元素的地址），*ptr的值为200（即urn[1]的值）。注意，ptr1本身的地址仍是0x7fff5fbff8c8。毕竟，变量不会因为值发生变化就移动位置。

·指针减去一个整数：可以使用-运算符从一个指针中减去一个整数。指针必须是第1个运算对象，整数是第2个运算对象。该整数将乘以指针指向类型的大小（以字节为单位），然后用初始地址减去乘积。所以ptr3 - 2与&urn[2]等价，因为ptr3指向的是&urn[4]。如果相减的结果超出了初始指针所指向数组的范围，计算结果则是未定义的。除非正好超过数组末尾第一个位置，C保证该指针有效。

·递减指针：当然，除了递增指针还可以递减指针。在本例中，递减ptr2使其指向数组的第2个元素而不是第3个元素。前缀或后缀的递增和递减运算符都可以使用。注意，在重置ptr1和ptr2前，它们都指向相同的元素urn[1]。

·指针求差：可以计算两个指针的差值。通常，求差的两个指针分别指向同一个数组的不同元素，通过计算求出两元素之间的距离。差值的单位与数组类型的单位相同。例如，程序清单10.13的输出中，ptr2 - ptr1得2，意思是这两个指针所指向的两个元素相隔两个int，而不是2字节。只要两个指针都指向相同的数组（或者其中一个指针指向数组后面的第1个地址），C都能保证相减运算有效。如果指向两个不同数组的指针进行求差运算可能会得出一个值，或者导致运行时错误。

·比较：使用关系运算符可以比较两个指针的值，前提是两个指针都指向相同类型的对象。

在递增或递减指针时还要注意一些问题。编译器不会检查指针是否仍指向数组元素。C只能保证指向数组任意元素的指针和指向数组后面第1个位置的指针有效。但是，如果递增或递减一个指针后超出了这个范围，则是未定义的。另外，可以解引用指向数组任意元素的指针。但是，即使指针指向数组后面一个位置是有效的，也不能保证可以解引用这样的越界指针。

解引用未初始化的指针说到注意事项，一定要牢记一点：千万不要解引用未初始化的指针。例如，考虑下面的例子：
*/
    // int *pt; //未初始化的指针
    // *pt = 5; //严重错误

    /*
为何不行？第2行的意思是把5存储在pt指向的位置。但是pt未被初始化，其值是一个随机值，所以不知道5将存储在何处。这可能不会出什么错，也可能会擦写数据或代码，或者导致程序崩溃。切记：创建一个指针时，系统只分配了存储指针本身的内存，并未分配存储数据的内存。因此，在使用指针之前，必须先用已分配的地址初始化它。例如，可以用一个现有变量的地址初始化该指针（使用带指针形参的函数时，就属于这种情况）。或者还可以使用第12章将介绍的malloc()函数先分配内存。无论如何，使用指针时一定要注意，不要解引用未初始化的指针！
     double *pt1;  //未初始化的指针
    *pt1 = 2.4;  //严重错误
*********************************************************************/

int ptr_ops(void)
{
    int urn[5] = {100,200,300,400,500};
    int * ptr1, * ptr2, *ptr3;

    ptr1 = urn;         // assign an address to a pointer
    ptr2 = &urn[2];     // ditto
    // dereference a pointer and take
    // the address of a pointer
    printf("\n pointer value, dereferenced pointer, pointer address:\n");
    printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n",  ptr1, *ptr1, &ptr1);

    // pointer addition
    ptr3 = ptr1 + 4;
    printf("\nadding an int to a pointer:\n");
    printf("ptr1 + 4 = %p, *(ptr1 + 4) = %d\n",  ptr1 + 4, *(ptr1 + 4));
    ptr1++;            // increment a pointer
    printf("\nvalues after ptr1++:\n");
    printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n",  ptr1, *ptr1, &ptr1);
    ptr2--;            // decrement a pointer
    printf("\nvalues after --ptr2:\n");
    printf("ptr2 = %p, *ptr2 = %d, &ptr2 = %p\n",   ptr2, *ptr2, &ptr2);
    --ptr1;            // restore to original value
    ++ptr2;            // restore to original value
    printf("\nPointers reset to original values:\n");
    printf("ptr1 = %p, ptr2 = %p\n", ptr1, ptr2);
    // subtract one pointer from another
    printf("\nsubtracting one pointer from another:\n");
    printf("ptr2 = %p, ptr1 = %p, ptr2 - ptr1 = %td\n",    ptr2, ptr1, ptr2 - ptr1);
    // subtract an integer from a pointer
    printf("\nsubtracting an int from a pointer:\n");
    printf("ptr3 = %p, ptr3 - 2 = %p\n",   ptr3,  ptr3 - 2);

    return 0;
}


// 指针与多维数组


void  TestArrayPoint(void)
{
    printf(" ************************* 演示数组元素的地址和指针+1的含义 ************************\n");
    pnt_addr();
    printf(" ************************* 演示A[m][n]内存连续和int **A; malloc分配的内存不连续 ************************\n");
    C_stack();
    C_malloc();
    // CXX_stack();
    // CXX_new();
    // 打印分配一维二维数组
    Show1DArrayKindsOfWays();
    Show2DArrayKindsOfWaysC();

    ptr_ops();
}



