

/*
	int mkdir(const char *pathname, mode_t mode);
	mode方式：
	S_IRWXU 	00700权限，代表该文件所有者拥有读，写和执行操作的权限
	S_IRUSR(S_IREAD) 	00400权限，代表该文件所有者拥有可读的权限
	S_IWUSR(S_IWRITE) 	00200权限，代表该文件所有者拥有可写的权限
	S_IXUSR(S_IEXEC) 	00100权限，代表该文件所有者拥有执行的权限


	S_IRWXG 	00070权限，代表该文件用户组拥有读，写和执行操作的权限
	S_IRGRP 	00040权限，代表该文件用户组拥有可读的权限
	S_IWGRP 	00020权限，代表该文件用户组拥有可写的权限
	S_IXGRP 	00010权限，代表该文件用户组拥有执行的权限

	S_IRWXO 	00007权限，代表其他用户拥有读，写和执行操作的权限
	S_IROTH 	00004权限，代表其他用户拥有可读的权限
	S_IWOTH 	00002权限，代表其他用户拥有可写的权限
	S_IXOTH 	00001权限，代表其他用户拥有执行的权限


	参数 mode 有下列数种组合：
	S_ISUID 04000 文件的 (set user-id on execution)位
	S_ISGID 02000 文件的 (set group-id on execution)位
	S_ISVTX 01000 文件的sticky 位

	S_IRUSR (S_IREAD) 00400 文件所有者具可读取权限
	S_IWUSR (S_IWRITE)00200 文件所有者具可写入权限
	S_IXUSR (S_IEXEC) 00100 文件所有者具可执行权限

	S_IRGRP 00040 用户组具可读取权限
	S_IWGRP 00020 用户组具可写入权限
	S_IXGRP 00010 用户组具可执行权限

	S_IROTH 00004 其他用户具可读取权限
	S_IWOTH 00002 其他用户具可写入权限
	S_IXOTH 00001 其他用户具可执行权限

*/


/***********************************************************
 * 此程序是实现目录和文件相关操作:
 * 打开一个目录，并列出该目录下的所有文件名
 * 创建一个目录，并在相应目录下创建多个规则命名的文件.
 *
**************************************************************/
#ifndef _SEARCHDIR_CJJ
#define _SEARCHDIR_CJJ


#include <unistd.h> // Linux系统中
// #include <direct.h> // windows系统中
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <libgen.h>



#define MODE777 (S_IRWXU | S_IRWXG | S_IRWXO)
#define MODE664 (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH )
#define PATH_SIZE 255


/**********************************************************************
功能: 获取当前目录
***********************************************************************/
void GetPwd(char *CurrentDir);
void useGetPwd(void);

/*
https://blog.csdn.net/lang523493505/article/details/122558431

一、提取文件名
头文件：#include <libgen.h>
**函数：**char *basename(char *path);

注：这个函数不会修改传入的 path 内容。

二、提取路径
头文件：#include <libgen.h>
**函数：**char *dirname(char *path);

注：这个函数会修改传入的 path 内容，如果不像path被改变需要重新申请一个buf传入，如果传入的是宏则会段错误。

*/
void  BaseNameDirName(void);



/**********************************************************************
函数： void mkMultiDirs(char *muldir);
功能: 创建目录(可以是多级目录), 果已经存在，则什么也不做.
输入:
    testDira/test1/test2
    ~/testDira/test1/test2
    ./testDira/test1/test2
    ../../testDira/test1/test2
***********************************************************************/
void mkMultiDirs(char *muldir);



/**********************************************************************
函数：void mkMultiDirsBySystem(char *muldir);
功能: 通过 System调用shell命令 创建目录(可以是多级目录)，如果已经存在，则什么也不做.
输入:
    testDira/test1/test2
    ~/testDira/test1/test2
    ./testDira/test1/test2
    ../../testDira/test1/test2
***********************************************************************/
void mkMultiDirsBySystem(char *muldir);



/**********************************************************************
功能: 创建目录(只能是单级，不能是多级目录)，如果已经存在，则什么也不做.
***********************************************************************/
void MkrDir(char *dir);


bool IsHiddenFile(char *file);

/**********************************************************************
功能: 列出指定目录下的所有文件名称
***********************************************************************/
int  ListFileInDir(char *Dirname, int MaxFileNum, char **FileName);
void useListFileInDir(void);




/**********************************************************************
int  ListAbsFileInDir(char *Dirname, int maxfilenum, char **FileName)
功能: 列出指定目录下的所有文件名称,包括路径
输入:
	Dirname：目录名称
	MaxFileNum：最多多少个文件

输出:
	FileName： 保存文件名称的数组,提前分配好内存
	filenum： 文件个数
***********************************************************************/
int  ListAbsFileInDir(char *Dirname, int maxfilenum, char **FileName);
void useListAbsFileInDir(void);



/**********************************************************************
void GetDirnameBasename(char *filename, char *dirname, char *basename);
功能:  分离目录和文件名
输入:
	filename： 例如： /home/jack/公共的/ShellScript/USB.sh

输出:
	Dirname： /home/jack/公共的/ShellScript/
	Basename： USB.sh

一、提取文件名
头文件：#include <libgen.h>
**函数：**char *basename(char *path);
注：这个函数不会修改传入的 path 内容。

二、提取路径
头文件：#include <libgen.h>
**函数：**char *dirname(char *path);
注：这个函数会修改传入的 path 内容，如果不像path被改变需要重新申请一个buf传入，如果传入的是宏则会段错误。
***********************************************************************/
void GetDirnameBasename(char *filename, char *dirname, char *basename);
void useGetDirnameBasename(void);

/**********************************************************************
int GetFilenameExtensionname(char *filename, char *basename, char *extname);

功能:  分离文件名和后缀
输入:
	filename： 例如：  USB.sh

输出:
	Dirname： USB，  jpg文件名
	Basename： sh，   后缀
***********************************************************************/
int GetFilenameExtensionname(char *filename, char *basename, char *extname);
void useGetFilenameExtensionname(void);


void mainSearchDir(void);


#endif  //_VLA_CJJ