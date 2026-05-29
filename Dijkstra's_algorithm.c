#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 999999

// Function to find the vertex with the minimum distance value,
// from the set of vertices not yet processed
int minDistance(int dist[], bool visited[], int n) {
    int min = INF, min_index = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to recursively print the path from source to a given vertex
void printPath(int parent[], int j) {
    // Base Case: If j is source (parent is -1)
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function that implements Dijkstra's single source shortest path algorithm
void dijkstra(int **graph, int n, int src) {
    int *dist = (int *)malloc(n * sizeof(int));
    bool *visited = (bool *)malloc(n * sizeof(bool));
    int *parent = (int *)malloc(n * sizeof(int));

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1; 
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of unvisited vertices
        int u = minDistance(dist, visited, n);

        if (u == -1) break; // Remaining nodes are unreachable

        // Mark the picked vertex as processed
        visited[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++) {
            // Update dist[v] only if it's not visited, there is an edge,
            // and total weight of path from src to v through u is smaller than current dist[v]
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the calculated shortest distances and paths
    printf("\nShortest Paths from Source Vertex %d:\n", src);
    printf("Destination\tDistance\tPath\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t", i);
        if (dist[i] == INF) {
            printf("INF\t\tNo Path\n");
        } else {
            printf("%d\t\t", dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }

    // Free tracking memory blocks
    free(dist);
    free(visited);
    free(parent);
}

int main() {
    int n, src, i, j;

    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Dynamically allocate the 2D graph cost matrix
    int **graph = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter cost adjacency matrix (Use 0 for self-loop, and 999999 for infinity/no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    printf("Enter the source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    if (src < 0 || src >= n) {
        printf("Invalid source vertex.\n");
        // Cleanup before exit
        for (i = 0; i < n; i++) free(graph[i]);
        free(graph);
        return 1;
    }

    dijkstra(graph, n, src);

    // Free the dynamically allocated graph matrix
    for (i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
