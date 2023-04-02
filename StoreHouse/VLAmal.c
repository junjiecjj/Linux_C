

#include  "VLAmal.h"




/**************************************************************************************************************************
    被调函数创建一个数组并返回指针， 供主调函数访问， 然后主调函数在末尾调用free()释放之前被调函数分配的内存。
    另外， free()所用的指针变量可以与 malloc()的指针变量不同， 但是两个指针必须储存相同的地址。 但是， 不能释放同一块内存两次。
***************************************************************************************************************************/
//使用const声明的对象是一个运行时对象，无法使用其作为某个量的初值、数组的长度、case的值或在类型的情形中使用。例如:
//注释中为报错信息
// const int length = 256;
// char buzzer[length];        //error: variably modified ‘buffer’ at file scope
// int i = length;             //error: initializer element is not constant

// switch (x) {
// case length:            //error: case label does not reduce to an integer constant
// 	/* code */
// 	 break;
// default:
// 	 break;
// }

const int len = 10;
// int item[len] = {0};  // error,  在C语言中不允许对数组进行动态的定义，定义数组时的长度必需为常量。   使用常量定义数组长度。定义数组的时候，指定的数组长度为变量。
int item1[LEN] = {0}; // 使用宏定义#define代替只读类型const，#define和const的不同：由const修饰的类型在内存中占空间而#define不占空间，#define只是在编译前将要编译的源文件中相应的部分使用字符串替换例如前面的代码在编译前会被预处理为

int *GlobalPoint = NULL;
// 不能将全局变量初始化为一个无法在编译时期确定的值,需要在编译时期确定全局变量的值，而 malloc 需要在运行时分配内存，所以就出现这个错误了，因此只能在某个函数中为全局指针分配内存。
// ptd = (int *)malloc(LEN*sizeof(int)); //error ：  initializer element is not constant，初始化静态或全局变量时不能调用函数，常量表达式中不允许调用函数。


// 对于C语言层级来说，main函数的入口函数，任何函数都必须从main作为入口被调用，malloc是main之外的函数，如果放在外面，没有谁可以调用它，因此，不仅仅是malloc，任何函数都不能在全局情况下被调用。
// 初始化静态或全局变量时不能调用函数。下面的代码声明一个静态变量，并试图用malloc来初始化：
// static int *p = malloc(sizeof(int));
// 编译时会提示错误消息，全局变量也一样。对于静态变量，可以通过在后面用一个单独的语句给变量分配内存来避免这个问题。但是全局变量不能用单独的赋值语句，因为全局变量是在函数和可执行代码外部声明的，赋值语句这类代码必须出现在函数中：
// static int *p;
// pi = malloc(sizeof(int));

// static int *globalp;
int *globalp;


/*
现在， 我们有3种创建数组的方法：
1、声明数组时， 用常量表达式表示数组的维度， 用数组名访问数组的元素。 可以用静态内存或自动内存创建这种数组。
2、声明变长数组（C99新增的特性） 时， 用变量表达式表示数组的维度，用数组名访问数组的元素。 具有这种特性的数组只能在自动内存中创建。
3、声明一个指针， 调用malloc()， 将其返回值赋给指针， 使用指针访问数组的元素。 该指针可以是静态的或自动的。
*/
int VLAarr1[10][10];  // 1、声明数组时， 用常量表达式表示数组的维度， 用数组名访问数组的元素。 可以用静态内存创建这种数组。
int VLAarr2[LEN][LEN];  // 1、声明数组时， 用常量表达式表示数组的维度， 用数组名访问数组的元素。 可以用静态内存创建这种数组。LEN是宏，等同于上一行。

static int rows = 2;
static int cols = 3;
// int VLAarr3[rows][cols];   // error,2、只能在自动内存中创建。

void InitStaticMemory(void)
{
    printf("******************** 初始化静态指针变量 *********************\n");
    globalp = (int *) malloc(sizeof(int)*LEN);  //3、声明一个指针， 调用malloc()， 将其返回值赋给指针， 使用指针访问数组的元素。 该指针可以是静态的或自动的。
    for(int i=0; i<LEN; ++i)
    {
        globalp[i] = i+2;
    }
}

void ChangeStaticMem(void)
{
    printf("******************** 改变静态指针变量的数组元素的值 *********************\n");
    printf("******************** 改变前的静态指针变量 ********************\n");
    Display1DIntArray(globalp, LEN);
    globalp[2] = 76;
    Display1DIntArray(globalp, LEN);
}


void FreeStaticMem(void)
{
    printf("******************** 改变后静态变量 *********************\n");
    Display1DIntArray(globalp, LEN);
    free(globalp);
}



// 在函数内分配内存，但在这个函数不释放，在另一个函数释放内存
int *MallocAndReturnLocalPoint()
{
    int *p = (int *)malloc(LEN*sizeof(int));
    for(int i=0; i<LEN; i++)
    {
        p[i] = i+1;
    }

    return p;
}

// 被调函数返回的内存赋值给另一个指针，然后使用这个指针。
void  UseLocalPoint(void)
{
    // 利用全局指针打印这块内存的值。
    //  displayArray1(GlobalPoint, LEN); //段错误，得先为GlobalPoint 分配内存，因为还没给GlobalPoint分配内存，无打印

    // 不能先为GlobalPoint分配内存，这样后面free只是释放为GlobalPoint分配的内存，而 MallocAndReturnLocalPoint 的局部内存p永远无法释放，而是直接将函数返回的指针给GlobalPoint即可。
    // GlobalPoint =  (int *)malloc(  LEN*sizeof(int));
    // 将被调函数的分配的内存返回指针并赋值给全局的指针。这时GlobalPoint和MallocAndReturnLocalPoint中的 p所指向的地址一样。
    GlobalPoint  =  MallocAndReturnLocalPoint();

    // 再利用全局指针打印这块内存的值。
    Display1DIntArray(GlobalPoint, LEN);

    GlobalPoint[0] = 765;

    Display1DIntArray2(GlobalPoint, LEN);

}

// 释放局部内存
void  FreeLocalPoint(int *LocalPoint)
{
    free(LocalPoint);
}

const int days[MONTHS] = {31,28,31,30,31,30,31,31,30,31,30,31};


void DisplayMonth(void)
{
    // const int days[MONTHS] = {31,28,31,30,31,30,31,31,30,31,30,31};
    for (int index = 0; index < MONTHS; index++)
        printf("Month %d has %2d days.\n", index +1, days[index]);

}

/**************************************************************************************************************************
            动态内存和变长数组

C99定义的这种变长数组的使用是有限制的，不能像在C++等语言中一样自由使用
变长数组有以下限制：
1、变长数组必须在程序块的范围内定义，不能在文件范围内定义变长数组；
2、无论是在函数中申明还是作为函数形参声明，变长数组不能用static或者extern修饰；
3、变长数组不能作为结构体或者联合的成员，只能以独立的数组形式存在；
4、变长数组的作用域为块的范围，对应地，变长数组的生存时间为当函数执行流退出变长数组所在块的时
5、 不能在声明中初始化它们，
***************************************************************************************************************************/

//================================================================================================================

























