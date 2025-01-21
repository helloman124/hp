#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
    int n, i;
    printf("Number of terms : ");
    scanf("%d", &n);
    
    int* a = (int*)malloc(n * sizeof(int));
    a[0] = 0;
    a[1] = 1;

    // Start the wall-clock time for parallel execution
    double start_time = omp_get_wtime();

    // Set the number of threads
    omp_set_num_threads(2);

    #pragma omp parallel
    {
        // Single thread computes the Fibonacci sequence
        #pragma omp single
        {
            printf("id of thread involved in the computation of fibonacci numbers = %d\n", omp_get_thread_num());
            for (i = 2; i < n; i++) {
                a[i] = a[i - 2] + a[i - 1];
            }
        }

        // Single thread displays the Fibonacci sequence
        #pragma omp single
        {
            printf("id of thread involved in the displaying of fibonacci numbers = %d\n", omp_get_thread_num());
            printf("Fibonacci numbers: ");
            for (i = 0; i < n; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");
        }
    }

    // End the wall-clock time for parallel execution
    double end_time = omp_get_wtime();
    
    // Calculate the time taken for parallel execution
    double time_taken = end_time - start_time;
    printf("Parallel Execution Time Taken: %lf seconds\n", time_taken);

    free(a);
    return 0;
}
