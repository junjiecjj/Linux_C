/*************************************************************************
>> File Name: Define.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年07月12日 星期一 09时56分09秒

>> 此程序的功能是：
************************************************************************/

#include "Define.h"
#include <stdio.h>
#include <stdlib.h>

void Color_test() {
  int a = 12;
  float b = 12.12;

  printf("one "
         "two \n");
  printf(BLACK_BLUE
         " *你要改变颜色的内容，黑底和红色字* a = %d, b = %f \n" COLOR_RESET,
         a, b);

  printf(BLACK_BLACK
         " 黑底黑字 " COLOR_RESET BLACK_RED " 黑底红字 " COLOR_RESET BLACK_GREEN
         " 黑底绿字 " COLOR_RESET "a=%d, b=%f" BLACK_YELLOW
         " 黑底黄字 " COLOR_RESET BLACK_BLUE
         " 黑底蓝字 " COLOR_RESET BLACK_PURTPLE
         " 黑底紫字 " COLOR_RESET BLACK_DEEPGREEN
         " 黑底深绿字 " COLOR_RESET BLACK_WHITE " 黑底白字 " COLOR_RESET "\n",
         a, b);

  printf(RED_BLACK
         " 红底黑字 " COLOR_RESET RED_RED " 红底红字 " COLOR_RESET RED_GREEN
         " 红底绿字 " COLOR_RESET RED_YELLOW " 红底黄字 " COLOR_RESET RED_BLUE
         " 红底蓝字 " COLOR_RESET RED_PURTPLE
         " 红底紫字 " COLOR_RESET RED_DEEPGREEN
         " 红底深绿字 " COLOR_RESET RED_WHITE " 红底白字 " COLOR_RESET "\n");

  printf(GREEN_BLACK
         " 绿底黑字 " COLOR_RESET GREEN_RED " 绿底红字 " COLOR_RESET GREEN_GREEN
         " 绿底绿字 " COLOR_RESET GREEN_YELLOW
         " 绿底黄字 " COLOR_RESET GREEN_BLUE
         " 绿底蓝字 " COLOR_RESET GREEN_PURTPLE
         " 绿底紫字 " COLOR_RESET GREEN_DEEPGREEN
         " 绿底深绿字 " COLOR_RESET GREEN_WHITE " 绿底白字 " COLOR_RESET "\n");

  printf(YELLOW_BLACK " 黄底黑字 " COLOR_RESET YELLOW_RED
                      " 黄底红字 " COLOR_RESET YELLOW_GREEN
                      " 黄底绿字 " COLOR_RESET YELLOW_YELLOW
                      " 黄底黄字 " COLOR_RESET YELLOW_BLUE
                      " 黄底蓝字 " COLOR_RESET YELLOW_PURTPLE
                      " 黄底紫字 " COLOR_RESET YELLOW_DEEPGREEN
                      " 黄底深绿字 " COLOR_RESET YELLOW_WHITE
                      " 黄底白字 " COLOR_RESET "\n");

  printf(BLUE_BLACK
         " 蓝底黑字 " COLOR_RESET BLUE_RED " 蓝底红字 " COLOR_RESET BLUE_GREEN
         " 蓝底绿字 " COLOR_RESET BLUE_YELLOW " 蓝底黄字 " COLOR_RESET BLUE_BLUE
         " 蓝底蓝字 " COLOR_RESET BLUE_PURTPLE
         " 蓝底紫字 " COLOR_RESET BLUE_DEEPGREEN
         " 蓝底深绿字 " COLOR_RESET BLUE_WHITE " 蓝底白字 " COLOR_RESET "\n");

  printf(PURPLE_BLACK " 紫底黑字 " COLOR_RESET PURPLE_RED
                      " 紫底红字 " COLOR_RESET PURPLE_GREEN
                      " 紫底绿字 " COLOR_RESET PURPLE_YELLOW
                      " 紫底黄字 " COLOR_RESET PURPLE_BLUE
                      " 紫底蓝字 " COLOR_RESET PURPLE_PURTPLE
                      " 紫底紫字 " COLOR_RESET PURPLE_DEEPGREEN
                      " 紫底深绿字 " COLOR_RESET PURPLE_WHITE
                      " 紫底白字 " COLOR_RESET "\n");

  printf(DEEPGREEN_BLACK " 深绿底黑字 " COLOR_RESET DEEPGREEN_RED
                         " 深绿底红字 " COLOR_RESET DEEPGREEN_GREEN
                         " 深绿底绿字 " COLOR_RESET DEEPGREEN_YELLOW
                         " 深绿底黄字 " COLOR_RESET DEEPGREEN_BLUE
                         " 深绿底蓝字 " COLOR_RESET DEEPGREEN_PURTPLE
                         " 深绿底紫字 " COLOR_RESET DEEPGREEN_DEEPGREEN
                         " 深绿底深绿字 " COLOR_RESET DEEPGREEN_WHITE
                         " 深绿底白字 " COLOR_RESET "\n");

  printf(WHITE_BLACK
         " 白底黑字 " COLOR_RESET WHITE_RED " 白底红字 " COLOR_RESET WHITE_GREEN
         " 白底绿字 " COLOR_RESET WHITE_YELLOW
         " 白底黄字 " COLOR_RESET WHITE_BLUE
         " 白底蓝字 " COLOR_RESET WHITE_PURTPLE
         " 白底紫字 " COLOR_RESET WHITE_DEEPGREEN
         " 白底深绿字 " COLOR_RESET WHITE_WHITE " 白底白字 " COLOR_RESET "\n");

  printf("\033[40;31m *你要改变颜色的内容，黑底和红色字* "
         "\033[0m \n");
  printf("\033[47;32m *你要改变颜色的内容，白底和绿色字* "
         "\033[0m \n");
  printf("\033[43;35m *你要改变颜色的内容，黄底和紫色字* "
         "\033[0m \n");
}
