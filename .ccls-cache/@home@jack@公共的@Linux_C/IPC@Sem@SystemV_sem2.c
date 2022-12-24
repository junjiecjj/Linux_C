/*************************************************************************
>> File Name: sem_example2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月05日 星期日 23时16分06秒

>> 此程序的功能是：

https://blog.csdn.net/ljianhui/article/details/10243617


例子分析
：同时运行一个程序的两个实例，注意第一次运行时，要加上一个字符作为参数，例如本例中的字符‘O’，它用于区分是否为第一次调用，同时这个字符输出到屏幕中。因为每个程序都在其进入临界区后和离开临界区前打印一个字符，所以每个字符都应该成对出现，正如你看到的上图的输出那样。在main函数中循环中我们可以看到，每次进程要访问stdout（标准输出），即要输出字符时，每次都要检查信号量是否可用（即stdout有没有正在被其他进程使用）。所以，当一个进程A在调用函数semaphore_p进入了临界区，输出字符后，调用sleep时，另一个进程B可能想访问stdout，但是信号量的P请求操作失败，只能挂起自己的执行，当进程A调用函数semaphore_v离开了临界区，进程B马上被恢复执行。然后进程A和进程B就这样一直循环了10次。

************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *arry;
};

static int sem_id = 0;

static int set_semvalue();
static void del_semvalue();
static int semaphore_p();
static int semaphore_v();

int main(int argc, char *argv[]) {
  char message = 'X';
  int i = 0;

  //创建信号量
  sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

  if (argc > 1) {
    //程序第一次被调用，初始化信号量
    if (!set_semvalue()) {
      fprintf(stderr, "Failed to initialize semaphore\n");
      exit(EXIT_FAILURE);
    }
    //设置要输出到屏幕中的信息，即其参数的第一个字符
    message = argv[1][0];
    sleep(2);
  }
  for (i = 0; i < 10; ++i) {
    //进入临界区
    if (!semaphore_p())
      exit(EXIT_FAILURE);
    //向屏幕中输出数据
    printf("%c", message);
    //清理缓冲区，然后休眠随机时间
    fflush(stdout);
    sleep(rand() % 3);
    //离开临界区前再一次向屏幕输出数据
    printf("%c", message);
    fflush(stdout);
    //离开临界区，休眠随机时间后继续循环
    if (!semaphore_v())
      exit(EXIT_FAILURE);
    sleep(rand() % 2);
  }

  sleep(10);
  printf("\n%d - finished\n", getpid());

  if (argc > 1) {
    //如果程序是第一次被调用，则在退出前删除信号量
    sleep(3);
    del_semvalue();
  }
  exit(EXIT_SUCCESS);
}

static int set_semvalue() {
  //用于初始化信号量，在使用信号量前必须这样做
  union semun sem_union;

  sem_union.val = 1;
  if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    return 0;
  return 1;
}

static void del_semvalue() {
  //删除信号量
  union semun sem_union;

  if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_p() {
  //对信号量做减1操作，即等待P（sv）
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = -1; // P()
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1) {
    fprintf(stderr, "semaphore_p failed\n");
    return 0;
  }
  return 1;
}

static int semaphore_v() {
  //这是一个释放操作，它使信号量变为可用，即发送信号V（sv）
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1; // V()
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1) {
    fprintf(stderr, "semaphore_v failed\n");
    return 0;
  }
  return 1;
}

// 看了上面的例子，你可能还不是很明白，不过没关系，下面我就以另一个例子来说明一下，它实现的功能与前面的例子一样，运行方式也一样，都是两个相同的进程，同时向stdout中输出字符，只是没有使用信号量，两个进程在互相竞争stdout。它的代码非常简单，文件名为normalprint.c，代码如下：

/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        char message = 'X';
        int i = 0;
        if(argc > 1)
                message = argv[1][0];
        for(i = 0; i < 10; ++i)
        {
                printf("%c", message);
                fflush(stdout);
                sleep(rand() % 3);
                printf("%c", message);
                fflush(stdout);
                sleep(rand() % 2);
        }
        sleep(10);
        printf("\n%d - finished\n", getpid());
        exit(EXIT_SUCCESS);
}
*/
