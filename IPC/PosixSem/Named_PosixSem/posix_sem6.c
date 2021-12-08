/*************************************************************************
>> File Name: posix_sem6.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 21时45分40秒

>> 此程序的功能是：
下面以一个简单的多线程例子说明如何使用信号量进行线程同步。

在主线程中，创建一个子线程用于处理 resource
共享资源，如果主线程有需求（sem_post），就往其后追加一个 ‘a’ 字符串。
https://www.jianshu.com/p/9f99a6bdc2d0
************************************************************************/

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

sem_t *sem;
static char *resource[30];
void *change_resource(void *res) {
  char *msg = (char *)res;
  fprintf(stdout, "start change resource......\n");
  while (1) {
    sem_wait(sem);
    strcat(resource, "a");
    fprintf(stderr, "change value after: %s\n", msg);
  }
}
int main() {
  int err;
  pthread_t pthread;

  sem = sem_open("/mysem", O_CREAT, S_IRUSR | S_IWUSR, 0);
  do {
    if (pthread_create(&pthread, NULL, change_resource, (void *)resource) !=
        0) {
      printf("pthread_create failed \n");
      err = -1;
      break;
    }
    while (1) {
      int i;
      printf("1 添加 2 阻塞 3退出\n");
      sleep(1);
      scanf("%d", &i);
      if (i == 1) {
        sem_post(sem);
      } else if (i == 2) {
        continue;
      } else if (i == 3) {
        break;
      }
    }
  } while (0);
  if (sem_destroy(sem) != 0) {
    err = -1;
  }
  return err;
}
