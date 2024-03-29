#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100
void initializeMatrices(int ***x, int ***y, int ***z) 
{
    *x = (int **)malloc(N * sizeof(int *));
    *y = (int **)malloc(N * sizeof(int *));
    *z = (int **)malloc(N * sizeof(int *));
    for (int r = 0; r < N; r++) 
    {
        (*x)[r] = (int *)malloc(N * sizeof(int));
        (*y)[r] = (int *)malloc(N * sizeof(int));
        (*z)[r] = (int *)malloc(N * sizeof(int));
    }
}
void fillMatrices(int **x, int **y) 
{
    int r = 0;
    while (r < N) 
    {
        int k = 0;
        while (k < N) 
        {
            x[r][k] = rand() % 100;
            y[r][k] = rand() % 10;
            k++;
        }
        r++;
    }
}
void multiplyMatrices(int **x, int **y, int **z, int start, int end) 
{
    int r = start;
    while (r < end) 
    {
        int k = 0;
        while (k < N) 
        {
            int sum = 0;
            int h = 0;
            while (h < N) 
            {
                sum += x[r][h] * y[h][k];
                h++;
            }
            z[r][k] = sum;
            k++;
        }
        r++;
    }
}

int main() 
{
    int **x, **y, **z;
    double startingtime, endingtime;
    initializeMatrices(&x, &y, &z);
    fillMatrices(x, y);
    printf("Coarse Parallelization:\n");
    startingtime = omp_get_wtime();
    #pragma omp parallel for
    for (int r = 0; r < N; r++) 
    {
        multiplyMatrices(x, y, z, r, r + 1);
    }
    endingtime = omp_get_wtime();
    printf("Execution Time (default schedule): %f seconds\n", endingtime - startingtime);
    startingtime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(static)
        for (int r = 0; r < N; r++) 
        {
            multiplyMatrices(x, y, z, r, r + 1);
        }
    }
    endingtime = omp_get_wtime();
    printf("Execution Time (static schedule): %f seconds\n", endingtime - startingtime);
    startingtime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for (int r = 0; r < N; r++) 
        {
            multiplyMatrices(x, y, z, r, r + 1);
        }
    }
    endingtime = omp_get_wtime();
    printf("Execution Time (dynamic schedule): %f seconds\n", endingtime - startingtime);
    printf("\nFine Parallelization:\n");
    startingtime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for
        for (int r = 0; r < N; r++) 
        {
            multiplyMatrices(x, y, z, r, r + 1);
        }
    }
    endingtime = omp_get_wtime();
    printf("Execution Time (default schedule): %f seconds\n", endingtime - startingtime);
    startingtime = omp_get_wtime();
    #pragma omp parallel num_threads(N)
    {
        #pragma omp for schedule(static)
        for (int r = 0; r < N; r++) 
        {
            multiplyMatrices(x, y, z, r, r + 1);
        }
    }
    endingtime = omp_get_wtime();
    printf("Execution Time (static schedule): %f seconds\n", endingtime - startingtime);

    startingtime = omp_get_wtime();
    #pragma omp parallel num_threads(N)
    {
        #pragma omp for schedule(dynamic)
        for (int r = 0; r < N; r++) 
        {
            multiplyMatrices(x, y, z, r, r + 1);
        }
    }
    endingtime = omp_get_wtime();
    printf("Execution Time (dynamic schedule): %f seconds\n", endingtime - startingtime);
    for (int r = 0; r < N; r++) 
    {
        free(x[r]);
        free(y[r]);
        free(z[r]);
    }
    free(x);
    free(y);
    free(z);
    return 0;
}
