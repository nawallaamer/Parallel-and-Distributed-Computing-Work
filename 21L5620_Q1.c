#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

void Primeinitialization(bool *p, int num, int numProcs) 
{
    int r = 0;
    #pragma omp parallel num_threads(numProcs) private(r)
    while (r < num) 
    {
        p[r] = true;
        r++;
    }
}

void Primecalculation(bool *p, int num, int numProcs) 
{
    int r = 0;
    #pragma omp parallel num_threads(numProcs) private(r)
    while (r < num) 
    {
        if (p[r]) 
        {
            int k = 3;
            while (k <= sqrt(r * 2 + 3)) 
            {
                if (r % k == 0) 
                {
                    p[r] = false;
                    break;
                }
                k += 2;
            }    
        }
        r++;
    }
}

void writingtofile(bool *p, int num, char *outputFile) 
{
    FILE *fp = fopen(outputFile, "w");
    int r = 0;
    while (r < num) 
    {
        if (p[r]) 
        {
            fprintf(fp, "%d\n", r * 2 + 3);
        }
        r++;
    }
    fclose(fp);
}

int main(int argc, char *argv[]) 
{
    int numProcs = atoi(argv[1]);
    int num = atoi(argv[2]);
    char *outputFile = argv[3];
    bool *p = (bool *)malloc(num * sizeof(bool));
    double startingtime = omp_get_wtime();
    Primeinitialization(p, num, numProcs);
    Primecalculation(p, num, numProcs);
    double endingtime = omp_get_wtime();
    printf("Time Taken(sec): %f seconds\n", endingtime - startingtime);
    writingtofile(p, num, outputFile);
    free(p);
    return 0;
}
