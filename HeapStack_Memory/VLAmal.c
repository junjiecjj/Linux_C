


//=================================== 动态内存和变长数组 =========================================


//================================================================================================================
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
// int item[len] = {0};  // erroe,  在C语言中不允许对数组进行动态的定义，定义数组时的长度必需为常量。   使用常量定义数组长度。定义数组的时候，指定的数组长度为变量。
int item1[LEN] = {0}; // 使用宏定义#define代替只读类型const，#define和const的不同：由const修饰的类型在内存中占空间而#define不占空间，#define只是在编译前将要编译的源文件中相应的部分使用字符串替换例如前面的代码在编译前会被预处理为

int *ptd = NULL;
// 不能将全局变量初始化为一个无法在编译时期确定的值,需要在编译时期确定全局变量的值，而 malloc 需要在运行时分配内存，所以就出现这个错误了。
// ptd = (int *)malloc(22*sizeof(int)); //error ：  initializer element is not constant



int *VLAmal()
{
    int n = 0;

    return 0;
}
