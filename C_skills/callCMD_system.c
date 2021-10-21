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

int main(int argc, char *argv[]) {

  printf("使用system调研shell cmd的演示示例......\n");
  printf(DEEPGREEN_YELLOW "-------------------------------------例子1----------"
                          "-------------------------------\n"
                          "\033[0m" COLOR_RESET);

  system("ls -lh");

  printf(DEEPGREEN_BLUE "------------------------------------例子2-----------"
                        "-----------------------------\n"
                        "\033[0m" COLOR_RESET);
  system("ls -al /etc/passwd");

  printf("---------------------------------------------结束--------------------"
         "--------------------\n");
}
