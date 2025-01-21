#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main() {
    int m, n;
    printf("Enter the size of square matrix : ");
    scanf("%d", &n);
    printf("Enter the size of vector : ");
    scanf("%d", &m);
    if (m != n) {
        printf("Multiplication is not possible.\n");
        exit(0);
    }

    int i = 0, j = 0;
    int **arr = (int**)malloc(n * sizeof(int*));
    int *vec = (int*)malloc(n * sizeof(int));
    int *res = (int*)malloc(n * sizeof(int));

    // Set the number of threads to be used
    omp_set_num_threads(n);

    // Start timing for the initialization phase
    double start_time = omp_get_wtime();

    #pragma omp parallel private(j)
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            srand(i);  // To get different random numbers for each thread
            arr[i] = (int*)malloc(n * sizeof(int));
            vec[i] = rand() % 100;
            for (j = 0; j < n; j++) {
                arr[i][j] = rand() % 100;
            }
        }
    }

    // End timing for initialization phase
    double end_time = omp_get_wtime();
    printf("Initialization took %f seconds\n", end_time - start_time);

    // Start timing for the multiplication phase
    start_time = omp_get_wtime();

    #pragma omp parallel private(j)
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            res[i] = 0;
            for (j = 0; j < n; j++)
                res[i] += arr[i][j] * vec[j];
        }
    }

    // End timing for multiplication phase
    end_time = omp_get_wtime();
    printf("Multiplication took %f seconds\n", end_time - start_time);

    // Print the result
    printf("Matrix * Vector = Resultant Matrix\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%3d ", arr[i][j]);
        if (i == n / 2)
            printf("  *  %3d  = %6d\n", vec[i], res[i]);
        else
            printf("     %3d    %6d\n", vec[i], res[i]);
    }

    // Clean up
    for (i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    free(vec);
    free(res);
}
