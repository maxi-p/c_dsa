#include<stdio.h>
#include<stdlib.h>

#define SIZE 7919
#define PRIME 31

typedef struct Node{
  char key;
  int val;
  struct Node *next;
} Node;

int get_hash(char key) {
  return ((int)key * PRIME) % SIZE;
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

void put(Node **hash_table, char key, int val) {
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

int get(Node **hash_table, char key) {
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

  put(hash_table, 'a', 1);
  put(hash_table, 'b', 2);
  put(hash_table, 'c', 3);
  put(hash_table, 'd', 4);
  put(hash_table, 'e', 5);
  put(hash_table, 'f', 6);
  put(hash_table, 'g', 7);
  put(hash_table, 'h', 123);
  put(hash_table, 'i' , 456);


  printf("Get h: %d\n", get(hash_table, 'h'));
  printf("Get a: %d\n", get(hash_table, 'a'));
  printf("Get b: %d\n", get(hash_table, 'b'));

  destroy(hash_table, SIZE);
  return 0;
}
