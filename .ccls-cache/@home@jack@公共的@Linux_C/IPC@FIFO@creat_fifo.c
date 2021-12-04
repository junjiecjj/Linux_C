/*************************************************************************
>> File Name: creat_fifo.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com

>> Created Time: 2021年12月04日 星期六 17时02分28秒

>> 此程序的功能是：
************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s fifo_filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (mkfifo(argv[1], 0644) < 0) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }

  printf("create file \"%s\" success!\n", argv[1]);

  return 0;
}

/*

# root @ arch in ~/work on git:master x [17:17:33]
$ gcc a.c

# root @ arch in ~/work on git:master x [17:17:34]
$ ./a.out fifo
create file "fifo" success!

# root @ arch in ~/work on git:master x [17:17:38]
$ ll
total 16K
-rw-r--r-- 1 root root  461 Aug 13 17:15 a.c
-rwxr-xr-x 1 root root 8.5K Aug 13 17:17 a.out
prw-r--r-- 1 root root    0 Aug 13 17:17 fifo
*/
