


#ifndef FORMATTRANSFER_CJJ
#define FORMATTRANSFER_CJJ


#include "Define.h"
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

//unsigned int �� int ��С��ת��
unsigned int WAP_u32(unsigned int x);


//unsigned short ��С��ת��
unsigned short WAP_u16(unsigned short x);


//DOUBLE��С��ת��
DOUBLE dbMemeryConvert( DOUBLE  pData );


//float��С��ת��
float float_swap_32( float  pData );


//�ַ���תʮ������
void StrToHex(char *pbDest, char *pbSrc, int nLen);


//ʮ������ת�ַ���
void HexToStr(char *pszDest, char *pbSrc, int nlen);


//�ַ���תʮ����,���������
int my_atoi(const char * str);

//�ַ���תʮ����,�����������
void StrtoDec(uint32_t *pbDest, char *pbSrc, int nLen);


//�ַ���תʮ����,�����Ǹ�����
//m^n����
//����ֵ��m^n�η�
u32 NMEA_pow(u8 m, u8 n);

/*�ַ���תʮ����,�����Ǹ�����
�ַ���ת��Ϊ���֣���','��'*'����
buf:���ִ洢��
dx: С����λ�������ظ����ú���
����ֵ:ת�������ֵ
*/
int NMEA_Str2num(u8 *buf, u8 *dx);

//ʮ����ת�ַ���
u16 DecToStr(u8 *pSrc, u16 SrcLen, u8 *pObj);


//�ж�ϵͳ��С��,ʹ���������ж�
BOOL checkBiglittle();

//�ж�ϵͳ��С�ˣ�ʹ��ָ���ж�
BOOL checkBiglittle1();

//�ж�ϵͳ��С�ˣ�ʹ��ָ���ж�
BOOL checkBiglittle2();

//�ж�ϵͳ��С�ˣ�ʹ��ǿ������ת���ж�
BOOL checkBiglittle3();



//���Եĺ���
void Formattransfer_test();




#endif // FORMATTRANSFER_CJJ

