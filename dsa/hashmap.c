#include<stdio.h>
#include<stdlib.h>

#define SIZE 7919
#define PRIME 31

typedef struct Node{
  int key;
  int val;
  struct Node *next;
} Node;

int get_hash(int key) {
  return (key * PRIME) % SIZE;
}

void init(Node **hash_table, int size) {
  for (int i = 0; i < size; i++) {
    hash_table[i] = NULL;
  }
}

void destroy(Node **hash_table, int size) {
  for (int i = 0; i < size; i++) {
    Node *tmp;
    while (hash_table[i] != NULL) {
      tmp = hash_table[i];
      hash_table[i] = hash_table[i]->next;
      free(tmp);
    }
  }
}

void put(Node **hash_table, int key, int val) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }
  node->key = key;
  node->val = val;
  node->next = NULL;

  int index = get_hash(key);

  // first element (no collision)
  if (hash_table[index] == NULL) {
    hash_table[index] = node;
    return;
  }

  Node *tmp = hash_table[index], *prev;
  while (tmp != NULL) {
    prev = tmp;
    tmp = tmp->next;
  }

  prev->next = node;
}

int get(Node **hash_table, int key) {
  int index = get_hash(key);
  Node *tmp = hash_table[index];
  while (tmp != NULL) {
    if (tmp->key == key) {
      return tmp->val;
    }
    tmp = tmp->next;
  }
  return -1;
}

int main() {
  Node *hash_table[SIZE];
  init(hash_table, SIZE);

  put(hash_table, 1, 1);
  put(hash_table, 2, 2);
  put(hash_table, 3, 3);
  put(hash_table, 4, 4);
  put(hash_table, 5, 5);
  put(hash_table, 6, 6);
  put(hash_table, 7, 7);
  put(hash_table, 0, 123);
  put(hash_table, 7919, 456);


  printf("Get 5: %d\n", get(hash_table, 5));
  printf("Get 1: %d\n", get(hash_table, 1));
  printf("Get 3: %d\n", get(hash_table, 3));
  printf("Get 8: %d\n", get(hash_table, 8));
  printf("Get 0: %d\n", get(hash_table, 0));
  printf("Get 7919: %d\n", get(hash_table, 7919));

  destroy(hash_table, SIZE);
  return 0;
}
