#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 50
int partition(int array[], int low, int high, int ascending) 
{
    int pivot = array[high];
    int r = (low - 1);
    int k = low;
    while (k <= high - 1) 
    {
        if ((ascending && array[k] < pivot) || (!ascending && array[k] > pivot)) 
        {
            r++;
            int temp = array[r];
            array[r] = array[k];
            array[k] = temp;
        }
        k++;
    }
    int temp = array[r + 1];
    array[r + 1] = array[high];
    array[high] = temp;
    return (r + 1);
}
void quickSort(int array[], int low, int high, int ascending) 
{
    while (low < high) 
    {
        int pi = partition(array, low, high, ascending);
        #pragma omp task
        quickSort(array, low, pi - 1, ascending);
        low = pi + 1;
    }
}
void sortRow(int matrix[MAX_SIZE][MAX_SIZE], int row, int a, int ascending) 
{
    quickSort(matrix[row], 0, a - 1, ascending);
}
void sortColumn(int matrix[MAX_SIZE][MAX_SIZE], int column, int b, int ascending) 
{
    int temp[MAX_SIZE];
    for (int r = 0; r < b; r++) 
    {
        temp[r] = matrix[r][column];
    }
    quickSort(temp, 0, b - 1, ascending);
    for (int r = 0; r < b; r++) 
    {
        matrix[r][column] = temp[r];
    }
}
void matrixSum(int matrix[MAX_SIZE][MAX_SIZE], int a, int b) 
{
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int r = 0; r < a; r++) 
    {
        int k = 0;
        while (k < b) 
        {
            sum += matrix[r][k];
            k++;
        }
    }
    printf("Matrix Sum: %d\n", sum);
}

int main() 
{
    double startingtime, endingtime;
    int a, b;
    printf("Enter the Number of Rows and Columns of the Matrix: ");
    scanf("%d %d", &a, &b);
    int matrix[MAX_SIZE][MAX_SIZE];
    printf("Enter the Elements of the Matrix:\n");
    for (int r = 0; r < a; r++) 
    {
        int k = 0;
        while (k < b) 
        {
            scanf("%d", &matrix[r][k]);
            k++;
        }
    }
    int lastDigit; 
    printf("Enter the Last Digit of your Student ID: ");
    scanf("%d", &lastDigit);
    startingtime = omp_get_wtime();
    if (lastDigit == 0 || lastDigit == 1 || lastDigit == 2) 
    {
        #pragma omp parallel for num_threads(b)
        for (int r = 0; r < b; r++) 
        {
            sortColumn(matrix, r, a, 1);
        }
    } 
    else if (lastDigit == 3 || lastDigit == 4 || lastDigit == 5) 
    {
        #pragma omp parallel for num_threads(b)
        for (int r = 0; r < b; r++) 
        {
            sortColumn(matrix, r, a, 0);
        }
    } 
    else if (lastDigit == 6 || lastDigit == 7) 
    {
        #pragma omp parallel for num_threads(a)
        for (int r = 0; r < a; r++) 
        {
            sortRow(matrix, r, b, 1);
        }
    } 
    else if (lastDigit == 8 || lastDigit == 9) 
    {
        #pragma omp parallel for num_threads(a)
        for (int r = 0; r < a; r++) 
        {
            sortRow(matrix, r, b, 0);
        }
    }
    printf("Sorted Matrix:\n");
    for (int r = 0; r < a; r++) 
    {
        int k = 0;
        while (k < b) 
        {
            printf("%d ", matrix[r][k]);
            k++;
        }
        printf("\n");
    }
    matrixSum(matrix, a, b);
    endingtime = omp_get_wtime();
    printf("Total Execution Time: %f\n",endingtime - startingtime);
    return 0;
}
