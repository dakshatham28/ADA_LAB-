#include <stdio.h>
#include <stdlib.h>

#define INF 999999

// Structure to represent a graph edge
typedef struct {
    int src, dest, weight;
} Edge;

// Disjoint Set: Find function with path compression
int findSet(int i, int parent[]) {
    int root = i;
    while (parent[root] >= 0) {
        root = parent[root];
    }
    
    // Path compression to keep the tree flat (optimizes future lookups)
    int curr = i;
    while (curr != root) {
        int nxt = parent[curr];
        parent[curr] = root;
        curr = nxt;
    }
    
    return root;
}

// Disjoint Set: Union function
int unionSet(int i, int j, int parent[]) {
    if (i != j) {
        parent[j] = i; // Make root i the parent of root j
        return 1;
    }
    return 0;
}

int main() {
    int n, i, j;

    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Allocate memory for the cost matrix
    int **cost = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        cost[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter cost adjacency matrix (Use 0 for self-loop, and 999999 for infinity/no edge):\n");
    int maxEdges = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j) {
                cost[i][j] = INF;
            }
            // Count unique edges for an undirected graph (upper triangle of matrix)
            if (j > i && cost[i][j] != INF) {
                maxEdges++;
            }
        }
    }

    // Extract all unique edges into an edge list array
    Edge *edges = (Edge *)malloc(maxEdges * sizeof(Edge));
    int edgeCount = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (cost[i][j] != INF) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = cost[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges based on weight using Bubble Sort (simple and effective for lab scales)
    for (i = 0; i < edgeCount - 1; i++) {
        for (j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Allocate and initialize parent array for Union-Find
    int *parent = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        parent[i] = -1; // Each vertex is initially its own isolated root set
    }

    int mincost = 0;
    int edgesSelected = 0;

    printf("\nEdges selected in MST:\n");
    printf("Edge \tWeight\n");

    // Process sorted edges one by one
    for (i = 0; i < edgeCount && edgesSelected < n - 1; i++) {
        int u = findSet(edges[i].src, parent);
        int v = findSet(edges[i].dest, parent);

        // If including this edge does not cause a cycle
        if (unionSet(u, v, parent)) {
            printf("%d - %d \t%d\n", edges[i].src, edges[i].dest, edges[i].weight);
            mincost += edges[i].weight;
            edgesSelected++;
        }
    }

    // Safety fallback for disconnected graph profiles
    if (edgesSelected < n - 1) {
        printf("\nError: The graph is disconnected. Spanning tree impossible.\n");
    } else {
        printf("\nMinimum cost = %d\n", mincost);
    }

    // Free all allocated memories
    for (i = 0; i < n; i++) {
        free(cost[i]);
    }
    free(cost);
    free(edges);
    free(parent);

    return 0;
}
