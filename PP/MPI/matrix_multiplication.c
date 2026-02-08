#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>


int main(int arc, char** argv){

  MPI_Init(&arc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  srand(time(NULL)+rank);
  
  int K =120; // no of total matrix
  int M =50;  // row of matrix
  int N =50;  // column of matrix
  int P =50;  // column of matrix

  // Broadcast the dimensions to all processes
  // MPI_Bcast(sendBuf,count,datatype,root,comm)
  MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&P, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if(K%size){
    printf("K should be divisible by size\n");
    MPI_Finalize();
    return 0;
  }
  int A[K][M][N];
  int B[K][N][P];
  int C[K][M][P];

  if(rank==0){
    for(int i=0;i<K;i++){
      for(int j=0;j<M;j++){
        for(int k=0;k<N;k++){
          A[i][j][k]=rand()%100;
        }
      }
      for(int j=0;j<N;j++){
        for(int k=0;k<P;k++){
          B[i][j][k]=rand()%100;
        }
      }
    }
  } 
  int local_K = K/size;
  int local_A[local_K][M][N];
  int local_B[local_K][N][P];
  int local_C[local_K][M][P];
  // Scatter the matrices A and B to all processes
  MPI_Scatter(A, local_K*M*N, MPI_INT, local_A, local_K*M*N, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(B, local_K*N*P, MPI_INT, local_B, local_K*N*P, MPI_INT, 0, MPI_COMM_WORLD);
  // Each process performs matrix multiplication on its local portion of the data
  for(int i=0;i<local_K;i++){
    for(int j=0;j<M;j++){
      for(int k=0;k<P;k++){
        local_C[i][j][k]=0;
        for(int l=0;l<N;l++){
          local_C[i][j][k]+=local_A[i][j][l]*local_B[i][l][k];
        }
      }
    }
  }
  // Gather the results from all processes to the root process
  MPI_Gather(local_C, local_K*M*P, MPI_INT, C, local_K*M*P, MPI_INT, 0, MPI_COMM_WORLD);
  
  if(rank==0){
    printf("Matrix multiplication completed successfully\n");
    for(int i=0;i<K;i++){
      for(int j=0;j<M;j++){
        for(int k=0;k<P;k++){
          printf("%d ",C[i][j][k]);
        }
        printf("\n");
      }
      printf("\n");
    }
  }
  MPI_Finalize();
  return 0;
}