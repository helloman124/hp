#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main() {
    int r, i, ans = 0;
    printf("Enter number of sections : ");
    scanf("%d", &r);

    int **arr = (int**)malloc(r * sizeof(int*));
    int *size = (int*)malloc(r * sizeof(int));
    omp_set_num_threads(r);

    // Start timing for the parallel section
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for
        for (i = 0; i < r; i++) {
            srand(i);  // Use a different seed for each thread
            int j, sum = 0;
            size[i] = rand() % 20;
            arr[i] = (int*)malloc(size[i] * sizeof(int));

            // Fill the section with random values and compute the sum
            for (j = 0; j < size[i]; j++) {
                arr[i][j] = rand() % 100;
                sum += arr[i][j];
            }

            // Update the total sum in a thread-safe manner
            #pragma omp critical
            {
                ans += sum;
            }
        }
    }

    // End timing for the parallel section
    double end_time = omp_get_wtime();
    printf("Parallel computation took %f seconds\n", end_time - start_time);

    // Print the sections and the total sum
    for (i = 0; i < r; i++) {
        printf("Section - %2d ( %3d Items ) : ", i, size[i]);
        for (int j = 0; j < size[i]; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    // Print the total amount
    printf("Total Amount : %d\n", ans);

    // Free the allocated memory
    for (i = 0; i < r; i++) {
        free(arr[i]);
    }
    free(arr);
    free(size);
}
