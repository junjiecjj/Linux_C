/*************************************************************************
>> File Name: mq_snd.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月10日 星期五 23时04分48秒

>> 此程序的功能是：
************************************************************************/

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  mqd_t mq_id;
  //打开创建好的消息队列
  mq_id = mq_open("/notify", O_WRONLY | O_CREAT, 0666, NULL);
  if (mq_id == -1) {
    printf("mq_open failed\n");
    _exit(-1);
  }

  //持续向消息队列中每隔两秒写入数据
  while (1) {
    if (mq_send(mq_id, "hello world", sizeof("hello world"), 1) == -1) {
      printf("mq_send failed \n");
      _exit(-1);
    }
    printf("msg send success -----\n");
    sleep(2);
  }
  return 0;
}
