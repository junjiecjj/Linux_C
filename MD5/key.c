#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"

static int keygen = 0;
static int offset = 0;

static int default_keygen = 0x9527;

/*
功能：
 重置keygen，会影响生成的随机数序列
*/
void reset_keygen()
{
	set_keygen(default_keygen);
}

/*
功能：
 向密码机设置keygen，设置后会影响产生的随机密钥序列
参数：
 key：密钥
返回值:
 无
*/
void set_keygen(int key)
{
	keygen = key;
	offset = 0;
}

/*
功能：
 根据同步码和keygen生成随机密钥种子
参数：
    sync：同步码 
 key：密钥
返回值:
 种子
*/
int born_seed(int sync,int key)
{
	return (sync^key);
}

/*
功能：
 向密码机申请一定数量的用于加密数据的密钥，如果不设置新的keygen，那么生成的密码会顺序产生下去，每次申请密钥都会记录上次生成的密钥的偏移，下次在申请的时候，都会从上一位置继续分配密钥
参数：
 sync：同步码，密码机依据此同步产生随机序列的密钥
 key_num：申请的密钥个数
 key：申请的密钥存储的缓存
返回值:
 实际返回密钥个数
*/
int request_key(int sync,int key_num,char key[])
{
	int i,j, r;
	int seed;

	seed = born_seed(sync,keygen);
	
	srand(seed);
	if(key_num > MAX_KEY_REQUEST)
	{
		key_num = MAX_KEY_REQUEST;
	}	

	for(i=0;i<offset;i++)
	{
		rand();
	}
	
	for (j = 0; j < key_num; j++) {
		r =  rand()&0xff;
		key[j] = r;
	}
	offset += key_num;
	return key_num;
}
