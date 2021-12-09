/*************************************************************************
>> File Name: SystemVMsgQue2_recv.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月10日 星期五 00时41分08秒

>> 此程序的功能是：
************************************************************************/

/*receive.c */
#include <errno.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSGKEY 1024

struct msgstru {
  long msgtype;
  char msgtext[2048];
};

/*子进程，监听消息队列*/
void childproc() {
  struct msgstru msgs;
  int msgid, ret_value;
  char str[512];

  while (1) {
    msgid = msgget(MSGKEY, IPC_EXCL); /*检查消息队列是否存在 */
    if (msgid < 0) {
      printf("msq not existed! errno=%d [%s]\n", errno, strerror(errno));
      sleep(2);
      continue;
    }
    /*接收消息队列*/
    ret_value = msgrcv(msgid, &msgs, sizeof(struct msgstru), 0, 0);
    printf("text=[%s] pid=[%d]\n", msgs.msgtext, getpid());
  }
  return;
}

void main() {
  int i, cpid;

  /* create 5 child process */
  for (i = 0; i < 5; i++) {
    cpid = fork();
    if (cpid < 0)
      printf("fork failed\n");
    else if (cpid == 0) /*child process*/
      childproc();
  }
}
