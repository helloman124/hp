#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
    int n, i;
    printf("Enter the number of students : ");
    scanf("%d", &n);
    
    double* arr = (double*)malloc(n * sizeof(double));
    double arr_max = 0.0;

    // Start timing the parallel section
    double start_time = omp_get_wtime();

    // Parallel section to initialize CGPA values
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        srand(i);  // Different seed for each thread
        arr[i] = (double)(rand() % 10000) / 1000;  // CGPA value between 0.0 and 10.0
    }

    // Display CGPA values
    printf("CGPA of students : ");
    for (i = 0; i < n; i++) {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");

    // Parallel section to find the maximum CGPA
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        #pragma omp critical
        if (arr_max < arr[i]) {
            arr_max = arr[i];
        }
    }

    // End timing for the parallel section
    double end_time = omp_get_wtime();
    
    // Calculate and print the time taken for parallel execution
    double parallel_time_taken = end_time - start_time;
    printf("Student with highest CGPA = %.2lf\n", arr_max);
    printf("Parallel Execution Time Taken: %.6lf seconds\n", parallel_time_taken);

    free(arr);  // Free allocated memory
    return 0;
}
