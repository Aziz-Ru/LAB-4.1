#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    int K = 120, M = 50, N = 50, P = 50;

    MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&P, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (K % size != 0) {
        if (rank == 0)
            printf("K must be divisible by size\n");
        MPI_Finalize();
        return 0;
    }

    int local_K = K / size;

    /* Root matrices */
    int *A = NULL, *B = NULL, *C = NULL;

    if (rank == 0) {
        A = malloc(K * M * N * sizeof(int));
        B = malloc(K * N * P * sizeof(int));
        C = malloc(K * M * P * sizeof(int));

        for (int i = 0; i < K; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < N; k++)
                    A[i*M*N + j*N + k] = rand() % 10;

        for (int i = 0; i < K; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < P; k++)
                    B[i*N*P + j*P + k] = rand() % 10;
    }

    /* Local matrices */
    int *local_A = malloc(local_K * M * N * sizeof(int));
    int *local_B = malloc(local_K * N * P * sizeof(int));
    int *local_C = malloc(local_K * M * P * sizeof(int));

    MPI_Scatter(A, local_K*M*N, MPI_INT,
                local_A, local_K*M*N, MPI_INT,
                0, MPI_COMM_WORLD);

    MPI_Scatter(B, local_K*N*P, MPI_INT,
                local_B, local_K*N*P, MPI_INT,
                0, MPI_COMM_WORLD);

    /* Local multiplication */
    for (int i = 0; i < local_K; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < P; k++) {
                local_C[i*M*P + j*P + k] = 0;
                for (int l = 0; l < N; l++)
                    local_C[i*M*P + j*P + k] +=
                        local_A[i*M*N + j*N + l] *
                        local_B[i*N*P + l*P + k];
            }

    MPI_Gather(local_C, local_K*M*P, MPI_INT,
               C, local_K*M*P, MPI_INT,
               0, MPI_COMM_WORLD);

   
    MPI_Finalize();
    return 0;
}
