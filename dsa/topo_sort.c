#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int V;
    int **adj;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adj = (int**)malloc(V * sizeof(int*));

    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int*)calloc(V, sizeof(int));
    }
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    graph->adj[u][v] = 1;
}

void topologicalSort(struct Graph* graph) {
    int V = graph->V;
    int *inDegree = (int*)calloc(V, sizeof(int));
    int *queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;

    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph->adj[u][v]) {
                inDegree[v]++;
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int count = 0;

    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);
        count++;

        for (int v = 0; v < V; v++) {
            if (graph->adj[u][v]) {
                inDegree[v]--;

                if (inDegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (count != V) {
        printf("\ncycle detected\n");
    } else {
        printf("\ntopological sort completed\n");
    }

    free(inDegree);
    free(queue);
}

int main() {
    int V = 6;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);

    for (int i = 0; i < V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);

    return 0;
}
