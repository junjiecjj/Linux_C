#include<mpi.h>
#include<omp.h>
#include<stdio.h>
#include<math.h>
//#define N 10000000000

int main( int argc, char* argv[] ){
    long long int N = 10000000000000;
    int rank, nproc;
    int i,low,up;
    double local = 0.0, pi, w = 0.0000000000000000001, temp;
    int thread_num = 4;

    MPI_Status  status;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &nproc );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    //w = 1.0/N;
    printf("w = %.19f\n",w);
	low = rank*(N / nproc);
	up = low + N/nproc - 1;
	#pragma omp parallel for reduction(+:local) private(temp,i) num_threads(thread_num)
    for (i=low;i<up; i++){
        temp = (i + 0.5)*w;
        local = local + 4.0/(1.0+temp*temp);
    }
    MPI_Reduce(&local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);
    if(rank==0) printf("pi = %.20f\n",pi*w);
    MPI_Finalize();
}
