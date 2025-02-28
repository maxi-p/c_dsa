#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define CAPACITY 128

typedef struct Heap {
  int heap[CAPACITY];
  int size;
} Heap;

void init(Heap *heap) {
  heap->size = 0;
  for (int i = 0; i < CAPACITY; i++) {
    heap->heap[i] = INT_MAX;
  }
}

int parent(int node) {
  return (node - 1) / 2;
}

int l_child(int node) {
  return node * 2 + 1;
}

int r_child(int node) {
  return node * 2 + 2;
}

int peek(Heap *heap) {
  if (heap->size == 0) {
    return -1;
  }

  return heap->heap[0];
}

void insert(Heap *heap, int val) {
  heap->heap[heap->size] = val;
  int cur = heap->size;
  heap->size += 1;

  // percolate up
  while (cur != 0 &&
    heap->heap[cur] < heap->heap[parent(cur)]) {
    int temp = heap->heap[parent(cur)];
    heap->heap[parent(cur)] = heap->heap[cur];
    heap->heap[cur] = temp;
    cur = parent(cur);
  }
}

int pop(Heap *heap) {
  if (heap->size == 0) {
    return -1;
  }
  int val = heap->heap[0];
  heap->heap[0] = heap->heap[heap->size - 1];
  heap->heap[heap->size - 1] = INT_MAX;
  heap->size -= 1;

  // percolate down
  int cur = 0;
  while (l_child(cur) < heap->size) {
    int l = l_child(cur);
    int r = r_child(cur);
    int smallest = cur;

    if (r < heap->size && heap->heap[r] < heap->heap[l]) {
      smallest = r;
    }
    if (heap->heap[r] >= heap->heap[l]) {
      smallest = l;
    }
    if (smallest == cur) {
      break;
    }

    int temp = heap->heap[cur];
    heap->heap[cur] = heap->heap[smallest];
    heap->heap[smallest] = temp;
    cur = smallest;
  }

  return val;
}

int main() {
  Heap *heap = (Heap *) malloc(sizeof(Heap));
  if (heap == NULL) {
    printf("Cannot allocate\n");
    exit(1);
  }

  init(heap);

  int count = 0, val;
  while (count++ < 5) {
    printf("Enter value to insert: ");
    scanf("%d", &val);
    insert(heap, val);
  }
  printf("\n");

  while (heap->size > 0) {
    printf("Popped: %d\n", pop(heap));
  }

  free(heap);
  return 0;
}
