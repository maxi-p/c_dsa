#include <stdio.h>
#include <stdlib.h>

#define DEGREE 3 // Degree of the B-tree (minimum degree)

typedef struct BTreeNode {
    int *keys;          // Array of keys
    struct BTreeNode **children; // Array of child pointers
    int numKeys;        // Current number of keys
    int isLeaf;         // 1 if leaf node, 0 otherwise
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

// Function to create a new BTree node
BTreeNode* createNode(int isLeaf) {
    BTreeNode *newNode = (BTreeNode*) malloc(sizeof(BTreeNode));
    newNode->keys = (int*) malloc((DEGREE - 1) * sizeof(int));
    newNode->children = (BTreeNode**) malloc(DEGREE * sizeof(BTreeNode*));
    newNode->numKeys = 0;
    newNode->isLeaf = isLeaf;

    return newNode;
}

// Function to split a full node
void splitNode(BTreeNode *parent, int index, BTreeNode *fullNode) {
    BTreeNode *newNode = createNode(fullNode->isLeaf);
    int midKey = fullNode->keys[DEGREE / 2]; // Mid element to be promoted to parent

    // Move the second half of the keys and children to the new node
    newNode->numKeys = DEGREE / 2;
    for (int i = 0; i < DEGREE / 2; i++) {
        newNode->keys[i] = fullNode->keys[i + DEGREE / 2 + 1];
    }
    if (!fullNode->isLeaf) {
        for (int i = 0; i <= DEGREE / 2; i++) {
            newNode->children[i] = fullNode->children[i + DEGREE / 2 + 1];
        }
    }

    fullNode->numKeys = DEGREE / 2;

    // Shift the children of the parent node to make space for the new node
    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newNode;

    // Move the middle key up to the parent
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = midKey;
    parent->numKeys++;
}

// Function to insert a key into a node
void insertNonFull(BTreeNode *node, int key) {
    int i = node->numKeys - 1;

    // If the node is a leaf, insert the key in the correct position
    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        // Find the child that will have the key
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;

        // Check if the child is full
        if (node->children[i]->numKeys == DEGREE - 1) {
            // Split the child before inserting the key
            splitNode(node, i, node->children[i]);

            // After split, the middle key has been promoted to the parent
            if (node->keys[i] < key) {
                i++;
            }
        }
        // Insert the key into the appropriate child
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B-tree
void insert(BTree *tree, int key) {
    // If the root is full, split it
    if (tree->root->numKeys == DEGREE - 1) {
        BTreeNode *newRoot = createNode(0);
        newRoot->children[0] = tree->root;
        tree->root = newRoot;

        splitNode(newRoot, 0, tree->root);
    }

    insertNonFull(tree->root, key);
}

// Function to print the B-tree (for debugging)
void printTree(BTreeNode *node, int level) {
    if (node == NULL) return;

    printf("Level %d: ", level);
    for (int i = 0; i < node->numKeys; i++) {
        printf("%d ", node->keys[i]);
    }
    printf("\n");

    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            printTree(node->children[i], level + 1);
        }
    }
}

// Function to create a new B-tree
BTree* createBTree() {
    BTree *tree = (BTree*) malloc(sizeof(BTree));
    tree->root = createNode(1); // Root is a leaf initially
    return tree;
}

// Driver function to test the B-tree insertion
int main() {
    BTree *tree = createBTree();
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 5);
    insert(tree, 6);
    insert(tree, 12);
    insert(tree, 30);
    insert(tree, 7);
    insert(tree, 17);

    // Print the B-tree
    printTree(tree->root, 0);

    return 0;
}
