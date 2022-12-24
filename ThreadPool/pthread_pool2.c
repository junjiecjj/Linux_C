/*************************************************************************
>> File Name: pthread_pool2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年11月14日 星期日 00时35分07秒

>> 此程序的功能是：
https://mp.weixin.qq.com/s?__biz=MzUxMjEyNDgyNw==&mid=2247497507&idx=1&sn=1d27c2c5d8e049cd97c215041bfe2d1b&chksm=f96b85d7ce1c0cc11755bfd0c421f493bebb0d53558eb2beae6af832d378492c13a58c95d16e&mpshare=1&scene=24&srcid=111006OdtwQ6L2OmLdM0kGZ4&sharer_sharetime=1636516576363&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8&exportkey=AVUKXOD%2FZ6CIfV%2BS6iEMWso%3D&pass_ticket=NanSdx21vnnpMjiN9K7CuB1fPYDqSmxOvvFjXalQNUl3fKpXqkCJ6F8R235X1%2Frb&wx_header=0#rd



************************************************************************/

#include <complex.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

//链表插入
#define LIST_INSERT(item, list)                                                \
  do {                                                                         \
    item->prev = NULL;                                                         \
    item->next = list;                                                         \
    if (list != NULL)                                                          \
      list->prev = item;                                                       \
    list = item;                                                               \
  } while (0)

//删除
#define LIST_REMOVE(item, list)                                                \
  do {                                                                         \
    if (item->prev != NULL)                                                    \
      item->prev->next = item->next;                                           \
    if (item->next != NULL)                                                    \
      item->next->prev = item->prev;                                           \
    if (list == item)                                                          \
      list = item->next;                                                       \
    item->prev = item->next = NULL;                                            \
  } while (0)
//任务队列

struct nTask {
  void (*task_funt)(struct nTask *task);
  void *uset_data;

  struct nTask *prev;
  struct nTask *next;
};

//执行队列
struct nWorker {
  pthread_t threadid;
  int terminate;

  struct nManager *manager;

  struct nWorker *prev;
  struct nWorker *next;
};

//管理组件
typedef struct nManager {
  struct nTask *tasks;
  struct nWoker *workers;

  pthread_mutex_t mutex;
  pthread_cond_t cond;

} ThreadPool;
//线程回调函数
void *nThreadPoolCallback(void *arg) {
  struct nWorker *worker = (struct nWorker *)arg;

  while (1) {
    //判断是否有任务
    pthread_mutex_lock(&worker->manager->mutex);
    while (worker->manager->tasks == NULL) {
      if (worker->terminate)
        break;
      pthread_cond_wait(
          &worker->manager->cond,
          &worker->manager->mutex); //如果没有任务，一直等待任务的到来
    }
    if (worker->terminate) {
      pthread_mutex_unlock(&worker->manager->mutex);
      break;
    }
    struct nTask *task = worker->manager->tasks;
    LIST_REMOVE(task, worker->manager->tasks);
    pthread_mutex_unlock(&worker->manager->mutex);
    task->task_funt(task);
  }

  free(worker);
}

//创建线程池
int nThreadPoolCreate(ThreadPool *pool, int numWorkers) {
  if (pool == NULL)
    return -1;
  if (numWorkers < 1)
    numWorkers = 1;
  memset(&pool, 0, sizeof(ThreadPool));

  //开始初始化
  pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;

  memcpy(&pool->cond, &blank_cond, sizeof(pthread_cond_t));

  pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
  memcpy(&pool->mutex, &blank_mutex, sizeof(pthread_mutex_t));

  int i = 0; //开线程的个数,也就是执行任务的个数

  for (i = 0; i < numWorkers; i++) {
    struct nWorker *worker = (struct nWorker *)malloc(sizeof(struct nWorker));
    if (worker == NULL) {
      perror("malloc");
      return -2;
    }
    memset(worker, 0, sizeof(struct nWorker));
    worker->manager = pool;

    //创建线程
    int ret =
        pthread_create(&worker->threadid, NULL, nThreadPoolCallback, worker);

    if (ret) {
      perror("pthread_create");
      free(worker);
      return -3;
    }
    LIST_INSERT(worker, pool->workers);
  }
}

//线程池销毁

int nThreadPoolDestory(ThreadPool *pool, int nWorker) {
  struct nWorker *worker = NULL;
  for (worker = pool->workers; worker != NULL; worker = worker->next) {
    worker->terminate;
  }
  pthread_mutex_lock(&pool->mutex);
  pthread_cond_broadcast(&pool->cond); //做一个广播通知
  pthread_mutex_unlock(&pool->mutex);

  pool->workers = NULL;
  pool->tasks = NULL;
}

//往线程池里面添加任务

int nThreadPoolPushTask(ThreadPool *pool, struct nTask *task) {
  pthread_mutex_lock(&pool->mutex);
  LIST_INSERT(task, pool->tasks);
  pthread_cond_sigal(&pool->cond); // 发送一个信号，有人来办理业务了
  pthread_mutex_unlock(&pool->mutex);
}

#if 1

#define THREADPOOL_INIT_COUNT 20
#define TASK_INIT_SIZE 1000
#endif

void task_entry(struct nTask *task) { // type

  // struct nTask *task = (struct nTask*)task;
  int idx = *(int *)task->uset_data;

  printf("idx: %d\n", idx);

  free(task->uset_data);
  free(task);
}

int main(void) {

  ThreadPool pool = {0};

  nThreadPoolCreate(&pool, THREADPOOL_INIT_COUNT);
  // pool --> memset();

  int i = 0;
  for (i = 0; i < TASK_INIT_SIZE; i++) {
    struct nTask *task = (struct nTask *)malloc(sizeof(struct nTask));
    if (task == NULL) {
      perror("malloc");
      exit(1);
    }
    memset(task, 0, sizeof(struct nTask));

    task->task_funt = task_entry;
    task->uset_data = malloc(sizeof(int));
    *(int *)task->uset_data = i;

    nThreadPoolPushTask(&pool, task);
  }

  getchar();
}
