#include<stdio.h>
#include<stdlib.h>
#define number_places 13

typedef struct{
	int min_dist;//最短距离
	int num_path;//最短路径地点个数
	int *p_path;//最短路径点
}DpStruct;

void dp(int (*const data)[number_places],DpStruct *p);

int main(int argc,char **argv){
	int i;
	/*路线数组，从后往前，第一维表示第几个结点，第二维表示与其它结点的距离，0表示不相连 */
	int data[][number_places]={
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,4,2,0,0,0,0,0,0,0,0,0,0},
	{0,6,9,0,0,0,0,0,0,0,0,0,0},
	{0,7,5,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,5,0,0,0,0,0,0,0,0},
	{0,0,0,8,4,6,0,0,0,0,0,0,0},
	{0,0,0,4,4,2,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,9,5,0,0,0,0,0},
	{0,0,0,0,0,0,4,3,5,0,0,0,0},
	{0,0,0,0,0,0,0,1,7,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,3,5,4,0},
	};
	DpStruct *p=malloc(sizeof(DpStruct));
	dp(data,p);
	printf("最短距离：%d\012",p->min_dist);
	printf("途径地点个数：%d\012",p->num_path);
	printf("所经路径：");
	for(i=0;i<p->num_path;++i)
		printf("%d\t",p->p_path[i]);
	printf("\012");
	free(p->p_path);
	free(p);
	return EXIT_SUCCESS;
}


void dp(int (*const data)[number_places],DpStruct *p){
	/*求取最短路径*/
	int min_dist[number_places]={0};//申请min_dist数组存放每个状态的最短距离，min_dist[0]置0
	int decision[number_places]={0};//申请decision数组存放每个状态的决策
	int i,j,min;
	for(i=1;i<number_places;++i){
		min_dist[i]=99999;               //min_dist[i]为一很大的数，足以大过该状态的最短距离
		for(j=0;j<i;++j)
			if(data[i][j]!=0 && (min=data[i][j]+min_dist[j])<min_dist[i]){	  //每个状态的决策可能不止一个，判断min得到min_dist[i]
				decision[i]=j;     //每个状态的决策
				min_dist[i]=min;    //每个状态的最短距离
			}
	}

	/*求取所经路径*/
	int path[number_places]={number_places-1};//申请path数组存放路径
	i=0;//将i置0
	while(path[i++]!=0){  //只要path[i]！=0，则继续
		path[i]=decision[path[i-1]];//第i个点路径，为前一个点状态的决策
	}

	/*对结构赋值*/
	p->min_dist=min_dist[number_places-1];	//赋值最短距离
	p->num_path=i;//赋值地点个数
	p->p_path=malloc(p->num_path*sizeof(int));//赋值路径点
	for(i=0;i<p->num_path;++i){
		p->p_path[i]=path[i];
	}
}