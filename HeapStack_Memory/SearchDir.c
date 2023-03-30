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

#include "SearchDir.h"


/**********************************************************************
功能: 获取当前目录
***********************************************************************/
void GetPwd(char *CurrentDir)
{

	if(getcwd(CurrentDir, PATH_SIZE) == NULL){
		printf("Get path fail!\n");
		exit(EXIT_FAILURE);
	}
	// printf("Current Dir is: %s\n", CurrentDir);

}

void useGetPwd(void)
{
	char path[PATH_SIZE];
	GetPwd(path);
	//printf("Current Path is: %s\n", path);
	printf("[file:%s,fun:%s, Line:%d, Current Path:%s] \n", __FILE__, __func__, __LINE__, path);
}


/**************************************************************************
https://blog.csdn.net/lang523493505/article/details/122558431

一、提取文件名
头文件：#include <libgen.h>
**函数：**char *basename(char *path);

注：这个函数不会修改传入的 path 内容。

二、提取路径
头文件：#include <libgen.h>
**函数：**char *dirname(char *path);

注：这个函数会修改传入的 path 内容，如果不像path被改变需要重新申请一个buf传入，如果传入的是宏则会段错误。

**************************************************************************/
void  BaseNameDirName(void)
{
	char *path;
	char s_filepath[] = "/mnt/usr/file.txt";
    printf("FILE_PATH - FILE : %s\n", basename(s_filepath));
    printf("1 -- s_filepath = %s\n\n", s_filepath);

    path = strdup(s_filepath);
    printf("1 -- path = %s\n", path);
    printf("FILE_PATH - PATH : %s\n", dirname(path));
    printf("2 -- path = %s\n", path);  // 从结果也可以看出dirname修改了传入的路径内容。

    free(path);
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
			printf("mkdir %s failed\n\n", dir);
		}
		else
		{
			printf("mkdir %s success\n\n", dir);
		}
	}
	else
	{
		printf("%s already exists !!!\n\n",dir);
		closedir(mydir);
	}
}


/*
判断一个文件是否是以点号开头
*/
bool IsHiddenFile(char *filename)
{
	if(filename[0] == '.'){
		return 1;
	}
	else{
		return 0;
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
			if (!IsHiddenFile(dirInfo->d_name)){
				//filelist[filenum] = dirInfo->d_name;  // 不能这样，后面free会段错误
				strncpy (filelist[filenum], dirInfo->d_name, PATH_SIZE-1);   // ok
				// printf("filelist[%d] ptr:%p \t dirInfo->d_name:%p \n", filenum, filelist[filenum], dirInfo->d_name);
				if(dirInfo->d_type == DT_DIR){
					printf("filename[%d] = %s, 是一个目录\n",filenum,filelist[filenum]);
				}
				else if(dirInfo->d_type == DT_REG){
					printf("filename[%d] = %s, 是一个文件\n",filenum,filelist[filenum]);
				}
				filenum++;
			}
		}
		closedir(dirpt);
	}

	printf("filenum %d\n", filenum);
	// for(int i = 0; i < filenum; ++i){
	// 	// strcat(filelist[i], )
	// 	printf("filename[%d] = %s\n",i,filelist[i]);
	// }

	// 释放内存
    for(int i = 0;  i < MaxFileNum; ++i){
        free(filelist[i]);
        filelist[i] = NULL;
    }

    free(filelist);

    filelist = NULL;
}

/**********************************************************************
功能: 列出指定目录下的所有文件名称,不包括路径
输入:
	Dirname：目录名称
	MaxFileNum：最多多少个文件

输出:
	FileName： 保存文件名称的数组,提前分配好内存
	filenum： 文件个数
***********************************************************************/
int  ListFileInDir(char *Dirname, int MaxFileNum, char **FileName)
{
	if(Dirname == NULL)
	{
		printf("dir_name is null ! \n");
		exit(EXIT_FAILURE);
	}

	DIR *dirpt;
	struct dirent* dirInfo;
	int filenum = 0;

	if((dirpt = opendir(Dirname)) == NULL){
		printf("%s cannot open !!!\n", Dirname);
	}
	else{
		while((dirInfo = readdir(dirpt))!=0){
			if (!IsHiddenFile(dirInfo->d_name)){
				//filelist[filenum] = dirInfo->d_name;  // 不能这样，后面free会段错误
				strncpy (FileName[filenum], dirInfo->d_name, PATH_SIZE-1);   // ok
				// printf("filelist[%d] ptr:%p \t dirInfo->d_name:%p \n", filenum, filelist[filenum], dirInfo->d_name);
				// if(dirInfo->d_type == DT_DIR){
				// 	printf("filename[%d] = %s, 是一个目录\n",filenum, FileName[filenum]);
				// }
				// else if(dirInfo->d_type == DT_REG){
				// 	printf("filename[%d] = %s, 是一个文件\n",filenum, FileName[filenum]);
				// }
				filenum++;
			}
		}
		closedir(dirpt);
	}

	return filenum;

}



void useListFileInDir(void)
{
	int MaxFileNum = 100;
	char Dir[255];

	strncpy(Dir, "./", 10);

	// 分配内存
	char **filelist;
	filelist = (char **)malloc(MaxFileNum * sizeof(char *));
	for(int i = 0; i < MaxFileNum; ++i)
	{
		filelist[i] = (char *)malloc(PATH_SIZE * sizeof(char));
		//printf("filelist[%d] ptr:%p \r\n", i, filelist[i]);
	}

	int filenum = ListFileInDir(Dir, MaxFileNum, filelist);

	printf("filenum is %d\n", filenum);
	// for(int i = 0; i < filenum; ++i){
	// 	// strcat(filelist[i], )
	// 	printf("filename[%d] = %s\n",i,filelist[i]);
	// }

	// 释放内存
    for(int i = 0;  i < MaxFileNum; ++i){
        free(filelist[i]);
        filelist[i] = NULL;
    }
    free(filelist);
    filelist = NULL;

	printf("\n\n");
}


/**********************************************************************
功能: 列出指定目录下的所有文件名称,包括路径
输入:
	Dirname：目录名称
	MaxFileNum：最多多少个文件

输出:
	FileName： 保存文件名称的数组,提前分配好内存
	filenum： 文件个数
***********************************************************************/
int  ListAbsFileInDir(char *Dirname, int MaxFileNum, char **FileName)
{
	if(Dirname == NULL)
	{
		printf("dir_name is null ! \n");
		exit(EXIT_FAILURE);
	}

	char tempfiledir[255];
	DIR *dirpt;
	struct dirent* dirInfo;
	int filenum = 0;

	if((dirpt = opendir(Dirname)) == NULL){
		printf("%s cannot open !!!\n", Dirname);
	}
	else{
		while((dirInfo = readdir(dirpt))!=0){
			if (!IsHiddenFile(dirInfo->d_name)){
				//filelist[filenum] = dirInfo->d_name;  // 不能这样，后面free会段错误
				strncpy (FileName[filenum], dirInfo->d_name, PATH_SIZE-1);   // ok
				// printf("filelist[%d] ptr:%p \t dirInfo->d_name:%p \n", filenum, filelist[filenum], dirInfo->d_name);
				// if(dirInfo->d_type == DT_DIR){
				// 	printf("filename[%d] = %s, 是一个目录\n",filenum, FileName[filenum]);
				// }
				// else if(dirInfo->d_type == DT_REG){
				// 	printf("filename[%d] = %s, 是一个文件\n",filenum, FileName[filenum]);
				// }
				strncpy(tempfiledir, Dirname, 100);
				strncat(tempfiledir, FileName[filenum], 50);
				strncpy(FileName[filenum], tempfiledir, 255);

				filenum++;
			}
		}
		closedir(dirpt);
	}

	return filenum;

}



void useListAbsFileInDir(void)
{
	int MaxFileNum = 100;
	char Dir[255];

	strncpy(Dir, "/home/jack/公共的/ShellScript/", 100);

	// 分配内存
	char **filelist;
	filelist = (char **)malloc(MaxFileNum * sizeof(char *));
	for(int i = 0; i < MaxFileNum; ++i)
	{
		filelist[i] = (char *)malloc(PATH_SIZE * sizeof(char));
		//printf("filelist[%d] ptr:%p \r\n", i, filelist[i]);
	}

	int filenum = ListAbsFileInDir(Dir, MaxFileNum, filelist);

	printf("filenum is %d\n", filenum);
	for(int i = 0; i < filenum; ++i){
		// strcat(filelist[i], )
		printf("filename[%d] = %s\n",i,filelist[i]);
	}

	// 释放内存
    for(int i = 0;  i < MaxFileNum; ++i){
        free(filelist[i]);
        filelist[i] = NULL;
    }
    free(filelist);
    filelist = NULL;

	printf("\n\n");
}







void mainSearchDir(void)
{
    useGetPwd();

	MkrDir("testMkdir");                  // 以当前的exe文件为根目录建立文件夹
	// MkrDir("/home/jack/tmp/testMkdir");  // 绝对路径
	// int2Darray();

	// release2Dchar();

	// ListDir("./", 100);
	useListFileInDir();
	useListAbsFileInDir();

	BaseNameDirName();



}

int main(int argc, char *argv[])
{
	mainSearchDir();
	return 0;
}