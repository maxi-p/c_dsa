#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_SIZE 100
#define SIZE 5
#define EDGES 5

int findMin(int *dist, int *visited, int size) {
  int min = INT_MAX, minIndex = 0;

  for (int i = 0; i < size; i++) {
    if (visited[i] == 0 && dist[i] < min) {
      min = dist[i];
      minIndex = i;
    }
  }

  return minIndex;
}

void dijkstra(int** graph, int *dist, int size, int src) {
  for (int i = 0; i < size; i++) {
    dist[i] = INT_MAX;
  }
  dist[src] = 0;

  int *visited = (int *) malloc(sizeof(int) * size);
  if (visited == NULL) {
    printf("Could not allocate\n");
    exit(1);
  }

  for (int i = 0; i < size; i++) {
    visited[i] = 0; // set to not visited
  }

  for (int i = 0; i < size - 1; i++) {
    // equivalent of pop from heap
    int cur = findMin(dist, visited, size);
    visited[cur] = 1;
    for (int j = 0; j < size; j++) {
      if (cur != j &&
          graph[cur][j] != 0 &&
          dist[cur] != INT_MAX &&
          dist[j] > dist[cur] + graph[cur][j]) {
        dist[j] = dist[cur] + graph[cur][j];
      }
    }
  }


  free(visited);
}

//     1
//    0
//  3  2
//         4

int main() {
  int edges[EDGES][3] = {
    {0, 1, 6},
    {0, 2, 2},
    {0, 3, 16},
    {2, 4, 42},
    {0, 4, 45}
  };
  int *graph[SIZE];

  // initialize to 0
  for (int i = 0; i < SIZE; i++) {
    graph[i] = (int *) malloc(sizeof(int) * SIZE);
    if (graph[i] == NULL) {
      printf("Error allocating\n");
      exit(1);
    }

    for (int j = 0; j < SIZE; j++) {
      graph[i][j] = 0;
    }
  }

  for (int i = 0; i < EDGES; i++) {
    int from = edges[i][0];
    int to = edges[i][1];
    graph[from][to] = edges[i][2]; // weight
    graph[to][from] = edges[i][2];
  }

  int *dist = (int *) malloc(sizeof(int) * SIZE);
  if (dist == NULL) {
    printf("Could not allocate\n");
    exit(1);
  }

  dijkstra(graph, dist, SIZE, 0); // src = 0

  for (int i = 0; i < SIZE; i++) {
    printf("%d ", dist[i]);
  }
  printf("\n");

  for (int i = 0; i < SIZE; i++) {
    free(graph[i]);
  }
  free(dist);

  return 0;
}
