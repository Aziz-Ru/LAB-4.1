#include<mpi.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[8]={1,2,3,4,5,6,7,8};
    int recv[2];
    MPI_Scatter(arr, 2, MPI_INT, recv, 2, MPI_INT, 0, MPI_COMM_WORLD);
    // printf("Process %d received: %d %d\n", rank, recv[0], recv[1]);
    int local_sum = recv[0] + recv[1];
    printf("Process %d local sum: %d\n", rank, local_sum);
    int result[4];
    MPI_Gather(&local_sum,1,MPI_INT,result,1,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<4;i++){
        printf("Process %d gathered result[%d]: %d\n", rank, i, result[i]);
    }
    if (rank == 0) {
        int global_sum = 0;
        for (int i = 0; i < 4; i++) {
            global_sum += result[i];
        }
        printf("Global sum: %d\n", global_sum);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}