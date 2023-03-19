

/***********************************************************
 * 此程序是实现目录和文件相关操作:
 * 打开一个目录，并列出该目录下的所有文件名
 * 创建一个目录，并在相应目录下创建多个规则命名的文件.
 *
**************************************************************/


#include <unistd.h> // Linux系统中
// #include <direct.h> // windows系统中
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


#define PATH_SIZE 255

int GetCwd(void)
{
	char path[PATH_SIZE];
	if(!getcwd(path,PATH_SIZE)){
		printf("Get path fail!\n");
		return 0;
	}
	printf("path = %s\n", path);
    return 0;
}



void  GetFileNames(char *Dirname, int MaxFileNum)
{

}


int main(int argc, char *argv[])
{
    GetCwd();
    return 0;
}