/*************************************************************************
>> File Name: MatrixMultipl.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.06.07
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>

#define Width 4
#define Block_width 2

//device code
__global__ void MatrixMulKernel(int *d_M, int *d_N, int *d_P, int width)
{
    //计算P和M的行
    int Row = blockIdx.y * blockDim.y + threadIdx.y;

    //计算P和N的列
    int Col = blockIdx.x * blockDim.x + threadIdx.x;
    printf("Row = %d, Col = %d\n", Row, Col);
    if((Row < Width) && (Col < Width))
    {
        int Pvalue = 0;
        for(int i = 0; i < Width; ++i)
        {
            Pvalue += d_M[Row*Width + i]*d_N[i*Width + Col];
        }

        d_P[Row*Width + Col] = Pvalue;
    }
}


void showaray(int *A, int row, int col)
{
    for(int i = 0; i< row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            printf("%3d",A[i*Width + j]);
        }
        printf("\n");
    }
}
//Host code
int main(int argc, char *argv[])
{

    int dev_count;
    cudaDeviceProp dev_prop;

    cudaGetDeviceCount(&dev_count);
    printf("设备数:%d\n",dev_count);
    for(int i = 0; i < dev_count; ++i)
    {
        cudaGetDeviceProperties(&dev_prop,i);
        printf("每个block支持的最大线程数: %d\n", dev_prop.maxThreadsPerBlock);
        printf("设备中SM数: %d\n", dev_prop.multiProcessorCount);
        printf("时钟频率为: %d\n",dev_prop.clockRate);
        printf("每个Block的x方向的最大线程数: %d\n", dev_prop.maxThreadsDim[0]);
        printf("每个Block的y方向的最大线程数: %d\n", dev_prop.maxThreadsDim[1]);
        printf("每个Block的z方向的最大线程数: %d\n", dev_prop.maxThreadsDim[2]);
        printf("每个grid的x方向支持的最大的block数: %d\n", dev_prop.maxGridSize[0]);
        printf("每个grid的y方向支持的最大的block数: %d\n", dev_prop.maxGridSize[1]);
        printf("每个grid的z方向支持的最大的block数: %d\n", dev_prop.maxGridSize[2]);
        printf("每个warp包含的线程数为: %d\n", dev_prop.warpSize);
        printf("每个SM里面的registers变量个数:%d\n", dev_prop.regsPerBlock);
        printf("每个Block里共享内存:%lu\n", dev_prop.sharedMemPerBlock);
    }

    int N = Width * Width;
    size_t size = Width * Width * sizeof(int);

    int *h_M = (int *)malloc(size);
    int *h_N = (int *)malloc(size);
    int *h_P = (int *)malloc(size);
    //初始化h_M, h_N;
    for(int i = 0; i < N; ++i)
    {
        h_M[i] = 1;
        h_N[i] = 1;
        h_P[i] = 0;
    }
    printf("h_M, h_N,h_P分配成功\n");
    printf("打印h_M\n");
    showaray(h_M, Width, Width);
    printf("打印h_N\n");
    showaray(h_N, Width, Width);
    printf("打印h_P\n");
    showaray(h_P, Width, Width);

    int *d_M;
    cudaMalloc(&d_M, size);

    int *d_N;
    cudaMalloc(&d_N, size);

    int *d_P;
    cudaMalloc(&d_P, size);
    printf("d_M, d_N, d_P分配成功\n");

    cudaMemcpy(d_M, h_M, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_N, h_N, size, cudaMemcpyHostToDevice);
    printf("d_M, d_N, d_P拷贝到h成功\n");


    int NumBlocks = Width/Block_width;
    if(Width%Block_width )
        NumBlocks++;

    dim3 grid(NumBlocks, NumBlocks, 1);
    dim3 block(Block_width, Block_width, 1);
    MatrixMulKernel<<<grid, block>>>(d_M, d_N, d_P, Width);

    cudaMemcpy(h_P, d_P, size, cudaMemcpyDeviceToHost);
    printf("计算成功\n");

    showaray(h_P, Width, Width);
    cudaFree(d_M);
    cudaFree(d_M);
    cudaFree(d_P);
    printf("释放d_M, d_P, d_N成功\n");
    return 0;
}
