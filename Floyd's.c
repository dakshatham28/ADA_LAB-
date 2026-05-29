#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define INF 999999 // Representing infinity for unreachable nodes

// Utility function to find the minimum of two values
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function implementing Floyd's Algorithm
void floyd(int dist[MAX][MAX], int n) {
    int i, j, k;

    // k represents the intermediate vertex
    for (k = 0; k < n; k++) {
        // i represents the source vertex
        for (i = 0; i < n; i++) {
            // j represents the destination vertex
            for (j = 0; j < n; j++) {
                // If vertex k can act as a shortcut path from i to j
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    int n, i, j;
    int dist[MAX][MAX];

    printf("Enter number of vertices (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the cost matrix (Use 0 for self-loop, and 999999 for infinity/no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            // Safeguard: Ensure self-loops are explicitly 0 distance
            if (i == j) {
                dist[i][j] = 0;
            }
        }
    }

    // Run the algorithm
    floyd(dist, n);

    // Check for negative-weight cycles
    for (i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            printf("\nWarning: Graph contains a negative-weight cycle! Shortest paths are undefined.\n");
            return 0;
        }
    }

    // Print the final all-pairs shortest path matrix
    printf("\nThe final All-Pairs Shortest Paths matrix is:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                printf("%7s", "INF");
            } else {
                printf("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
