#include <stdio.h>
#include <stdlib.h>

// Utility function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack using Dynamic Programming
void knapsack(int W, int weights[], int values[], int n) {
    int i, w;
    
    // Allocate memory for the 2D DP table: (n+1) rows x (W+1) columns
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    // Build the DP table in a bottom-up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base Case: No items or 0 capacity
            } else if (weights[i - 1] <= w) {
                // Max of: including the item OR excluding the item
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], 
                               dp[i - 1][w]);
            } else {
                // Weight of item is more than capacity, exclude it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right corner stores the maximum profit
    int max_value = dp[n][W];
    printf("\nMaximum Value in Knapsack = %d\n", max_value);

    // --- Backtracking Step: Find which items were selected ---
    printf("Items selected (1-indexed): ");
    w = W;
    for (i = n; i > 0 && max_value > 0; i--) {
        // If the value came from the row above, the item wasn't included
        if (dp[i][w] == dp[i - 1][w]) {
            continue;
        } else {
            // Item was included
            printf("%d ", i);
            
            // Deduct the item's value and weight from remaining capacities
            max_value -= values[i - 1];
            w -= weights[i - 1];
        }
    }
    printf("\n");

    // Free dynamically allocated memory
    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

int main() {
    int n, W;

    printf("Enter the number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of items.\n");
        return 1;
    }

    int *values = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));

    printf("Enter the values of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    printf("Enter the weights of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter the maximum capacity of the knapsack: ");
    scanf("%d", &W);

    if (W <= 0) {
        printf("Invalid knapsack capacity.\n");
        free(values);
        free(weights);
        return 1;
    }

    knapsack(W, weights, values, n);

    // Free resources
    free(values);
    free(weights);

    return 0;
}
