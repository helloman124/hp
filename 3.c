#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

void main() {
    int num, i;
    printf("Enter the number of steps : ");
    scanf("%d", &num);

    // Start the wall-clock time for parallel execution
    double start_time = omp_get_wtime();
    
    double step = 1.0 / (double)num, pi = 0.0;
    omp_set_num_threads(num);

    // Parallel region with reduction on pi
    #pragma omp parallel for reduction(+:pi)
    for(i = 0; i < num; i++) {
        double x = (i + 0.5) * step;
        double local_pi = (4.0 * step) / (1 + x * x);
        pi += local_pi;
    }

    // End the wall-clock time for parallel execution
    double end_time = omp_get_wtime();

    // Calculate the time taken for parallel execution
    double time_taken = end_time - start_time;
    printf("Parallel Execution Time Taken: %lf seconds\n", time_taken);

    // Output the calculated value of Pi
    printf("Value of Pi = %.16lf\n", pi);
}
