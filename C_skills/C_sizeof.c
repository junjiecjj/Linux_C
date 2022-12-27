#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef unsigned long ULONG;
typedef enum { FALSE = 0, TRUE = 1 } BOOL;
typedef unsigned char UCHAR;



//海基目标起始结构体
/*点迹信息*/
typedef struct PLOT_BASE_INFO_CO {
  ULONG dSystemTime; /*! 时间 */
  double dRange;     /*! 距离 */
  double dAzimuth;   /*! 方位 */
  double dElevation; /*! 俯仰 */
  double xlocal;     /*! x方向余弦 */
  double zlocal;     /*! z方向余弦 */
  double dAmp;       // 目标幅度
  double dsore;      // 目标质量
  UCHAR circle;      // 圈数
  UCHAR bp;          // 模拟波位号
  UCHAR sbp;         // 数字波位号
} PLOT_BASE_INFO_CO;

/*!  相关点迹信息 */
typedef struct PLOT_MANAGE_CO {
  BOOL bUsedFlag;       /*!< 是否已经在使用标志*/
  ULONG dSystemTime;    /*! 时间 */
  unsigned short Frame; /*!  更新帧数 */
  PLOT_BASE_INFO_CO plot[5];
} PLOT_MANAGE_CO;

typedef struct STRUCT1 {
  int a;
  double b;
  float c;
  unsigned char d;
  int e;
  int f;
} STR1;

typedef struct STRUCT2 {
  int a;
  double b;
  float c;
  unsigned char d;
  // int e;
  // int f;
} STR2;

enum {
  ENUM_SCAN_RESET = 0,           // 复位
  ENUM_SCAN_SCAN = 1,            // 扫描
  ENUM_SCAN_POINT = 2,           // 指向--跟踪
  ENUM_SCAN_TRACK = 3,           // 跟踪
  ENUM_SCAN_ZERO_POINT = 4,      // 中心波束
  ENUM_SCAN_OPEN_POINT = 5,      // 开环跟踪
  ENUM_SCAN_RECORD_POINT = 6,    // 闭环跟踪
  ENUM_SCAN_MEAR_POINT = 7,      // 测量
  ENUM_SCAN_XYZFILTER_POINT = 8, // x,y,z跟踪
  ENUM_SCAN_SMOOTH_POINT = 9,    // 平滑
  ENUM_SCAN_OPEN_POINT_MOVE = 10 // 开环波束调度测试
};

void showstr(STR2 *p) {
  printf("a = %d, b = %lf, c = %f, d = %hhu, \n", p->a, p->b, p->c, p->d);
}

int main() {
  long double A1[4] = {12.12, 13.13, 14.14, 15.15};
  long double *LongDoubleP = NULL;

  double A[4] = {12.12, 13.13, 14.14, 15.15};
  double *DoubleP = NULL;

  int B[4] = {12, 13, 14, 15};
  int *IntP = NULL;

  float C[4] = {12.21, 13.31, 14.41, 15.51};
  float *FloatP = NULL;

  char D[4] = {'a', 'b', 'c', 'd'};
  char *CharP = NULL;

  unsigned int E[4] = {12, 13, 14, 15};
  unsigned int *UintP = NULL;

  short int F[4] = {12, 13, 14, 15};
  short int *SintP = NULL;

  unsigned short int G[4] = {12, 13, 14, 15};
  unsigned short int *USintP = NULL;

  long int H[4] = {12, 13, 14, 15};
  long int *LintP = NULL;

  unsigned long int I[4] = {12, 13, 14, 15};
  unsigned long int *ULintP = NULL;

  long long int J[4] = {12, 13, 14, 15};
  long long int *LLintP = NULL;

  unsigned long long int K[4] = {12, 13, 14, 15};
  unsigned long long int *ULLintP = NULL;

  printf("sizeof(A1) = %d\n", sizeof(A1));
  printf("sizeof(long double) = %d\n", sizeof(long double));
  printf("sizeof(long double  *) = %d\n", sizeof(long double *));

  printf("sizeof(A) = %d\n", sizeof(A));
  printf("sizeof(double) = %d\n", sizeof(double));
  printf("sizeof(double *) = %d\n", sizeof(double *));

  printf("sizeof(B) = %d\n", sizeof(B));
  printf("sizeof(int) = %d\n", sizeof(int));
  printf("sizeof(int *) = %d\n", sizeof(int *));

  printf("sizeof(C) = %d\n", sizeof(C));
  printf("sizeof(float) = %d\n", sizeof(float));
  printf("sizeof(float *) = %d\n", sizeof(float *));

  printf("sizeof(D) = %d\n", sizeof(D));
  printf("sizeof(char) = %d\n", sizeof(char));
  printf("sizeof(char *) = %d\n", sizeof(char *));

  printf("sizeof(E) = %d\n", sizeof(E));
  printf("sizeof(unsigned int) = %d\n", sizeof(unsigned int));
  printf("sizeof(unsigned int *) = %d\n", sizeof(unsigned int *));

  printf("sizeof(F) = %d\n", sizeof(F));
  printf("sizeof(short int) = %d\n", sizeof(short int));
  printf("sizeof(short int *) = %d\n", sizeof(short int *));

  printf("sizeof(G) = %d\n", sizeof(G));
  printf("sizeof(unsigned short int) = %d\n", sizeof(unsigned short int));
  printf("sizeof(unsigned short int *) = %d\n", sizeof(unsigned short int *));

  printf("sizeof(H) = %d\n", sizeof(H));
  printf("sizeof(long int) = %d\n", sizeof(long int));
  printf("sizeof(long int *) = %d\n", sizeof(long int *));

  printf("sizeof(I) = %d\n", sizeof(H));
  printf("sizeof(unsigned long int) = %d\n", sizeof(unsigned long int));
  printf("sizeof(unsigned long int *) = %d\n", sizeof(unsigned long int *));

  printf("sizeof(J) = %d\n", sizeof(I));
  printf("sizeof(long long int) = %d\n", sizeof(long long int));
  printf("sizeof(long long int *) = %d\n", sizeof(long long int *));

  printf("sizeof(K) = %d\n", sizeof(J));
  printf("sizeof(unsigned long long int) = %d\n",
         sizeof(unsigned long long int));
  printf("sizeof(unsigned long long int *) = %d\n",
         sizeof(unsigned long long int *));


  STR1 S1;
  S1.a = 12;
  S1.b = 12.12;
  S1.c = 13.13;
  S1.d = 14;
  S1.e = 101;
  S1.f = 111;

  STR2 *p2 = &S1;

  showstr(p2);

  int a = ENUM_SCAN_SCAN;

  if (a == 1) {
    printf("aaaa\n");
  }
  return 0;
}
