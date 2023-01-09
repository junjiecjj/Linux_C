

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
在堆上的时候，由于是分批次分配内存（首先new出或malloc多少行，然后每一行再分别new），因此其存放是平行的几条连续存储，每一行是连续的，行与行之间并不连续。为此，我们尝试创建一个2X4的二维矩阵如下
*/
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
}



