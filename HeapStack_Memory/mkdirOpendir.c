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

*/

/*
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


/**********************************************************************
功能: 创建目录(只能是单级，不能是多级目录)，如果已经存在，则什么也不做.
***********************************************************************/
void MkrDir(char *dir)
{

	// check the parameter !
	if( NULL == dir )
	{
		printf("dir_name is null ! \n");
		exit(EXIT_FAILURE);
	}

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
		closedir(mydir);
	}
}


/**********************************************************************
功能: 列出指定目录下的所有文件名称
***********************************************************************/
void  ListDir(char *Dirname, int MaxFileNum)
{
	if(Dirname == NULL)
	{
		printf("dir_name is null ! \n");
		exit(EXIT_FAILURE);
	}

	// 分配内存
	char **filelist;
	filelist = (char **)malloc(MaxFileNum * sizeof(char *));
	for(int i = 0; i < MaxFileNum; ++i)
	{
		filelist[i] = (char *)malloc(PATH_SIZE * sizeof(char));
		//printf("filelist[%d] ptr:%p \r\n", i, filelist[i]);
	}

	DIR *dirpt;
	struct dirent* dirInfo;
	int filenum = 0;

	if((dirpt = opendir(Dirname)) == NULL){
		printf("%s is not existing !!!\n",Dirname);
	}
	else{
		while((dirInfo = readdir(dirpt))!=0){
			if (strcmp(dirInfo->d_name, ".") != 0 && strcmp(dirInfo->d_name, "..") != 0){
				filelist[filenum] = dirInfo->d_name;
				filenum++;
			}
		}
	}

	printf("filenum %d\n", filenum);
	for(int i = 0; i < filenum; ++i){
		printf("filename[%d] = %s\n",i,filelist[i]);
	}
	printf("00000000000000\n");
	// 释放内存
    for(int i = 0;  i < MaxFileNum; ++i){
		printf("free idx i = %d\n",i);
        free(filelist[i]);
        filelist[i] = NULL;
    }
	printf("1111111111111\n");
    free(filelist);
	printf("2222222222222\n");
    filelist = NULL;
}

void release2Dchar(void)
{
    int n = 3;
    int lens = 10;

    char**pps8Output = (char **) malloc(n * sizeof(char *));

    ///< malloc
    for (int i = 0; i < n; i++)
    {
        pps8Output[i] = (char *) malloc(lens * sizeof(char));
        printf("pps8Output[%d] ptr:%p \r\n", i, pps8Output[i]);
    }

    ///< free
    for (int i = 0; i < n; i++)
    {
        free(pps8Output[i]);
    }
    free(pps8Output);


	printf("release 2D char array done \n\n\n");
}



void intarray(void)
{
	int m = 3;
	int n = 4;
    int **D;
    //这样分配内存不连续,行内连续，行间不一定连续，
    D = (int **)malloc(m * sizeof(int *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < m; i++)
    {
        D[i] = (int *)malloc(n * sizeof(int)); //每一行一定连续
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = i * n + j;
        }
    }

	printf("release 2D int array\n");
    for(int i=0;  i<m; ++i){
        free(D[i]);
        D[i] = NULL;
    }
    free(D);
    D = NULL;
	printf("release 2D int done \n\n\n");
}

int main(int argc, char *argv[])
{
    GetPwd();
	MkrDir("testMkdir");                  // 以当前的exe文件为根目录建立文件夹
	// MkrDir("/home/jack/tmp/testMkdir");  // 绝对路径
	intarray();

	release2Dchar();

	ListDir("./folder", 100);

    return 0;
}