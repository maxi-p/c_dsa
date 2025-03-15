#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Graph {
    int vertices;
    int graph[MAX_VERTICES][MAX_VERTICES];
};

bool does_path_exist_bfs(int residualGraph[MAX_VERTICES][MAX_VERTICES], int src, int dest, int parent[MAX_VERTICES], int vertices) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = src;
    parent[src] = -1;
    visited[src] = true;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[dest];
}

void initGraph(struct Graph *g, int vertices, int graph[MAX_VERTICES][MAX_VERTICES]) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->graph[i][j] = graph[i][j];
        }
    }
}

int max_flow(struct Graph *g, int source, int sink) {
    int vertices = g->vertices;
    int residualGraph[MAX_VERTICES][MAX_VERTICES];
    int parent[MAX_VERTICES];
    int max_flow = 0;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            residualGraph[i][j] = g->graph[i][j];
        }
    }

    while (does_path_exist_bfs(residualGraph, source, sink, parent, vertices)) {
        int flow_capacity = INT_MAX;
        int t = sink;
        while (t != source) {
            int s = parent[t];
            flow_capacity = (flow_capacity < residualGraph[s][t]) ? flow_capacity : residualGraph[s][t];
            t = s;
        }

        t = sink;
        while (t != source) {
            int s = parent[t];
            residualGraph[s][t] -= flow_capacity;
            residualGraph[t][s] += flow_capacity;
            t = s;
        }

        max_flow += flow_capacity;
    }

    return max_flow;
}

int main() {
    int vertices = 6;
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 10, 8, 0, 0, 0},
        {0, 0, 5, 5, 0, 0},
        {0, 4, 0, 0, 10, 0},
        {0, 0, 9, 0, 10, 3},
        {0, 0, 0, 6, 0, 14},
        {0, 0, 0, 0, 0, 0}
    };

    struct Graph g;
    initGraph(&g, vertices, graph);

    int source = 0;
    int destination = 5;

    int flow = max_flow(&g, source, destination);

    printf("Maximum flow from source: %d to destination: %d is: %d\n", source, destination, flow);

    return 0;
}
