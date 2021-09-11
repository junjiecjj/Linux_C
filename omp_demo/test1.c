/*使用共享任务结构并行化的程序*/
#include <omp.h>
#include<stdio.h>
static long num_steps = 24;
double step;
#define NUM_THREADS 6
int main ()
{
    int i,id;
    double x, pi, sum[NUM_THREADS];
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel  //private(i)
    {
        id = omp_get_thread_num();
	    //sum[id] = 0;
        #pragma omp for schedule(static ,2)
        for (i = 0, sum[id] = 0;i< num_steps; i++)
        {
            printf("%-5d 被线程 %d 处理\n",i,id);
            x = (i+0.5)*step;
            sum[id] += 4.0/(1.0+x*x);
	  	}
	}
    for(i=0, pi=0.0;i<NUM_THREADS;i++)pi += sum[i] * step;
    printf("Pi = %lf\n",pi);
    return 0;
}

/*
int main ()
{
    int i;
    double  pi, sum[NUM_THREADS];
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel private(i)
{
    int id;
    double x;
	id = omp_get_thread_num();
	sum[id] = 0;
#pragma omp for
    for (i=0;i< num_steps; i++){
        printf("%d 被线程 %d 处理\n",i,id);
        x = (i+0.5)*step;
        sum[id] += 4.0/(1.0+x*x);
	  	}
	  }
for(i=0, pi=0.0;i<NUM_THREADS;i++)pi += sum[i] * step;
printf("Pi = %lf\n",pi);
return 0;
}

0     被线程 0 处理
1     被线程 0 处理
2     被线程 0 处理
3     被线程 0 处理
16    被线程 4 处理
17    被线程 4 处理
18    被线程 4 处理
19    被线程 4 处理
8     被线程 2 处理
9     被线程 2 处理
10    被线程 2 处理
11    被线程 2 处理
4     被线程 1 处理
5     被线程 1 处理
6     被线程 1 处理
7     被线程 1 处理
20    被线程 5 处理
21    被线程 5 处理
22    被线程 5 处理
23    被线程 5 处理
12    被线程 3 处理
13    被线程 3 处理
14    被线程 3 处理
15    被线程 3 处理
Pi = 3.141737
*/
