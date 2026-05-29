#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 999999

// Function to find the vertex with the minimum key value, 
// from the set of vertices not yet included in the MST
int minKey(int key[], bool in_mst[], int n) {
    int min = INF, min_index = -1;

    for (int v = 0; v < n; v++) {
        if (!in_mst[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to construct and print MST using Prim's algorithm
void primMST(int **graph, int n) {
    // Array to store constructed MST structure
    int *parent = (int *)malloc(n * sizeof(int));
    // Key values used to pick minimum weight edge in cut
    int *key = (int *)malloc(n * sizeof(int));
    // To represent set of vertices included in MST
    bool *in_mst = (bool *)malloc(n * sizeof(bool));

    // Initialize all keys as INFINITE and in_mst[] as false
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        in_mst[i] = false;
    }

    // Always include the first vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked first
    parent[0] = -1; // First node is always the root of MST

    // The MST will have exactly n vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, in_mst, n);

        // If u == -1, the graph is disconnected
        if (u == -1) {
            printf("\nError: The graph is disconnected. Spanning tree impossible.\n");
            free(parent); free(key); free(in_mst);
            return;
        }

        // Add the picked vertex to the MST Set
        in_mst[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < n; v++) {
            // graph[u][v] is non-zero only for adjacent vertices of m
            // cost[u][v] should be smaller than current key[v]
            if (graph[u][v] != INF && !in_mst[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    int mincost = 0;
    printf("\nEdges selected in MST:\n");
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        mincost += graph[i][parent[i]];
    }
    
    printf("\nMinimum cost = %d\n", mincost);

    // Clean up local tracking arrays
    free(parent);
    free(key);
    free(in_mst);
}

int main() {
    int n, i, j;

    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Dynamically allocate 2D array for cost matrix
    int **graph = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter cost adjacency matrix (Use 0 for self-loop, and 999999 for infinity/no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            // Safeguard: If no direct edge exists, make it infinity
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    primMST(graph, n);

    // Free the dynamically allocated graph matrix
    for (i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
