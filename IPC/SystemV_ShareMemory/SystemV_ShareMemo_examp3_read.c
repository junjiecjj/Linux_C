/*************************************************************************
>> File Name: SystemV_ShareMemo_examp3_read.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 22时09分41秒

>> 此程序的功能是：
************************************************************************/

// shm_read.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

//自定义标识符，最终是以16进制来显示
#define IPC_KEY 0x12345678
int main() {
  // 1.创建共享内存
  int shm_id = shmget(IPC_KEY, 32, IPC_CREAT | 0664);
  if (shm_id < 0) {
    perror("shmget error");
    return -1;
  }
  // 2.建立映射关系
  void *shm_start = shmat(shm_id, NULL, 0);
  if (shm_start == (void *)-1) {
    perror("shmat error");
    return -1;
  }
  // 3.进行内存操作
  while (1) {
    //打印内存中的数据
    printf("[%s]\n", shm_start);
    sleep(1);
  }
  // 4.解除映射关系
  shmdt(shm_start);
  // 5.删除共享内存
  shmctl(shm_id, IPC_RMID, NULL);

  return 0;
}
