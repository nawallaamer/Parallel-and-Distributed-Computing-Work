#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 600
#define NUM_THREADS 3
int main() 
{
    int arr[N];
    int key = 13;
    int occurrences = 0;
    int r = 0;
    while (r < N) 
    {
        arr[r] = rand() % 100;
        r++;
    }
    #pragma omp parallel num_threads(NUM_THREADS) reduction(+:occurrences)
    {
        int count = 0;
        int r = 0;
        while (r < N) 
        {
            if (arr[r] == key) 
            {
                count++;
            }
            r++;
        }
        occurrences += count;
    }
    printf("Total occurrences of %d: %d\n", key, occurrences);
    return 0;
}
