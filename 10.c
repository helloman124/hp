#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main() {
    int n;
    printf("Enter the dimension of square matrices: ");
    scanf("%d", &n);

    int i = 0, j = 0, k = 0;
    int** arr1 = (int**)malloc(n * sizeof(int*));
    int** arr2 = (int**)malloc(n * sizeof(int*));
    int** res = (int**)malloc(n * sizeof(int*));

    omp_set_num_threads(64);  // Set number of threads

    // Matrix initialization using parallel region
    #pragma omp parallel private(j)
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            srand(i);  // Initialize seed based on i
            arr1[i] = (int*)malloc(n * sizeof(int));
            arr2[i] = (int*)malloc(n * sizeof(int));
            res[i] = (int*)malloc(n * sizeof(int));
            for (j = 0; j < n; j++) {
                arr1[i][j] = rand() % 100;
                arr2[i][j] = rand() % 100;
            }
        }
    }

    // Parallel matrix multiplication
    double st = omp_get_wtime();  // Start the timer for parallel algorithm
    #pragma omp parallel private(j, k)
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                res[i][j] = 0;
                for (k = 0; k < n; k++)
                    res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    double et = omp_get_wtime();  // End the timer for parallel algorithm
    printf("Time taken by parallel algorithm: %lf seconds\n", et - st);

    // Sequential matrix multiplication
    st = omp_get_wtime();  // Start the timer for sequential algorithm
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = 0;
            for (k = 0; k < n; k++)
                res[i][j] += arr1[i][k] * arr2[k][j];
        }
    }
    et = omp_get_wtime();  // End the timer for sequential algorithm
    printf("Time taken by sequential algorithm: %lf seconds\n", et - st);

    // Clean up memory
    for (i = 0; i < n; i++) {
        free(arr1[i]);
        free(arr2[i]);
        free(res[i]);
    }
    free(arr1);
    free(arr2);
    free(res);
}
