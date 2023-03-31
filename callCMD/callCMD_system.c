/*************************************************************************
>> File Name: callCMD_system.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年09月12日 星期日 11时31分44秒

>> 此程序的功能是：利用system执行shell cmd
************************************************************************/

#include "color.h"
#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#include <errno.h>
#include <dirent.h>

#include <libgen.h>


#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>


#define MODE777 (S_IRWXU | S_IRWXG | S_IRWXO)
#define MODE664 (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH )
#define PATH_SIZE 255



/******************************************************************************************************************
在Linux下，access函数的声明在<unistd.h>文件中，声明如下：
int access(const char *pathname, int mode);

access函数用来判断指定的文件或目录是否存在(F_OK)，已存在的文件或目录是否有可读(R_OK)、可写(W_OK)、可执行(X_OK)权限。F_OK、R_OK、W_OK、X_OK这四种方式通过access函数中的第二个参数mode指定。如果指定的方式有效，则此函数返回0，否则返回-1。

用来判断指定的文件或目录是否仅存在(00)，已存在的文件或目录是否有仅读(04)、仅写(02)、既可读又可写(06)权限。这四种方式通过_access函数中的第二个参数mode指定，如果mode传入的值不是0或2或4或6，调用此函数则会crash。如果指定的方式有效，则此函数返回0，否则返回-1。
*******************************************************************************************************************/

void mkdirs(char *muldir){
    int  len;
    char str[512];
    strncpy(str, muldir, 512);
    len = strlen(str);
    printf("len = %d\n", len);
    for(int i = 0; i<len; i++ )
    {
      if( str[i] == '/' )
        {
            str[i] = '\0';

            if( access(str, R_OK)!=0 )
            {
                mkdir(str, 0777);
            }
            str[i]='/';
        }
    }
    printf("str = %s\n", str);
    if( len>0 && access(str,R_OK)!=0 )
    {
        mkdir( str, 0777 );
    }
    return;
}

/**********************************************************************
功能: 创建目录(可以是多级目录), 果已经存在，则什么也不做.
输入:
    testDira/test1/test2
    ~/testDira/test1/test2
    ./testDira/test1/test2
    ../../testDira/test1/test2
***********************************************************************/
void mkMultiDirs(char *muldir){
	// check the parameter !
	if( NULL == muldir )
	{
		printf("dir_name is null ! \n");
		exit(EXIT_FAILURE);
	}

    int  len;
    char str[512];
    strncpy(str, muldir, 512);
    len = strlen(str);


	DIR *mydir;
	if((mydir = opendir(muldir)) == NULL){
		for(int i = 0; i < len; i++ )
		{
			if( str[i] == '/' )
			{
				str[i] = '\0';
        // printf("i = %d, str = %s\n", i, str);
				if( access(str, R_OK)!=0 )
				{
					mkdir(str, 0777);
				}
				str[i]='/';
			}
		}
		printf("str = %s\n", str);
		if( len>0 && access(str,R_OK)!=0 )
		{
			mkdir( str, 0777 );
		}
	}
	else
	{
		printf("%s already exists !!!\n\n",muldir);
		closedir(mydir);
	}
    return;
}

/**********************************************************************
功能: 通过 System调用shell命令 创建目录(可以是多级目录)，如果已经存在，则什么也不做.
输入:
    testDira/test1/test2
    ~/testDira/test1/test2
    ./testDira/test1/test2
    ../../testDira/test1/test2
***********************************************************************/
void mkMultiDirsBySystem(char *muldir){
	// check the parameter !
	if( NULL == muldir )
	{
		printf("dir_name is null ! \n");
		exit(EXIT_FAILURE);
	}

  printf("strlen multidir = %lu\n", strlen(muldir));

  char cmd[1000];
  char filesavepath[500];
  printf("strlen(cmd) = %lu, (filesavepath) = %lu\n", strlen(cmd), strlen(filesavepath));

	DIR *mydir;

  if((mydir = opendir(muldir)) == NULL){

		strncpy(filesavepath, muldir, sizeof(filesavepath));
    printf("filesavepath = %s\n", filesavepath);
		sprintf(cmd,"mkdir -p %s",filesavepath); // 组成命令
    printf("cmd = %s\n", cmd);
		system(cmd); // 建路径

	}
  else{
		printf("%s already exists !!!\n\n",muldir);
		closedir(mydir);
  }
  return;
}



int main(int argc, char *argv[]) {

  printf("使用system调研shell cmd的演示示例......\n");
  printf("-------------------------------------例子1 ls 命令 -----------------------------------------\n");

  system("ls -lh");

  printf("------------------------------------例子2 ls 命令 ----------------------------------------\n");
  system("ls -al /etc/passwd");

  printf("------------------------------------例子2 mkdir 命令 ----------------------------------------\n");
  double SNR = 2.50;

  // system("mkdir -p ./testDir/test1/test2");

  mkMultiDirs("../../testDira/test1/test2");

  printf("---------------------------------------------结束----------------------------------------\n");

  return 0;
}
