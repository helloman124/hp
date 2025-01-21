#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char** argv)
{
    int rank, numproc;
    int sum = 0;
    int total_sum = 0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Start the parallel execution time measurement
    double start_time = MPI_Wtime();

    // Each robot picks a random number of mangoes
    srand(rank);
    sum = rand() % 100;
    printf("Robot %d picked %d mangoes.\n", rank, sum);

    // Perform reduction to sum up all mangoes picked
    MPI_Reduce(&sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // The root process (rank 0) will display the total mangoes picked
    if (rank == 0) {
        printf("Total Mangoes picked by %d Robots = %d\n", numproc, total_sum);
    }

    // End the parallel execution time measurement
    double end_time = MPI_Wtime();

    // Calculate and display the parallel execution time
    if (rank == 0) {
        printf("Parallel Execution Time Taken: %.6f seconds\n", end_time - start_time);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
