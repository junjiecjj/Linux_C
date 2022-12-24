/*************************************************************************
>> File Name: main.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月27日 星期六 22时49分07秒

>> 此程序的功能是：
************************************************************************/

/*
 *一口Linux
 *2021.6.21
 *version: 1.0.0
 */
#include "crc.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define LENGTH 8
const uint8_t data[3][LENGTH] = {
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
    {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f}};

typedef struct {
  CRC_Type crcType;
  uint32_t result[3];
} CRC_Test;

CRC_Test crc4_ITU = {{4, 0x03, 0x00, true, true, 0x00}, {0x0f, 0x0a, 0x0e}};
CRC_Test crc5_EPC = {{5, 0x09, 0x09, false, false, 0x00}, {0x00, 0x0c, 0x17}};
CRC_Test crc5_ITU = {{5, 0x15, 0x00, true, true, 0x00}, {0x16, 0x0a, 0x17}};
CRC_Test crc5_USB = {{5, 0x05, 0x1f, true, true, 0x1f}, {0x10, 0x09, 0x17}};
CRC_Test crc6_ITU = {{6, 0x03, 0x00, true, true, 0x00}, {0x1d, 0x30, 0x00}};
CRC_Test crc7_MMC = {{7, 0x09, 0x00, false, false, 0x00}, {0x57, 0x30, 0x5b}};
CRC_Test crc8 = {{8, 0x07, 0x00, false, false, 0x00}, {0x3e, 0xe1, 0x36}};
CRC_Test crc8_ITU = {{8, 0x07, 0x00, false, false, 0x55}, {0x6b, 0xb4, 0x63}};
CRC_Test crc8_ROHC = {{8, 0x07, 0xff, true, true, 0x00}, {0x6b, 0x78, 0x93}};
CRC_Test crc8_MAXIM = {{8, 0x31, 0x00, true, true, 0x00}, {0x83, 0x60, 0xa9}};
CRC_Test crc16_IBM = {{16, 0x8005, 0x0000, true, true, 0x0000},
                      {0xc4f0, 0x2337, 0xa776}};
CRC_Test crc16_MAXIM = {{16, 0x8005, 0x0000, true, true, 0xffff},
                        {0x3b0f, 0xdcc8, 0x5889}};
CRC_Test crc16_USB = {{16, 0x8005, 0xffff, true, true, 0xffff},
                      {0x304f, 0xd788, 0x53c9}};
CRC_Test crc16_MODBUS = {{16, 0x8005, 0xffff, true, true, 0x0000},
                         {0xcfb0, 0x2877, 0xac36}};
CRC_Test crc16_CCITT = {{16, 0x1021, 0x0000, true, true, 0x0000},
                        {0xeea7, 0xfe7c, 0x7919}};
CRC_Test crc16_CCITT_FALSE = {{16, 0x1021, 0xffff, false, false, 0x0000},
                              {0x4792, 0x13a7, 0xb546}};
CRC_Test crc16_X25 = {{16, 0x1021, 0xffff, true, true, 0xffff},
                      {0x6dd5, 0x7d0f, 0xfa6a}};
CRC_Test crc16_XMODEM = {{16, 0x1021, 0x0000, false, false, 0x0000},
                         {0x76ac, 0x2299, 0x8478}};
CRC_Test crc16_DNP = {{16, 0x3D65, 0x0000, true, true, 0xffff},
                      {0x7bda, 0x0535, 0x08c4}};
CRC_Test crc32 = {{32, 0x04c11db7, 0xffffffff, true, true, 0xffffffff},
                  {0x3fca88c5, 0xe0631a53, 0xa4051a26}};
CRC_Test crc32_MPEG2 = {{32, 0x4c11db7, 0xffffffff, false, false, 0x00000000},
                        {0x14dbbdd8, 0x6509b4b6, 0xcb09d294}};

void CrcTest(CRC_Test crcTest) {
  uint32_t i;
  for (i = 0; i < 3; i++) {
    printf("%08x\t%08x\r\n", CrcCheck(crcTest.crcType, data[i], LENGTH),
           crcTest.result[i]);
  }
  printf("\r\n");
}

int main(void) {
  CrcTest(crc4_ITU);
  CrcTest(crc5_EPC);
  CrcTest(crc5_ITU);
  CrcTest(crc5_USB);
  CrcTest(crc6_ITU);
  CrcTest(crc7_MMC);
  CrcTest(crc8);
  CrcTest(crc8_ITU);
  CrcTest(crc8_ROHC);
  CrcTest(crc8_MAXIM);
  CrcTest(crc16_IBM);
  CrcTest(crc16_MAXIM);
  CrcTest(crc16_USB);
  CrcTest(crc16_MODBUS);
  CrcTest(crc16_CCITT);
  CrcTest(crc16_CCITT_FALSE);
  CrcTest(crc16_X25);
  CrcTest(crc16_XMODEM);
  CrcTest(crc16_DNP);
  CrcTest(crc32);
  CrcTest(crc32_MPEG2);

  return 0;
}
