

/***********************************************************
 * 此程序是实现目录和文件相关操作:
 * 打开一个目录，并列出该目录下的所有文件名
 * 创建一个目录，并在相应目录下创建多个规则命名的文件.
 *
**************************************************************/


#include <unistd.h> // Linux系统中
// #include <direct.h> // windows系统中
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>


#define MODE777 (S_IRWXU | S_IRWXG | S_IRWXO)
#define MODE664 (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define PATH_SIZE 255


/**********************************************************************
功能: 获取当前目录
***********************************************************************/
void GetPwd(void)
{
	char path[PATH_SIZE];
	if(getcwd(path,PATH_SIZE) == NULL){
		printf("Get path fail!\n");
		exit(EXIT_FAILURE);
	}
	printf("path = %s\n", path);

}

void MkrDir(char *dir)
{
	DIR *mydir;

	if((mydir = opendir(dir)) == NULL){
		if(mkdir(dir, MODE777) != 0)
		{
			printf("mkdir %s failed\n", dir);
		}
		else
		{
			printf("mkdir %s success\n", dir);
		}
	}
	else
	{
		printf("%s already exists !!!\n",dir);
	}
}



void  GetFileNames(char *Dirname, int MaxFileNum)
{

}


int main(int argc, char *argv[])
{
    GetPwd();
	MkrDir("./testMkdir");                  // 以当前的exe文件为根目录建立文件夹
	// MkrDir("/home/jack/tmp/testMkdir");  // 绝对路径

    return 0;
}