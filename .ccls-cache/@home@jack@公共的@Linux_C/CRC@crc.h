/*************************************************************************
>> File Name: crc.h
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月27日 星期六 22时48分22秒

>> 此程序的功能是：
************************************************************************/

/*
 *一口Linux
 *2021.6.21
 *version: 1.0.0
*/
#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
 uint8_t width;
 uint32_t poly;
 uint32_t init;
 bool refIn;
 bool refOut;
 uint32_t xorOut;
}CRC_Type;

uint32_t CrcCheck(CRC_Type crcType, const uint8_t *buffer, uint32_t length);

#endif
