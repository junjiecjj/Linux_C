/*使用private子句和critical部分并行化的程序*/
#include<stdio.h>
#include<stdlib.h>
#define NUM_THREADS 6

int main()
{
    int i = 1;
    unsigned long long int N = 1000000000000000000;
    printf("N = %llu\n", N);
    printf("i = %.20lf\n",0.11111111111111111);
    return 0;
}

/*
int main ()
{
	int i,id;
	double x, sum, pi=0.0;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel private (x,i,id,sum)
	{
		id = omp_get_thread_num();
	  	for (i=id,sum=0.0;i< num_steps;i=i+NUM_THREADS){
            printf("%d 被线程 %d 处理\n",i,id);
		  	x = (i+0.5)*step;
		  	sum += 4.0/(1.0+x*x);
	  	}
		#pragma omp critical
	  		pi += sum*step;

//		#pragma omp barrier
//
//	  	#pragma omp master
//  	          printf("Pi = %lf\n",pi);
  	 }
	printf("Pi = %lf\n",pi);
    return 0;
}

*/

/*
int main ()
{
	double pi=0.0;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
    {
        int i,id;
        double x,sum;
		id = omp_get_thread_num();
	  	for (i=id,sum=0.0;i< num_steps;i=i+NUM_THREADS){
            printf("%d 被线程 %d 处理\n",i,id);
		  	x = (i+0.5)*step;
		  	sum += 4.0/(1.0+x*x);
	  	}
		#pragma omp critical
	  		pi += sum*step;

//		#pragma omp barrier
//
//	  	#pragma omp master
//  	          printf("Pi = %lf\n",pi);
  	 }
	printf("Pi = %lf\n",pi);
    return 0;
}

*/

/*
int main ()
{   int i,id;
    double x,sum,pi=0.0;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel private(i,id,sum)
    {

		id = omp_get_thread_num();
	  	for (i=id,sum=0.0;i< num_steps;i=i+NUM_THREADS){
            printf("%d 被线程 %d 处理\n",i,id);
		  	x = (i+0.5)*step;
		  	sum += 4.0/(1.0+x*x);
	  	}
		#pragma omp critical
	  		pi += sum*step;

//		#pragma omp barrier
//
//	  	#pragma omp master
//  	          printf("Pi = %lf\n",pi);
  	 }
	printf("Pi = %lf\n",pi);
    return 0;
}

0 被线程 0 处理
6 被线程 0 处理
12 被线程 0 处理
18 被线程 0 处理
3 被线程 3 处理
9 被线程 3 处理
15 被线程 3 处理
21 被线程 3 处理
2 被线程 2 处理
8 被线程 2 处理
14 被线程 2 处理
20 被线程 2 处理
4 被线程 4 处理
10 被线程 4 处理
1 被线程 1 处理
7 被线程 1 处理
13 被线程 1 处理
19 被线程 1 处理
16 被线程 4 处理
22 被线程 4 处理
5 被线程 5 处理
11 被线程 5 处理
17 被线程 5 处理
23 被线程 5 处理
我是线程 1, 我的sum 为13.076551
我是线程 4, 我的sum 为12.066606
我是线程 2, 我的sum 为12.754286
我是线程 0, 我的sum 为13.380499
我是线程 5, 我的sum 为11.707106
我是线程 3, 我的sum 为12.416647
我是线程 4, 我的sum = 12.066606
我是线程 5, 我的sum = 11.707106
我是线程 2, 我的sum = 12.754286
我是线程 1, 我的sum = 13.076551
*********************
我是线程0,Pi = 3.141737
我是线程 0, 我的sum = 13.380499
我是线程 3, 我的sum = 12.416647
Pi = 3.141737
*/
