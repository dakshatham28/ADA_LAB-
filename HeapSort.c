#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to heapify a subtree rooted with node i
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child = 2*i + 1
    int right = 2 * i + 2; // right child = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main Heap Sort function
void heapSort(int arr[], int n) {
    // Build max heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    // Allocate memory for master and worker arrays
    int *master_arr = (int *)malloc(n * sizeof(int));
    int *worker_arr = (int *)malloc(n * sizeof(int));
    if (master_arr == NULL || worker_arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Generate random values for testing (or you can prompt user for input)
    for (int i = 0; i < n; i++) {
        master_arr[i] = rand() % 10000; 
    }

    // Benchmark setup
    // For large N (e.g., > 10,000), set iterations to 1.
    // For small N, use 1000 to get a measurable clock reading.
    int iterations = (n < 5000) ? 1000 : 1; 
    double total_time = 0.0;

    for (int iter = 0; iter < iterations; iter++) {
        // Restore original unsorted array layout
        for (int i = 0; i < n; i++) {
            worker_arr[i] = master_arr[i];
        }

        // Time ONLY the Heap Sort routine
        clock_t start = clock();
        heapSort(worker_arr, n);
        clock_t end = clock();

        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }

    // Display the sorted results from the final benchmark run
    printf("\nSorted Array (First 20 elements shown for verification):\n");
    for (int i = 0; i < (n < 20 ? n : 20); i++) {
        printf("%d ", worker_arr[i]);
    }
    if (n > 20) printf("... [truncated]");
    printf("\n");

    // Print benchmarking results
    if (iterations > 1) {
        printf("\nTime taken for %d iterations: %f seconds\n", iterations, total_time);
        printf("Average time per sort: %f seconds\n", total_time / iterations);
    } else {
        printf("\nTime taken: %f seconds\n", total_time);
    }

    // Clean up memory
    free(master_arr);
    free(worker_arr);

    return 0;
}
