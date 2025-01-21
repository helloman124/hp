#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float recvbuf, sendbuf[100];

    // Start the parallel execution time measurement
    double start_time = MPI_Wtime();

    // Rank 0 initializes the sendbuf and broadcasts data
    if (rank == 0) {
        int i;
        printf("Before Scatter: sendbuf of rank 0: ");
        for (i = 0; i < size; i++) {
            srand(i);  // Random seed based on rank
            sendbuf[i] = (float)(rand() % 1000) / 10;  // Random float values
            printf("%.1f ", sendbuf[i]);
        }
        printf("\nAfter Scatter:\n");
    }

    // Scatter the data from rank 0 to all processes
    MPI_Scatter(sendbuf, 1, MPI_FLOAT, &recvbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Print the received data for each process
    printf("rank = %d, Recvbuf: %.1f\n", rank, recvbuf);

    // End the parallel execution time measurement
    double end_time = MPI_Wtime();

    // Calculate and display the parallel execution time (only for rank 0)
    if (rank == 0) {
        printf("Parallel Execution Time Taken: %.6f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
