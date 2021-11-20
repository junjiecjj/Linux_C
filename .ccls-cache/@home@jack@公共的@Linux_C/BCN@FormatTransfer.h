


#ifndef FORMATTRANSFER_CJJ
#define FORMATTRANSFER_CJJ


#include "Define.h"
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

//unsigned int 或 int 大小端转换
unsigned int WAP_u32(unsigned int x);


//unsigned short 大小端转换
unsigned short WAP_u16(unsigned short x);


//DOUBLE大小端转换
DOUBLE dbMemeryConvert( DOUBLE  pData );


//float大小端转换
float float_swap_32( float  pData );


//字符串转十六进制
void StrToHex(char *pbDest, char *pbSrc, int nLen);


//十六进制转字符串
void HexToStr(char *pszDest, char *pbSrc, int nlen);


//字符串转十进制,如果带负号
int my_atoi(const char * str);

//字符串转十进制,如果不带负号
void StrtoDec(uint32_t *pbDest, char *pbSrc, int nLen);


//字符串转十进制,可以是浮点数
//m^n函数
//返回值：m^n次方
u32 NMEA_pow(u8 m, u8 n);

/*字符串转十进制,可以是浮点数
字符串转换为数字，以','或'*'结束
buf:数字存储区
dx: 小数点位数，返回给调用函数
返回值:转换后的数值
*/
int NMEA_Str2num(u8 *buf, u8 *dx);

//十进制转字符串
u16 DecToStr(u8 *pSrc, u16 SrcLen, u8 *pObj);


//判断系统大小端,使用联合体判断
BOOL checkBiglittle();

//判断系统大小端，使用指针判断
BOOL checkBiglittle1();

//判断系统大小端，使用指针判断
BOOL checkBiglittle2();

//判断系统大小端，使用强制类型转换判断
BOOL checkBiglittle3();



//测试的函数
void Formattransfer_test();




#endif // FORMATTRANSFER_CJJ

