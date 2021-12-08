/*************************************************************************
>> File Name: example1_A.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月05日 星期五 15时25分14秒

>> 此程序的功能是：

https://mp.weixin.qq.com/s?__biz=MzAxODI5ODMwOA==&mid=2666558626&idx=2&sn=a27eb5de8281b290e8ec1b96e8ed76a2&chksm=80dcb009b7ab391f8ef3c318afa948a2bfe5bfaa53f975a8b5ed8c64d93f04a70ad402226167&mpshare=1&scene=1&srcid=1027sR3bDAjCRwcpUCbsOohY&sharer_sharetime=1636096586391&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8&exportkey=AVizUaAgLgXeCudX8Ll8QjA%3D&pass_ticket=rUihZeDJ4dAXC7Ft6B4oscfz3eynzUClpSFUFnCHc6SrbH5Fr%2FJA3gemHJWeR7ww&wx_header=0#rd
************************************************************************/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_PATH "/tmp/shm"
#define SHM_SIZE 128

int main(int argc, char *argv[]) {
  int shmid;
  char *addr;
  key_t key = ftok(SHM_PATH, 0x6666);

  shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
  if (shmid < 0) {
    printf("failed to create share memory\n");
    return -1;
  }

  addr = shmat(shmid, NULL, 0);
  if (addr <= 0) {
    printf("failed to map share memory\n");
    return -1;
  }

  sprintf(addr, "%s", "Hello World\n");

  return 0;
}
