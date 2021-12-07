/*************************************************************************
>> File Name: posix_sem6.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月07日 星期二 23时43分53秒

>> 此程序的功能是：
https://blog.csdn.net/fengxinlinux/article/details/76507140
************************************************************************/

#include "tlpi_hdr.h"
#include <pthread.h>
#include <semaphore.h>

static int glob = 0;
static sem_t sem;

static void * /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg) {
  int loops = *((int *)arg);
  int loc, j;

  for (j = 0; j < loops; j++) {
    if (sem_wait(&sem) == -1)
      errExit("sem_wait");

    loc = glob;
    loc++;
    glob = loc;

    if (sem_post(&sem) == -1)
      errExit("sem_post");
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2;
  int loops, s;

  loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

  /* Initialize a semaphore with the value 1 */

  if (sem_init(&sem, 0, 1) == -1)
    errExit("sem_init");

  /* Create two threads that increment 'glob' */

  s = pthread_create(&t1, NULL, threadFunc, &loops);
  if (s != 0)
    errExitEN(s, "pthread_create");
  s = pthread_create(&t2, NULL, threadFunc, &loops);
  if (s != 0)
    errExitEN(s, "pthread_create");

  /* Wait for threads to terminate */

  s = pthread_join(t1, NULL);
  if (s != 0)
    errExitEN(s, "pthread_join");
  s = pthread_join(t2, NULL);
  if (s != 0)
    errExitEN(s, "pthread_join");

  printf("glob = %d\n", glob);
  exit(EXIT_SUCCESS);
}
