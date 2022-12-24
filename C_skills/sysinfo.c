

/************************************************************************************

Linux中，sysinfo是用来获取系统相关信息的结构体，返回系统的统计信息。

头文件：
#include <sys/sysinfo.h>
函数声明：
int sysinfo (struct sysinfo *info);
功能：用来获取系统相关信息的结构体
参数：@info 结构体变量地址
返回值：0 - 操作成功；-1 - 操作错误，errno被设置

struct sysinfo {
    long uptime;                  // 启动到现在经过的时间
unsigned long loads[3];  // 1, 5, and 15 分钟平均负载
unsigned long totalram;  // 总的可用的内存大小
unsigned long freeram;   //还未被使用的内存大小
unsigned long sharedram; // 共享的存储器的大小
unsigned long bufferram; // 共享的存储器的大小
unsigned long totalswap; // 交换区大小
unsigned long freeswap;  // 还可用的交换区大小
unsigned short procs;    // 当前进程数目
unsigned long totalhigh; //总的高内存大小
unsigned long freehigh;  // 可用的高内存大小
unsigned int mem_unit;   // 以字节为单位的内存大小
char _f[20 - 2 * sizeof(long) - sizeof(int)]; // libc5的补丁
}
;

************************************************************************************/

#include <stdio.h>
#include <sys/sysinfo.h>

int main(int argc, char *agrv[]) {
  struct sysinfo s_info;
  int error;
  error = sysinfo(&s_info);
  printf("\n\ncode error=%d\n", error);
  printf("Uptime = %lus\nLoad: 1 min %lu / 5 min %lu / 15 min %lu\n"
         "RAM: total %lu / free %lu /shared %lu\n"
         "Memory in buffers = %lu\nSwap:total %lu/free %lu\n"
         "Number of processes = %lu\n",
         s_info.uptime, s_info.loads[0], s_info.loads[1], s_info.loads[2],
         s_info.totalram, s_info.freeram, s_info.totalswap, s_info.freeswap,
         s_info.procs);

  printf("\n**********************************\n");
  return 0;
}
