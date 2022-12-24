/*************************************************************************
>> File Name: posix_sem6_1.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月07日 星期二 23时45分24秒

>> 此程序的功能是：
https://blog.csdn.net/fuyuande/article/details/107123193
************************************************************************/

// 生产者
#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> /* For mode constants */
#include <unistd.h>

#define SEM_NAME "/sem0"

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: ./sem_post timeval nums\n");
    return -1;
  }

  int ts = atoi(argv[1]);
  int total = atoi(argv[2]);
  if (total < 1 || ts < 1) {
    printf("invalid param\n");
    return -1;
  }

  sem_t *sem_id;
  // 创建信号量并初始化值为0
  sem_id = sem_open(SEM_NAME, O_CREAT, O_RDWR, 0);
  if (sem_id == SEM_FAILED) {
    perror("sem_open error");
    return -1;
  }

  int curr = 0;
  while (curr < total) {
    // 生成信号量，即加1
    while (sem_post(sem_id)) {
      perror("sem_post error, try later");
      sleep(1);
    }
    printf("producing succ\n");
    sleep(ts);
    ++curr;
  }
  printf("work done\n");

  // 关闭信号量
  sem_close(sem_id);
  return 0;
}

/*
  default:
        gcc -o sem_post sem_post.c -pthread
        gcc -o sem_wait sem_wait.c -pthread
clean:
        rm -rf sem_wait sem_post
 * */
