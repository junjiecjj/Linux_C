/*************************************************************************
>> File Name: callcmd.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年09月08日 星期三 23时47分05秒

>> 此程序的功能是：总结C程序中执行shell cmd的popen方法：


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

//检查待启动进程是否已在运行
bool detect_process_exsit(const char *processName) {
  FILE *pReponse;                  //命令返回结果指针
  unsigned int uiResponseData = 0; //命令返回值
  char CommandStr[64];             //存储shell命令字符串
  memset(CommandStr, 0, 64);
  sprintf(CommandStr, "ps -e | grep -c %s", processName);

  pReponse = popen(CommandStr, "r"); //执行shell命令并返回结果

  if (pReponse != NULL) {
    fscanf(pReponse, "%u\n", &uiResponseData);
    printf("uiResponseData = %u\n", uiResponseData);
    if (uiResponseData >= 2) //这里需要注意的是，如果当前进程已经运行，正常时命令行返回为2，但在有的板卡上popen()函数返回为4
    {
      printf("程序 %s 正在运行........!\n", processName);
      pclose(pReponse);
      return true;
    }
  }
  pclose(pReponse);
  return false;
}

int main(int argc, char *argv[]) {
  printf("-------------------------------------例子1-----------------------------------------\n");

  FILE *fp;
  char buffer[80];
  fp = popen("cat /etc/passwd", "r");
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    fputs(buffer, stdout);
  }
  /* printf("%s", buffer); */
  pclose(fp);

  printf("-------------------------------------例子2-----------------------------------------\n");
  printf("%s\n", argv[1]);

  if (true == detect_process_exsit(argv[1])) {
    return 0;
  }

  printf("当前没有在运行,开始运行%%....\n");
  while (1) {
    sleep(3);
    printf("hello,dick .........\n");
  }

  printf("------------------------------------------结束---------------------------------------\n");
  exit(0);
}
