/*************************************************************************
>> File Name: mq_notify.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月10日 星期五 23时04分12秒

>> 此程序的功能是：

https://blog.csdn.net/Z_Stand/article/details/102008807

gcc mq_notify.c -o mq_notify -lrt gcc mq_snd.c -o send -lrt
************************************************************************/

#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

mqd_t mq_id;
char buf[8192];
struct sigevent sigev;

static void signal_handler(int signo) {
  ssize_t receive_len;
  //再次进行消息队列和异步通知方式注册的结构体进行绑定
  mq_notify(mq_id, &sigev);
  //尝试从mq_id中获取消息
  receive_len = mq_receive(mq_id, buf, 8192, NULL);
  if (receive_len == -1) {
    printf("mq_receive failed \n");
    _exit(-1);
  }
  printf("read %ld bytes: %s\n", (long)receive_len, buf);
  return;
}

int main() {
  //创建消息队列
  mq_id = mq_open("/notify", O_RDONLY | O_CREAT, 0666, NULL);
  if (mq_id == -1) {
    printf("mq_open failed \n");
    _exit(-1);
  }

  //信号处理逻辑，注册SIGUSR1用户信号，并设置回调函数
  signal(SIGUSR1, signal_handler);
  sigev.sigev_notify = SIGEV_SIGNAL;
  sigev.sigev_signo = SIGUSR1;
  //将消息队列的id和注册的异步通信结构体进行绑定
  mq_notify(mq_id, &sigev);

  int count = 0;
  while (1) {
    printf("while loop %d \n", count++);
    sleep(1);
  }

  mq_close(mq_id);
  return 0;
}
