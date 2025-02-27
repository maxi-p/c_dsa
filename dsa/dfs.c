#include<stdlib.h>
#include<stdio.h>

#define MAX_NODES 100
#define NODES 10
#define EDGES 9

typedef struct Stack {
  int stack[MAX_NODES];
  int top;
} Stack;

Stack *initStack() {
  Stack *stack = (Stack *) malloc(sizeof(Stack));
  if (stack == NULL) {
    printf("Error creating a stack\n");
    exit(1);
  }
  stack->top = -1;
  return stack;
}

void destroyStack(Stack *st) {
  free(st);
}

void push(Stack *st, int val) {
  if (st->top >= MAX_NODES - 1) {
    printf("Stack overflow\n");
    exit(1);
  }

  st->stack[++st->top] = val;
}

int pop(Stack *st) {
  if (st->top <= -1) {
    printf("Stack underflow\n");
    exit(1);
  }
  return st->stack[st->top--];
}

int peek(Stack *st) {
  if (st->top <= -1) {
    printf("Stack underflow\n");
    exit(1);
  }
  return st->stack[st->top];
}

//    4 5    9
//     3     7
//      0 2 6
//     1
//    8

int main() {
  Stack *st = initStack();
  int graph[NODES][NODES];
  int edge[EDGES][2] = {
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 8},
    {3, 4},
    {2, 6},
    {6, 7},
    {7, 9},
    {4, 5},
  };

  // initialize graph to zero
  for (int i = 0; i < NODES; i++) {
    for (int j = 0; j < NODES; j++) {
      graph[i][j] = 0;
    }
  }

  // convert edge list to adj list
  for (int i = 0; i < EDGES; i++) {
    int from = edge[i][0];
    int to = edge[i][1];
    graph[from][to] = 1;
    graph[to][from] = 1;
  }

  /* for (int i = 0; i < NODES; i++) { */
  /*   for (int j = 0; j < NODES; j++) { */
  /*     printf("%d ", graph[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  int visited[NODES];
  push(st, 0);
  int isLeaf;

  // while stack not empty
  while (st->top > -1) {
    int cur = peek(st);
    if (visited[cur] == 0) {
      printf("%d ", cur);
      visited[cur] = 1;
    }

    isLeaf = 1;

    for (int i = 0; i < NODES; i++) {
      if (graph[cur][i] == 1 && visited[i] != 1) {
        isLeaf = 0;
        push(st, i);
        break;
      }
    }
    if (isLeaf == 1) {
      pop(st);
    }
  }

  printf("\n");

  destroyStack(st);
  return 0;
}
