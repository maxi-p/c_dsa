
#include<stdio.h>
#include<stdlib.h>

#define MAX_NODES 100
#define NUM_NODES 10

typedef struct Node {
  int val;
  int adj[MAX_NODES];
} Node;

typedef struct Queue {
  int queue[MAX_NODES];
  int front;
  int size;
} Queue;

void queueInit(Queue *q) {
  if (q == NULL) {
    printf("Error, no queue\n");
    return;
  }
  q->front = 0;
  q->size = 0;
}

int size(Queue *q) {
  return q->size;
}

void enQueue(Queue *q, int val) {
  if (q->size >= MAX_NODES) {
    printf("Queue overflow error\n");
    return;
  }
  int index = (q->front + q->size++) % MAX_NODES;
  q->queue[index] = val;
}

int deQueue(Queue *q) {
  if (q->size <= 0) {
    printf("Queue underflow error\n");
    return -1;
  }
  int val = q->queue[q->front];
  q->front = (q->front + 1) % MAX_NODES;
  q->size -= 1;
  return val;
}

int queuePeek(Queue *q) {
  if (q->size <= 0) {
    printf("Queue underflow error\n");
    return -1;
  }
  int val = q->queue[q->front];
  return val;
}

Node *initGraph(int num_nodes) {
  Node *graph = (Node *) malloc(sizeof(Node) * num_nodes);
  if (graph == NULL) {
    printf("Error allocating\n");
    return NULL;
  }
  for (int i = 0; i < num_nodes; i++) {
    graph[i].val = i;
  }
  return graph;
}

void toAdjList(Node* graph, int edges[][2], int num_edges) {
  for (int i = 0; i < num_edges; i++) {
    int from = edges[i][0];
    int to = edges[i][1];

    graph[from].adj[to] = 1;
    graph[to].adj[from] = 1;
  }
}

// 9
//  7    6
//    0
//  4   2
// 8    1  5
//      3

// answer (bfs): 0 2 4 6 7 1 8 9 6 3 5
int main() {
  int num_nodes = NUM_NODES;
  int edges[][2] = {
    {0, 4},
    {0, 2},
    {1, 2},
    {1, 3},
    {1, 5},
    {4, 8},
    {0, 7},
    {0, 6},
    {7, 9}
  };
  Node *graph = initGraph(num_nodes);
  toAdjList(graph, edges, sizeof(edges)/sizeof(int[2]));

  int visited[NUM_NODES] = {0, 0, 0, 0, 0};
  Queue q;
  queueInit(&q);
  visited[0] = 1;
  enQueue(&q, 0);
  while (size(&q) > 0) {
    int curNode = deQueue(&q);
    printf("%d - ", curNode);
    for (int i = 0; i < MAX_NODES; i++) {
      if (graph[curNode].adj[i] == 1 && visited[i] == 0) {
        visited[i] = 1;
        enQueue(&q, i);
      }
    }
  }
  printf("\n");

  return 0;
}
