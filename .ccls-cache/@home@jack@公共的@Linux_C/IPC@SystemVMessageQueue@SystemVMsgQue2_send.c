/*************************************************************************
>> File Name: SystemVMsgQue2_send.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月10日 星期五 00时40分51秒

>> 此程序的功能是：
https://blog.csdn.net/sty23122555/article/details/51132158
************************************************************************/

/*send.c*/
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

main() {
  struct msgstru msgs;
  int msg_type;
  char str[256];
  int ret_value;
  int msqid;

  msqid = msgget(MSGKEY, IPC_EXCL); /*检查消息队列是否存在*/
  if (msqid < 0) {
    msqid = msgget(MSGKEY, IPC_CREAT | 0666); /*创建消息队列*/
    if (msqid < 0) {
      printf("failed to create msq | errno=%d [%s]\n", errno, strerror(errno));
      exit(-1);
    }
  }

  while (1) {
    printf("input message type(end:0):");
    scanf("%d", &msg_type);
    if (msg_type == 0)
      break;
    printf("input message to be sent:");
    scanf("%s", str);
    msgs.msgtype = msg_type;
    strcpy(msgs.msgtext, str);
    /* 发送消息队列 */
    ret_value = msgsnd(msqid, &msgs, sizeof(struct msgstru), IPC_NOWAIT);
    if (ret_value < 0) {
      printf("msgsnd() write msg failed,errno=%d[%s]\n", errno,
             strerror(errno));
      exit(-1);
    }
  }
  msgctl(msqid, IPC_RMID, 0); //删除消息队列
}
