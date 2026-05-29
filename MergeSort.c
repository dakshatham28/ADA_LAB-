#include <stdio.h>
#include <stdlib.h> // Required for malloc and free
#include <time.h>

// Merge function using dynamic allocation to prevent stack overflow
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Dynamically allocate memory on the heap
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Check if memory allocation was successful
    if (L == NULL || R == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];

    // Always free dynamically allocated memory
    free(L);
    free(R);
}

// Merge Sort function
void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        // Prevents integer overflow bug
        int m = l + (r - l) / 2; 

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    int n, i;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    // Dynamically allocate the main array based on user input
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed for main array.\n");
        return 1;
    }

    printf("Enter elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Start time
    clock_t start = clock();

    mergeSort(arr, 0, n - 1);

    // End time
    clock_t end = clock();

    // Display sorted array
    printf("Sorted array:\n");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // Time taken
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);

    // Clean up main array memory
    free(arr);

    return 0;
}
