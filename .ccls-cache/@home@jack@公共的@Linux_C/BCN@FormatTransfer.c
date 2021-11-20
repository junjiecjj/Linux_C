
#include "FormatTransfer.h"
#include <stdio.h>
#include <stdlib.h>

//大小端转换不分有无符号
// short 大小端转换
#define _swap16(x)                                                             \
  (unsigned short)((((unsigned short)(x & 0x00ff)) << 8) |                     \
                   (((unsigned short)(x & 0xff00)) >> 8));

// int 大小端转换
#define _swap32(x)                                                             \
  (unsigned int)((((unsigned int)(x & 0x000000ff)) << 24) |                    \
                 (((unsigned int)(x & 0x0000ff00)) << 8) |                     \
                 (((unsigned int)(x & 0x00ff0000)) >> 8) |                     \
                 (((unsigned int)(x & 0xff000000)) >> 24));

// double或64位的数据类型大小端转换
//#define		_swap64(x)   (unsigned long long)((((unsigned long
// long)(x & 0x00000000000000FF)) << 56) | (((unsigned long long)(x &
// 0x000000000000FF00)) << 40)	|(((unsigned long long)(x & 0x0000000000FF0000))
//<< 24)	| (((unsigned long long)(x & 0x00000000FF000000)) << 8)	|
//(((unsigned long long)(x & 0x000000FF00000000)) >> 8)	| (((unsigned long
// long)(x & 0x0000FF0000000000)) >> 24)	| (((unsigned long long)(x &
// 0x00FF000000000000)) >> 40)	| (((unsigned long long)(x &
// 0xFF00000000000000)) >> 56))
#define _swap64(x)                                                             \
  (unsigned long long)((((unsigned long long)(x & 0x00000000000000FF))         \
                        << 56) |                                               \
                       (((unsigned long long)(x & 0x000000000000FF00))         \
                        << 40) |                                               \
                       (((unsigned long long)(x & 0x0000000000FF0000))         \
                        << 24) |                                               \
                       (((unsigned long long)(x & 0x00000000FF000000)) << 8) | \
                       (((unsigned long long)(x & 0x000000FF00000000)) >> 8) | \
                       (((unsigned long long)(x & 0x0000FF0000000000)) >>      \
                        24) |                                                  \
                       (((unsigned long long)(x & 0x00FF000000000000)) >>      \
                        40) |                                                  \
                       (((unsigned long long)(x & 0xFF00000000000000)) >> 56))

// unsigned int 或 int 大小端转换
unsigned int WAP_u32(unsigned int x) {
  return (unsigned int)(((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) |
                        ((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24));
}

// unsigned short 大小端转换
unsigned short WAP_u16(unsigned short x) {
  return (unsigned short)(((x & 0xff00) >> 8) | ((x & 0x00ff) << 8));
}

// DOUBLE大小端转换
DOUBLE double_swap_64(DOUBLE pData) {

  DOUBLE *pNewValue;
  DOUBLE pData0 = 0;

  UCHAR *pValue;
  UCHAR Value[8];

  pValue = (UCHAR *)&pData;

  Value[0] = pValue[7];
  Value[1] = pValue[6];
  Value[2] = pValue[5];
  Value[3] = pValue[4];
  Value[4] = pValue[3];
  Value[5] = pValue[2];
  Value[6] = pValue[1];
  Value[7] = pValue[0];

  pNewValue = (DOUBLE *)Value;
  pData0 = *pNewValue;

  return pData0;
}

// float大小端转换
float float_swap_32(float pData) {

  float *pNewValue;
  float pData0 = 0;

  UCHAR *pValue;
  UCHAR Value[4];

  pValue = (UCHAR *)&pData;

  Value[0] = pValue[3];
  Value[1] = pValue[2];
  Value[2] = pValue[1];
  Value[3] = pValue[0];

  pNewValue = (float *)Value;
  pData0 = *pNewValue;

  return pData0;
}

//字符串转十六进制,不是特别好用
void StrToHex(char *pbDest, char *pbSrc, int nLen) {
  char h1, h2;
  char s1, s2;
  int i;

  for (int i = 0; i < nLen / 2; ++i) {
    h1 = pbSrc[2 * i];
    h2 = pbSrc[2 * i + 1];

    s1 = toupper(h1) - 0x30;
    if (s1 > 9) {
      s1 -= 7;
    }
    s2 = toupper(h2) - 0x30;
    if (s2 > 9) {
      s2 -= 7;
    }
    pbDest[i] = s1 * 16 + s2;
  }
}

//十六进制转字符串,不是特别好用
void HexToStr(char *pszDest, char *pbSrc, int nlen) {
  char ddl, ddh;
  for (int i = 0; i < nlen; ++i) {
    ddh = 48 + pbSrc[i] / 16;
    ddl = 48 + pbSrc[i] % 16;
    if (ddh > 57) {
      ddh = ddh + 7;
    }
    if (ddl > 57) {
      ddl = ddl + 7;
    }
    pszDest[i * 2] = ddh;
    pszDest[i * 2 + 1] = ddl;
  }
  pszDest[nlen * 2] = '\0';
}

//字符串转十进制,如果带负号,不是特别好用
int my_atoi(const char *str) {
  int value = 0;
  int flag = 1;       //判断符号
  while (*str == ' ') //跳过字符串前面的空格
  {
    str++;
  }
  if (*str == '-') {
    flag = 0;
    str++;
  } else if (*str == '+') {
    flag = 1;
    str++;
  } else if (*str >= '9' || *str <= '0') {
    return 0;
  }
  while (*str != '\0' && *str <= '9' && *str >= '0') {
    value = value * 10 + *str - '0'; //将数字字符串转化为对应的整数形式
    str++;
  }

  if (flag == 0) {
    value = -value;
  }

  return value;
}

/*字符串转十进制,如果不带负号,不是特别好用
    pbdest:函数输出
    pbSrc:输入的需要转换的字符串
*/
void StrtoDec(uint32_t *pbDest, char *pbSrc, int nLen) {
  int i;
  int tmp = 0;
  if (nLen > 10) {
    *pbDest = 0;
  }
  tmp = 1;
  *pbDest = 0;

  for (i = nLen - 1; i >= 0; i--) {
    *pbDest += tmp * (*(pbSrc + i) - '0');
    tmp = tmp * 10;
  }
}

//字符串转十进制,可以是浮点数,不是特别好用
// m^n函数
//返回值：m^n次方
u32 NMEA_pow(u8 m, u8 n) {
  u32 result = 1;
  while (n--) {
    result *= m;
  }
  return result;
}

/*字符串转十进制,可以是浮点数,不是特别好用
字符串转换为数字，以','或'*'结束
buf:数字存储区
dx: 小数点位数，返回给调用函数
返回值:转换后的数值
*/
int NMEA_Str2num(u8 *buf, u8 *dx) {
  u8 *p = buf;
  u32 ires = 0, fres = 0;
  u8 ilen = 0, flen = 0, i;
  u8 mask = 0;
  int res;

  while (1) {
    if (*p == '-') //是负数
    {
      mask |= 0x02;
      p++;
    }
    if (*p == ',' || *p == '*') //遇到结束符
    {
      break;
    }
    if (*p == '.') //遇到小数了
    {
      mask |= 0x01;
      p++;
    } else if (*p > '9' || (*p < '0')) //有非法字符
    {
      ilen = 0;
      flen = 0;
      break;
    }
    if (mask & 0x01) {
      flen++;
    } else {
      ilen++;
    }
    p++;
  }

  if (mask & 0x02) {
    buf++;
  }
  for (i = 0; i < ilen; ++i) //得到整数部分数据
  {
    ires += NMEA_pow(10, ilen - 1 - i) * (buf[i] - '0');
  }
  if (flen > 5) //最多取5位参数
  {
    flen = 5;
  }
  *dx = flen; //小数点位数
  for (i = 0; i < flen; i++) {
    fres = NMEA_pow(10, flen - 1 - i) * (buf[ilen + 1 + i] - '0');
  }
  res = ires * NMEA_pow(10, flen) + fres;
  if (mask & 0x02) {
    res = -res;
  }
  return res;
}

//十进制转字符串,不是特别好用
u16 DecToStr(u8 *pSrc, u16 SrcLen, u8 *pObj) {
  u16 i = 0;
  for (i = 0; i < SrcLen; ++i) {
    sprintf((char *)(pObj + i * 2), "%02d", *(pSrc + i));
  }
  *(pObj + i * 2) = '\0';
  return (i * 2);
}

// U32转换为U8
void U32ToU8Array(uint8_t *buf, uint32_t u32Value) {
  buf[0] = ((u32Value >> 24) & 0xFF);
  buf[1] = ((u32Value >> 16) & 0xFF);
  buf[2] = ((u32Value >> 8) & 0xFF);
  buf[3] = (u32Value & 0xFF);
}

// U8转换为U32
void U8ArrayToU32(uint8_t *buf, uint32_t *u32Value) {
  *u32Value = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + (buf[3] << 0);
}

/*
将输入的int, float,unsigned int,long int, unsigned long
int等4个字节的数据类型以二进制格式输出 ，适用于小端字节序
*/
void PrintIntBinary(int num) {
  printf("sizeof(num) = %zd\n", sizeof(num));
  printf("int %d binary is:\n", num);
  unsigned char *p = (unsigned char *)&num + sizeof(int) -
                     1; // p先指向num后面第三个字节的地址，即num最高位字节地址
  for (int i = 0; i < sizeof(int); ++i) //依次处理4个字节(32位)
  {
    int j =
        *(p - i); //取每个字节的首地址，从高位字节到低位字节，即p,p-1,p-2,p-3
    for (int k = 7; k >= 0;
         k--) //处理每个字节的8个位，注意字节内部的二进制是大端
    {
      if (j &
          (1
           << k)) // 1左移k位，当前字节的内容j进行或运算，如k=7,00000000&10000000=0
                  // -> 该字节的最高位为0
      {
        printf("1");
      } else {
        printf("0");
      }
    }
    printf(" ");
  }
  printf("\n");
}

/*
将输入的unsigned char等1个字节的数据类型以二进制格式输出，适用于小端字节序
*/
void PrintUCHARBinary(unsigned char num) {
  printf("sizeof(num) = %zd\n", sizeof(num));
  printf("unsigned char %d binary is:\n", num);

  unsigned char *p = (unsigned char *)&num;

  for (int k = 7; k >= 0; k--) {
    if (*p & (1 << k)) {
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}

//可以将任何数据类型打印为二进制格式,大端小端都有用
void AnyTobites(unsigned char *start, int len) {
  if (checkBiglittle()) //小端
  {
    // start = start + (len - 1);
    for (int i = 0; i < len; ++i) {
      // start = start - i;
      for (int j = 7; j >= 0; j--) {
        printf("%d", (start[len - 1 - i] >> j) & 0x01);
      }
      printf(" ");
    }
  } else //大端
  {
    for (int i = 0; i < len; ++i) {
      for (int j = 7; j >= 0; j--) {
        printf("%d", (start[i] >> j) & 0x01);
      }
      printf(" ");
    }
  }

  printf("\n");
}

//输出p指向的数据(可以为任何类型)的每个字节的地址和每个字节的16进制表示
void dump(void *p, int L) {
  char *s = p;
  int i;
  for (int i = 0; i < L; ++i, s++) {
    printf("%p:%x\n", s, *s);
  }
  s--;
  for (int i = 0; i < L; ++i, s--) {
    printf("%x ", *s);
  }
  printf("\n");
}

/*
将输入的float等4个字节的数据类型以二进制格式输出，适用于小端字节序
*/
void PrintFloatBinary(float num) {
  printf("sizeof(num) = %zd\n", sizeof(num));
  printf("float %f binary is:\n", num);
  unsigned char *p = (unsigned char *)&num + sizeof(float) -
                     1; // p先指向num后面第三个字节的地址，即num最高位字节地址
  for (int i = 0; i < sizeof(float); ++i) //依次处理4个字节(32位)
  {
    int j =
        *(p - i); //取每个字节的首地址，从高位字节到低位字节，即p,p-1,p-2,p-3
    for (int k = 7; k >= 0;
         k--) //处理每个字节的8个位，注意字节内部的二进制是大端
    {
      if (j &
          (1
           << k)) // 1左移k位，当前字节的内容j进行或运算，如k=7,00000000&10000000=0
                  // -> 该字节的最高位为0
      {
        printf("1");
      } else {
        printf("0");
      }
    }
    printf(" ");
  }
  printf("\n");
}

/*
将输入的double等8个字节的数据类型以二进制格式输出，适用于小端字节序
*/
void PrintDoubleBinary(double num) {
  printf("sizeof(num) = %zd\n", sizeof(num));
  printf("double %lf binary is:\n", num);
  unsigned char *p = (unsigned char *)&num + sizeof(double) -
                     1; // p先指向num后面第三个字节的地址，即num最高位字节地址
  for (int i = 0; i < sizeof(double); ++i) //依次处理4个字节(32位)
  {
    int j =
        *(p - i); //取每个字节的首地址，从高位字节到低位字节，即p,p-1,p-2,p-3
    for (int k = 7; k >= 0;
         k--) //处理每个字节的8个位，注意字节内部的二进制是大端
    {
      if (j &
          (1
           << k)) // 1左移k位，当前字节的内容j进行或运算，如k=7,00000000&10000000=0
                  // -> 该字节的最高位为0
      {
        printf("1");
      } else {
        printf("0");
      }
    }
    printf(" ");
  }
  printf("\n");
}

/*
将输入的float等4个字节的数据类型以二进制格式输出
*/
void PrintFloatBinary1(float num) {
  int L = sizeof(num) * 8;
  printf("L = %d\n", L);
  char bin[L];
  int t = 1;
  int *f = (int *)(&num);
  for (int i = 0; i < L; ++i) {
    bin[i] = (*f) & (t << L - i) ? 1 : 0;
  }

  for (int i = 0; i < L; ++i) {
    printf("%d", bin[i]);
    if (i == 0) {
      printf(", ");
    }
    if (i == 8) {
      printf(", ");
    }
  }
  printf("\n ");
}

//判断系统大小端,使用联合体判断
BOOL checkBiglittle() {
  BOOL res = 1;
  union u {
    int a;
    char b;
  } c;
  c.a = 1;
  if (c.b == 1) //小端返回true,大端返回false
  {
    // printf("Little endian\n");
  } else {
    res = 0;
    // printf("Big endian\n");
  }
  return res;
}

//判断系统大小端，使用指针判断
BOOL checkBiglittle1() {
  BOOL res = 1;
  int i = 1;
  unsigned char *p;
  p = (unsigned char *)&i;
  if (*p) //小端返回true,大端返回false
  {
    printf("Little endian\n");
  } else {
    res = 0;
    printf("Big endian\n");
  }
  return res;
}

//判断系统大小端，使用指针判断
BOOL checkBiglittle2() {
  BOOL res = true;
  int num = 0x12345678;
  char *p = &num;
  if (*p == 0x78) {
    printf("Little endian\n");
  } else {
    res = false;
    printf("Big endian\n");
  }
  return res;
}

//判断系统大小端，使用强制类型转换判断
BOOL checkBiglittle3() {
  BOOL res = 1;
  short a = 0x0061;
  if ((char)a == 'a') //小端返回true,大端返回false
  {
    printf("Little endian\n");
  } else {
    res = 0;
    printf("Big endian\n");
  }
  return res;
}

BOOL checkBiglittle4() {
  int a = 0x12345678;
  // printf("%x\n", a);
  // printf("%d\n", a);

  char *p = (char *)&a;

  for (int i = 0; i < sizeof(a); i++) {
    printf("内存地址：%p, 所存数据：%.2x\n", &p[i], p[i]);
  }
  /*
  内存地址：012FF7A4, 所存数据：56
  内存地址：012FF7A5, 所存数据：34
  内存地址：012FF7A6, 所存数据：12
  内存地址：012FF7A7, 所存数据：00
  */
}

void Formattransfer_test() {

  printf("***********************字符串转整数**********************\n");
  char S[10] = "1234";
  int result = 0;

  result = my_atoi(S);
  printf("result = %d\n", result);

  char *S1 = "129852";
  printf("S1 = %s\n", S1);
  uint32_t a = 12;
  uint32_t *R1 = &a; //这里不能使用uint32_t *R1 = NULL;

  StrtoDec(R1, S1, 6);
  printf("*R1 = %d\n", *R1);

  printf("*********************** U32 To U8 **********************\n");

  uint8_t *buf = NULL;
  buf = (uint8_t *)malloc(4 * sizeof(uint8_t));
  uint32_t u32value = 65;
  U32ToU8Array(buf, u32value);
  printf("buf[0] = %x, buf[1] = %x, buf[2] = %x, buf[3] = %x\n", buf[0], buf[1],
         buf[2], buf[3]);
  printf("buf[0] = %c, buf[1] = %c, buf[2] = %c, buf[3] = %c\n", buf[0], buf[1],
         buf[2], buf[3]);

  printf("*********************** U8 To U32 **********************\n");

  uint8_t buff[4] = {'\0', '\0', '\0', 'A'};
  // buff = (uint8_t *)malloc(4 * sizeof(uint8_t));
  // buff = {'\0', '\0','\0','2'};
  uint32_t tmp = 0;
  uint32_t *p = &tmp;
  U8ArrayToU32(buff, p);
  printf("u32Value = %d\n", *p);

  printf("*********************** _itoa() **********************\n");

  int a1 = 258;
  char s[32];
  /* itoa(a1, s, 2); */
  /* sprintf(); */
  printf("binary a1 == %s\n", s);

  printf("*********************** int_binary **********************\n");

  PrintIntBinary(a1);
  AnyTobites((unsigned char *)&a1, sizeof(int));
  dump(&a1, sizeof(a1));

  int i1 = 0x12345678;
  PrintIntBinary(i1); //将int以二进制格式打印
  AnyTobites((unsigned char *)&i1, sizeof(int)); //将int以二进制格式打印
  dump(&i1, sizeof(i1));                         //将int以16进制格式打印
  printf(
      "*********************** unsigned char_binary **********************\n");

  unsigned char b = 12;
  PrintUCHARBinary(b); //将unsigned char以二进制格式打印
  AnyTobites((unsigned char *)&b,
             sizeof(unsigned char)); //将unsigned char以二进制格式打印
  dump(&b, sizeof(b));               //将unsigned char以16进制格式打印

  char c = 9;
  PrintUCHARBinary(c);
  AnyTobites((unsigned char *)&c, sizeof(char));
  dump(&c, sizeof(c));
  printf("*********************** float_binary **********************\n");

  float f1 = 0.75;
  PrintFloatBinary(f1); //将float以二进制格式打印
  AnyTobites((unsigned char *)&f1, sizeof(float)); //将float以二进制格式打印
  dump(&f1, sizeof(f1)); //将float以16进制格式打印

  printf("*********************** double_binary **********************\n");

  double d1 = 0.75;
  // printf("%d\n",sizeof(d1));
  PrintDoubleBinary(d1); //将double以二进制格式打印
  AnyTobites((unsigned char *)&d1, sizeof(double)); //将double以二进制格式打印
  dump(&d1, sizeof(d1)); //将double以16进制格式打印

  printf("*********************** big little judge **********************\n");

  checkBiglittle();
  checkBiglittle1();
  checkBiglittle2();
  checkBiglittle3();

  printf("*********************** 0xFF int   print **********************\n");
  i1 = 0x1234;
  printf("%d\n", i1);
  printf("%X\n", *(int *)&i1);

  PrintFloatBinary1(0.75);

  printf("*********************** 0xFF float print **********************\n");

  f1 = 0.75;
  printf("%f\n", f1);
  printf("%X\n", *(int *)&f1);

  printf("*********************** 0xFF double print **********************\n");
  double d = 0.751;
  printf("%lf\n", d);
  printf("%X\n", *(int *)&d);

  printf("%d\n", 'a');

  printf("*********************** \"int (32bit)\" little to big endian method "
         "1 **********************\n");
  int A = 12;
  PrintIntBinary(A);
  AnyTobites((unsigned char *)&A, sizeof(int));
  dump(&A, sizeof(A));

  A = WAP_u32(A); //大小端互换
  PrintIntBinary(A);
  AnyTobites((unsigned char *)&A, sizeof(int));
  dump(&A, sizeof(A));

  printf("*********************** \"int (32bit)\"  little to big endian method "
         "2 **********************\n");
  A = 12;
  PrintIntBinary(A);
  AnyTobites((unsigned char *)&A, sizeof(int));
  dump(&A, sizeof(A));

  A = _swap32(A); //大小端互换
  PrintIntBinary(A);
  AnyTobites((unsigned char *)&A, sizeof(int));
  dump(&A, sizeof(A));

  printf("*********************** \"unsigned int (32bit)\" little to big "
         "endian method 1 **********************\n");
  unsigned int ui = 12;
  PrintIntBinary(ui);
  AnyTobites((unsigned char *)&ui, sizeof(unsigned int));
  dump(&ui, sizeof(ui));

  ui = WAP_u32(ui); //大小端互换
  PrintIntBinary(ui);
  AnyTobites((unsigned char *)&ui, sizeof(unsigned int));
  dump(&ui, sizeof(ui));

  printf("*********************** \"unsigned int  (32bit)\" little to big "
         "endian method 2 **********************\n");
  ui = 12;
  PrintIntBinary(ui);
  AnyTobites((unsigned char *)&ui, sizeof(int));
  dump(&ui, sizeof(ui));

  ui = WAP_u32(ui); //大小端互换
  PrintIntBinary(ui);
  AnyTobites((unsigned char *)&ui, sizeof(int));
  dump(&ui, sizeof(ui));

  printf("*********************** \"unsigned short  (16 bit)\" little to big "
         "endian  method 1 ***********\n");
  unsigned short us = 12;

  AnyTobites((unsigned char *)&us, sizeof(int));
  dump(&us, sizeof(us));

  us = WAP_u16(us); //大小端互换

  AnyTobites((unsigned char *)&us, sizeof(int));
  dump(&us, sizeof(us));

  printf("*********************** \"unsigned short  (16bit)\" little to big "
         "endian  method 2 ***********\n");
  us = 12;

  AnyTobites((unsigned char *)&us, sizeof(int));
  dump(&us, sizeof(us));

  us = _swap16(us); //大小端互换

  AnyTobites((unsigned char *)&us, sizeof(int));
  dump(&us, sizeof(us));

  printf("*********************** \"float  (32bit)\" little to big endian  "
         "method 1 ***********\n");
  float fl = 12.12;

  AnyTobites((unsigned char *)&fl, sizeof(float));
  dump(&fl, sizeof(fl));

  fl = float_swap_32(fl); //大小端互换

  AnyTobites((unsigned char *)&fl, sizeof(float));
  dump(&fl, sizeof(fl));

  printf("*********************** \"double  (64 bit)\" little to big endian  "
         "method 1 ***********\n");
  d1 = 12.12;

  AnyTobites((unsigned char *)&d1, sizeof(double));
  dump(&d1, sizeof(d1));

  d1 = double_swap_64(d1); //大小端互换

  AnyTobites((unsigned char *)&d1, sizeof(double));
  dump(&d1, sizeof(d1));

  printf("*********************** \"unsigned long long  (64bit)\" little to "
         "big endian  method 1 ***********\n");
  unsigned long long ull = 0x12345678;

  AnyTobites((unsigned char *)&ull, sizeof(unsigned long long));
  dump(&ull, sizeof(unsigned long long));

  ull = _swap64(ull); //大小端互换

  AnyTobites((unsigned char *)&ull, sizeof(unsigned long long));
  dump(&ull, sizeof(unsigned long long));
}
