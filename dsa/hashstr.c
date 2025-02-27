#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 7919
#define PRIME 31
#define STR 30

typedef struct Node{
  char key[STR];
  int val;
  struct Node *next;
} Node;

int get_hash(char *key) {
  int len = strlen(key);
  int index = 0;
  int base = 1;
  for (int i = 0; i < len; i++) {
    index = (((int) key[i]) * base + index) % SIZE;
    base = (base * PRIME) % SIZE;
  }
  return index;
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

void put(Node **hash_table, char *key, int val) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }
  strcpy(node->key, key);
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

int get(Node **hash_table, char *key) {
  int index = get_hash(key);
  Node *tmp = hash_table[index];
  while (tmp != NULL) {
    if (strcmp(tmp->key, key) == 0) {
      return tmp->val;
    }
    tmp = tmp->next;
  }
  return -1;
}

int main() {
  Node *hash_table[SIZE];
  init(hash_table, SIZE);

  put(hash_table, "abc", 1);
  put(hash_table, "asd", 2);
  put(hash_table, "qwerty", 3);
  put(hash_table, "max", 4);

  printf("Get abc: %d\n", get(hash_table, "abc"));
  printf("Get qwerty: %d\n", get(hash_table, "qwerty"));

  destroy(hash_table, SIZE);
  return 0;
}
