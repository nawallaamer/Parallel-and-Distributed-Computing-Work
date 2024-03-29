#include <stdio.h>
#include <omp.h>

#define SIZE 1000
int WinCountCalculation(int key) 
{
    int win = 0;
    int r = 0;
    while (r < SIZE) 
    {
        int k = 0;
        while (k < SIZE) 
        {
            int h = 0;
            while (h < SIZE) 
            {
                int a = (r * r * 1000 / 35) % 1000;
                int b = (k * k * 1000 / 36) % 1000;
                int c = (h * h * 1000 / 37) % 1000;
                if (key == (a + b + c))
                {
                    win++;
                }
                h++;
            }
            k++;
        }
        r++;
    }
    return win;
}
void ParallelExecution(int num_threads, int key) 
{
    int win = 0;
    int r = 0;
    while (r < SIZE) 
    {
        int k = 0;
        while (k < SIZE) 
        {
            int h = 0;
            while (h < SIZE) 
            {
                int a = (r * r * 1000 / 35) % 1000;
                int b = (k * k * 1000 / 36) % 1000;
                int c = (h * h * 1000 / 37) % 1000;
                if (key == (a + b + c)) 
                {
                    win++;
                }
                h++;
            }
            k++;
        }
        r++;
    }
    printf("Total Wins: %d\n", win);
}
int main() 
{
    int key = 111;
    double startingtime, endingtime;
    startingtime = omp_get_wtime();
    int win = WinCountCalculation(key);
    endingtime = omp_get_wtime();
    printf("Sequential Execution Time: %f seconds\n", endingtime - startingtime);
    printf("Total Wins: %d\n", win);
    win = 0;
    for (int num_threads = 2; num_threads <= 4; num_threads++) 
    {
    	startingtime=omp_get_wtime();
        ParallelExecution(num_threads, key);
        endingtime=omp_get_wtime();
        printf("Parallel Execution Time with %d Threads: %f seconds\n", num_threads, endingtime-startingtime);
    }
    return 0;
}
