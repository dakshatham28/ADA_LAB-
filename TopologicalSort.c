#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int main() {
    int n, i, j;
    int adj[MAX][MAX];    // Adjacency matrix
    int indegree[MAX];    // Array to store indegrees
    int queue[MAX];       // Custom queue for processing nodes
    int front = 0, rear = 0;
    int topo_order[MAX];  // Array to store the final topological sequence
    int count = 0;

    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Initialize indegrees to 0
    for (i = 0; i < n; i++) {
        indegree[i] = 0;
    }

    printf("Enter adjacency matrix (0 or 1):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
            // If there is an edge from i to j, increment the indegree of j
            if (adj[i][j] == 1) {
                indegree[j]++;
            }
        }
    }

    // Enqueue all vertices with an initial indegree of 0
    for (i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Process the graph
    while (front < rear) {
        // Dequeue a vertex
        int current = queue[front++];
        topo_order[count++] = current;

        // "Remove" the vertex and update the indegrees of its neighbors
        for (j = 0; j < n; j++) {
            if (adj[current][j] == 1) {
                indegree[j]--;
                
                // If indegree drops to 0, push it to the queue
                if (indegree[j] == 0) {
                    queue[rear++] = j;
                }
            }
        }
    }

    // Cycle detection guardrail
    if (count < n) {
        printf("\nError: The graph contains a cycle! Topological ordering is impossible.\n");
    } else {
        printf("\nTopological Ordering of vertices:\n");
        for (i = 0; i < n; i++) {
            printf("%d ", topo_order[i]);
        }
        printf("\n");
    }

    return 0;
}
