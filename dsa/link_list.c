#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
  int val;
  struct Node *next;
} Node;

// run free on all nodes
int freeNodes(Node* root) {
  Node *tmp;
  while (root != NULL) {
    tmp = root;
    root = root->next;
    free(tmp);
  }

  return 0;
}

Node *insertAfter(Node* root, int val, int after) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->val = val;
  node->next = NULL;

  // first insertion
  if (root == NULL) { return node; }

  Node *tmp = root, *prev = NULL;
  while (tmp && tmp->val != after) {
    prev = tmp;
    tmp = tmp->next;
  }

  // not found the "after" value
  if (tmp == NULL) {
    prev->next = node;
  } else {
    node->next = tmp->next;
    tmp->next = node;
  }

  return root;
}

void displayList(Node* root) {
  if (root == NULL) { return; }
  while (root != NULL) {
    printf("%d ", root->val);
    root = root->next;
  }
  printf("\n");
}

Node *insert(Node *root, int val) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node == NULL) { return root; }

  node->val = val;
  node->next = NULL;

  Node *tmp = root, *prev = NULL;
  while (tmp != NULL) {
    prev = tmp;
    tmp = tmp->next;
  }

  if (prev == NULL) {
    root = node;
    return root;
  }

  prev->next = node;

  return root;
}

Node *delete(Node *root, int val) {
  // empty list edge case
  if (root == NULL) { return root; }

  Node *tmp = root, *prev = NULL;

  // deleting the root node
  if (root->val == val) {
    tmp = root;
    root = root->next;
    free(tmp);
    return root;
  }

  while (tmp && tmp->val != val) {
    prev = tmp;
    tmp = tmp->next;
  }

  // node not found
  if (tmp == NULL) {
    printf("Node with val %d not found\n", val);
    return root;
  }

  prev->next = tmp->next;
  free(tmp);

  return root;
}

int main() {
  Node *root = NULL;

  root = delete(root, 6);
  displayList(root);

  if ((root = insert(root, 1)) == NULL) { return 1; }
  if ((root = insert(root, 2)) == NULL) { return 1; }
  if ((root = insert(root, 3)) == NULL) { return 1; }
  if ((root = insert(root, 4)) == NULL) { return 1; }
  if ((root = insert(root, 5)) == NULL) { return 1; }
  if ((root = insert(root, 6)) == NULL) { return 1; }

  displayList(root);

  if ((root = delete(root, 6)) == NULL) { return 1; }
  displayList(root);

  if ((root = delete(root, 1)) == NULL) { return 1; }
  displayList(root);

  if ((root = delete(root, 4)) == NULL) { return 1; }
  displayList(root);

  insertAfter(root, 23, 2);
  displayList(root);

  insertAfter(root, 30, 3);
  displayList(root);

  insertAfter(root, 10, 23);
  displayList(root);


  if (freeNodes(root) != 0) { return 1; }

  return 0;
}
