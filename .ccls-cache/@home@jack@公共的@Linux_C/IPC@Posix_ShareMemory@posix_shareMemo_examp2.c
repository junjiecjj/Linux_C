/*************************************************************************
>> File Name: posix_shareMemo_examp2.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月08日 星期三 23时06分48秒

>> 此程序的功能是：

https://cloud.tencent.com/developer/article/1005543


gcc -o racing_posix_shm -lrt racing_posix_shm.c



对于这个程序，我们需要解释以下几点：

shm_open的SHMPATH参数是一个路径，这个路径默认放在系统的/dev/shm目录下。这是shm_open已经封装好的，保证了文件一定会使用tmpfs。
shm_open实际上就是open系统调用的封装。我们当然完全可以使用open的方式模拟这个方法。
使用ftruncate方法来设置“共享内存”的大小。其实就是更改文件的长度。
要以共享方式做mmap映射，并且指定文件描述符为shmfd。
shm_unlink实际上就是unlink系统调用的封装。如果不做unlink操作，那么文件会一直存在于/dev/shm目录下，以供其它进程使用。
关闭共享内存描述符直接使用close。
以上就是POSIX共享内存。其本质上就是个tmpfs文件。那么从这个角度说，mmap匿名共享内存、XSI共享内存和POSIX共享内存在内核实现本质上其实都是tmpfs。如果我们去查看POSIX共享内存的free空间占用的话，结果将跟mmap和XSI共享内存一样占用shared和buff/cache，所以我们就不再做这个测试了。这部分内容大家也可以参考《Linux内存中的Cache真的能被回收么？》。

根据以上例子，我们整理一下POSIX共享内存的使用相关方法：

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
int shm_open(const char *name, int oflag, mode_t mode);

int shm_unlink(const char *name);
使用shm_open可以创建或者访问一个已经创建的共享内存。上面说过，实际上POSIX共享内存就是在/dev/shm目录中的的一个tmpfs格式的文件，所以shm_open无非就是open系统调用的封装，所以起函数使用的参数几乎一样。其返回的也是一个标准的我呢间描述符。

shm_unlink也一样是unlink调用的封装，用来删除文件名和文件的映射关系。在这就能看出POSIX共享内存和XSI的区别了，一个是使用文件名作为全局标识，另一个是使用key。

映射共享内存地址使用mmap，解除映射使用munmap。使用ftruncate设置共享内存大小，实际上就是对tmpfs的文件进行指定长度的截断。使用fchmod、fchown、fstat等系统调用修改和查看相关共享内存的属性。close调用关闭共享内存的描述符。实际上，这都是标准的文件操作。
************************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#include <sys/types.h>

#define COUNT 100
#define SHMPATH "shm"

int do_child(char *shmpath) {
  int interval, shmfd, ret;
  int *shm_p;
  /* 使用shm_open访问一个已经创建的POSIX共享内存 */
  shmfd = shm_open(shmpath, O_RDWR, 0600);
  if (shmfd < 0) {
    perror("shm_open()");
    exit(1);
  }

  /* 使用mmap将对应的tmpfs文件映射到本进程内存 */
  shm_p = (int *)mmap(NULL, sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED,
                      shmfd, 0);
  if (MAP_FAILED == shm_p) {
    perror("mmap()");
    exit(1);
  }
  /* critical section */
  interval = *shm_p;
  interval++;
  usleep(1);
  *shm_p = interval;
  /* critical section */
  munmap(shm_p, sizeof(int));
  close(shmfd);

  exit(0);
}

int main() {
  pid_t pid;
  int count, shmfd, ret;
  int *shm_p;

  /* 创建一个POSIX共享内存 */
  shmfd = shm_open(SHMPATH, O_RDWR | O_CREAT | O_TRUNC, 0600);
  if (shmfd < 0) {
    perror("shm_open()");
    exit(1);
  }

  /* 使用ftruncate设置共享内存段大小 */
  ret = ftruncate(shmfd, sizeof(int));
  if (ret < 0) {
    perror("ftruncate()");
    exit(1);
  }

  /* 使用mmap将对应的tmpfs文件映射到本进程内存 */
  shm_p = (int *)mmap(NULL, sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED,
                      shmfd, 0);
  if (MAP_FAILED == shm_p) {
    perror("mmap()");
    exit(1);
  }

  *shm_p = 0;

  for (count = 0; count < COUNT; count++) {
    pid = fork();
    if (pid < 0) {
      perror("fork()");
      exit(1);
    }

    if (pid == 0) {
      do_child(SHMPATH);
    }
  }

  for (count = 0; count < COUNT; count++) {
    wait(NULL);
  }

  printf("shm_p: %d\n", *shm_p);
  munmap(shm_p, sizeof(int));
  close(shmfd);
  // sleep(3000);
  shm_unlink(SHMPATH);
  exit(0);
}
