#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Partition function (Hoare-style variant)
int partition(int a[], int low, int high) {
    int pivot = a[low];
    int i = low + 1;
    int j = high;
    int temp;

    while (1) {
        while (i <= high && a[i] <= pivot)
            i++;
        while (a[j] > pivot)
            j--;

        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        } else {
            temp = a[low];
            a[low] = a[j];
            a[j] = temp;
            return j;
        }
    }
}

// Quick Sort
void quickSort(int a[], int low, int high) {
    if (low < high) {
        int j = partition(a, low, high);
        quickSort(a, low, j - 1);
        quickSort(a, j + 1, high);
    }
}

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    int sizes[] = {10, 50, 100, 500, 1000, 5000};
    int numSizes = 6;
    int iterations = 1000;

    printf("InputSize\tTime(seconds for %d runs)\n", iterations);
    printf("---------------------------------------------\n");

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        
        // Allocate master array and a worker clone array
        int *master_arr = (int *)malloc(n * sizeof(int));
        int *worker_arr = (int *)malloc(n * sizeof(int));

        // Generate master random numbers
        for (int i = 0; i < n; i++) {
            master_arr[i] = rand() % 1000;
        }

        double total_time = 0.0;

        for (int iter = 0; iter < iterations; iter++) {
            // 1. Reset the worker array with the original unsorted data
            for (int i = 0; i < n; i++) {
                worker_arr[i] = master_arr[i];
            }

            // 2. Time ONLY the sorting execution
            clock_t start = clock();
            quickSort(worker_arr, 0, n - 1);
            clock_t end = clock();

            // 3. Accumulate elapsed time
            total_time += (double)(end - start) / CLOCKS_PER_SEC;
        }

        printf("%d\t\t%f\n", n, total_time);

        free(master_arr);
        free(worker_arr);
    }

    return 0;
}
