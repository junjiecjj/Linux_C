/*************************************************************************
>> File Name: SystemV_ShareMemo_examp2_read.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 22时05分15秒

>> 此程序的功能是：
https://blog.csdn.net/ljianhui/article/details/10253345
下面就以两个不相关的进程来说明进程间如何通过共享内存来进行通信。其中一个文件shmread.c创建共享内存，并读取其中的信息，另一个文件shmwrite.c向共享内存中写入数据。为了方便操作和数据结构的统一，为这两个文件定义了相同的数据结构，定义在文件shmdata.c中。结构shared_use_st中的written作为一个可读或可写的标志，非0：表示可读，0表示可写，text则是内存中的文件。


分析：
1、程序shmread创建共享内存，然后将它连接到自己的地址空间。在共享内存的开始处使用了一个结构struct_use_st。该结构中有个标志written，当共享内存中有其他进程向它写入数据时，共享内存中的written被设置为0，程序等待。当它不为0时，表示没有进程对共享内存写入数据，程序就从共享内存中读取数据并输出，然后重置设置共享内存中的written为0，即让其可被shmwrite进程写入数据。

2、程序shmwrite取得共享内存并连接到自己的地址空间中。检查共享内存中的written，是否为0，若不是，表示共享内存中的数据还没有被完，则等待其他进程读取完成，并提示用户等待。若共享内存的written为0，表示没有其他进程对共享内存进行读取，则提示用户输入文本，并再次设置共享内存中的written为1，表示写完成，其他进程可对共享内存进行读操作。

四、关于前面的例子的安全性讨论
这个程序是不安全的，当有多个程序同时向共享内存中读写数据时，问题就会出现。可能你会认为，可以改变一下written的使用方式，例如，只有当written为0时进程才可以向共享内存写入数据，而当一个进程只有在written不为0时才能对其进行读取，同时把written进行加1操作，读取完后进行减1操作。这就有点像文件锁中的读写锁的功能。咋看之下，它似乎能行得通。但是这都不是原子操作，所以这种做法是行不能的。试想当written为0时，如果有两个进程同时访问共享内存，它们就会发现written为0，于是两个进程都对其进行写操作，显然不行。当written为1时，有两个进程同时对共享内存进行读操作时也是如些，当这两个进程都读取完是，written就变成了-1.

要想让程序安全地执行，就要有一种进程同步的进制，保证在进入临界区的操作是原子操作。例如，可以使用前面所讲的信号量来进行进程的同步。因为信号量的操作都是原子性的。
************************************************************************/

int main(int argc, char *argv[]) {
  int running = 1;              //程序是否继续运行的标志
  void *shm = NULL;             //分配的共享内存的原始首地址
  struct shared_use_st *shared; //指向shm
  int shmid;                    //共享内存标识符
  //创建共享内存
  shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
  if (shmid == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(EXIT_FAILURE);
  }
  //将共享内存连接到当前进程的地址空间
  shm = shmat(shmid, 0, 0);
  if (shm == (void *)-1) {
    fprintf(stderr, "shmat failed\n");
    exit(EXIT_FAILURE);
  }
  printf("\nMemory attached at %X\n", (int)shm);
  //设置共享内存
  shared = (struct shared_use_st *)shm;
  shared->written = 0;
  while (running) //读取共享内存中的数据
  {
    //没有进程向共享内存定数据有数据可读取
    if (shared->written != 0) {
      printf("You wrote: %s", shared->text);
      sleep(rand() % 3);
      //读取完数据，设置written使共享内存段可写
      shared->written = 0;
      //输入了end，退出循环（程序）
      if (strncmp(shared->text, "end", 3) == 0)
        running = 0;
    } else //有其他进程在写数据，不能读取数据
      sleep(1);
  }
  //把共享内存从当前进程中分离
  if (shmdt(shm) == -1) {
    fprintf(stderr, "shmdt failed\n");
    exit(EXIT_FAILURE);
  }
  //删除共享内存
  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    fprintf(stderr, "shmctl(IPC_RMID) failed\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
