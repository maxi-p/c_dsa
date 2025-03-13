#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct avlnode {
    int data;
    struct avlnode* left;
    struct avlnode* right;
    int height;
} avlnode;

void checkTree(avlnode* root);
void preorder(avlnode* root);
void postorder(avlnode* root);

avlnode* makeNewNode(int val);
int max(int a, int b);
int isLeafNode(avlnode* root);
int hasTwoChildren(avlnode* root);
avlnode* maxLeft(avlnode* root);
void freeTree(avlnode* root);


void updateHeight(avlnode* root);
avlnode* rebalance(avlnode* root);

avlnode* insert(avlnode* root, int value);
int search(avlnode* root, int value);

avlnode* delValue(avlnode* root, int value);
avlnode* findDelPtr(avlnode* root, int value);
avlnode* del(avlnode* root, avlnode* ptrDel) ;

void smallinsert();
void manyinsertsbadcase();
void smalldel();
void manyinsertsanddeletesbadcase();

int main(void) {
    manyinsertsanddeletesbadcase();
    return 0;
}

void smallinsert() {

    avlnode* tree = NULL;

    tree = insert(tree, 5);
    tree = insert(tree, 1);
    tree = insert(tree, 3);
    checkTree(tree);

    tree = insert(tree, 7);
    tree = insert(tree, 4);
    tree = insert(tree, 6);
    checkTree(tree);

    tree = insert(tree, 20);
    tree = insert(tree, 13);
    tree = insert(tree, 30);
    tree = insert(tree, 10);
    checkTree(tree);

    tree = insert(tree, 25);
    checkTree(tree);

    tree = insert(tree, 27);
    checkTree(tree);

    freeTree(tree);
}

void smalldel() {
    avlnode* tree = NULL;

    tree = insert(tree, 10);
    tree = insert(tree, 5);
    tree = insert(tree, 15);
    tree = insert(tree, 13);
    tree = insert(tree, 17);
    checkTree(tree);

    tree = delValue(tree, 10);
    checkTree(tree);

    tree = insert(tree, 16);
    tree = insert(tree, 40);
    tree = insert(tree, 26);
    checkTree(tree);

    tree = delValue(tree, 5);
    checkTree(tree);

    tree = insert(tree, 60);
    tree = insert(tree, 14);
    tree = insert(tree, 21);
    tree = insert(tree, 30);
    tree = insert(tree, 50);
    tree = insert(tree, 70);
    tree = insert(tree, 19);
    tree = insert(tree, 28);
    tree = insert(tree, 35);
    checkTree(tree);

    tree = delValue(tree, 16);
    checkTree(tree);

    freeTree(tree);
}

void manyinsertsbadcase() {
    avlnode* tree = NULL;

    for (int i=2; i<=2000000; i+=2) {
      tree = insert(tree, i);
    }

    for (int i=1; i<=2000000; i++) {
        int res = search(tree, i);
        if (res + i%2 != 1) {
          printf("error on search for %d\n", i);
        }
    }
    freeTree(tree);
}

void manyinsertsanddeletesbadcase() {
    avlnode* tree = NULL;

    for (int i=2; i<=2000000; i+=2) {
      tree = insert(tree, i);
    }

    for (int i=1; i<=2000000; i++) {
        int res = search(tree, i);
        if (res + i%2 != 1) {
          printf("Error on search for %d\n", i);
        }
    }

    for (int i=2000000; i>=10; i-=2) {
      tree = delValue(tree, i);
    }
    checkTree(tree);
    freeTree(tree);
}

avlnode* insert(avlnode* root, int value) {
    if (root == NULL) {
      return makeNewNode(value);
    }

    if (value < root->data) {
      root->left = insert(root->left, value);
    } else {
      root->right = insert(root->right, value);
    }
    root = rebalance(root);
    updateHeight(root);
    return root;
}

void updateHeight(avlnode* root) {
    if (root == NULL) {
      return;
    }

    int leftH = root->left == NULL ? -1 : root->left->height;
    int rightH = root->right == NULL ? -1 : root->right->height;
    root->height = 1 + max(leftH, rightH);
}

int max(int a, int b) {
    return a > b ? a : b;
}

avlnode* makeNewNode(int val) {
    avlnode* tmp = malloc(sizeof(avlnode));
    tmp->data = val;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 0;
    return tmp;
}

avlnode* rebalance(avlnode* root) {
    if (root == NULL) {
      return NULL;
    }

    int leftH = root->left == NULL ? -1 : root->left->height;
    int rightH = root->right == NULL ? -1 : root->right->height;

    if (abs(leftH-rightH) <= 1) {
      return root;
    }

    avlnode* tempA = NULL;
    avlnode* tempB = NULL;
    avlnode* tempC = NULL;
    avlnode* subT0 = NULL;
    avlnode* subT1 = NULL;
    avlnode* subT2 = NULL;
    avlnode* subT3 = NULL;

    if (leftH > rightH) {
        int leftLeftH = root->left->left == NULL ? -1 : root->left->left->height;
        int leftRightH = root->left->right == NULL ? -1 : root->left->right->height;

        if (leftLeftH >= leftRightH) {
            tempC = root;
            tempB = root->left;
            tempA = root->left->left;
            subT1 = tempA->right;
            subT2 = tempB->right;
        } else {
            tempA = root->left;
            tempB = root->left->right;
            tempC = root;
            subT1 = tempB->left;
            subT2 = tempB->right;
        }
    } else {
        int rightLeftH = root->right->left == NULL ? -1 : root->right->left->height;
        int rightRightH = root->right->right == NULL ? -1 : root->right->right->height;

        if (rightLeftH > rightRightH) {
            tempA = root;
            tempB = root->right->left;
            tempC = root->right;
            subT1 = tempB->left;
            subT2 = tempB->right;
        } else {
            tempA = root;
            tempB = root->right;
            tempC = root->right->right;
            subT1 = tempB->left;
            subT2 = tempC->left;
        }
    }

    subT0 = tempA->left;
    subT3 = tempC->right;

    tempB->left = tempA;
    tempB->right = tempC;

    tempA->left = subT0;
    tempA->right = subT1;
    tempC->left = subT2;
    tempC->right = subT3;

    updateHeight(tempA);
    updateHeight(tempC);
    updateHeight(tempB);

    return root;
}

void checkTree(avlnode* root) {
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n\n");
}

void preorder(avlnode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(avlnode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(avlnode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int search(avlnode* root, int value) {
    if (root == NULL) {
      return 0;
    }

    if (value < root->data) {
      return search(root->left, value);
    } else if (value > root->data) {
      return search(root->right, value);
    } else {
      return 1;
    }
}

int hasTwoChildren(avlnode* root) {
    return root->left != NULL && root->right != NULL;
}

int isLeafNode(avlnode* root) {
    return root->left == NULL && root->right == NULL;
}

avlnode* maxLeft(avlnode* root) {
    avlnode* tmp = root->left;

    while (tmp->right != NULL) {
      tmp = tmp->right;
    }

    return tmp;
}

avlnode* delValue(avlnode* root, int value) {
    avlnode* gone = findDelPtr(root, value);

    if (gone == NULL) {
      return root;
    }

    return del(root, gone);
}

avlnode* findDelPtr(avlnode* root, int value) {
    if (root == NULL) {
      return NULL;
    }

    if (value < root->data) {
      return findDelPtr(root->left, value);
    } else if (value > root->data) {
      return findDelPtr(root->right, value);
    } else {
      return root;
    }
}

avlnode* del(avlnode* root, avlnode* ptrDel) {
    if (root == NULL) {
      return NULL;
    }

    int delVal = ptrDel->data;

    if (root == ptrDel) {
        if (isLeafNode(ptrDel)) {
            free(ptrDel);
            return NULL;
        } else if (hasTwoChildren(ptrDel)) {
            avlnode* tmp = maxLeft(ptrDel);

            int saveVal = tmp->data;
            ptrDel->left = del(ptrDel->left, tmp);
            ptrDel->data = saveVal;

            ptrDel = rebalance(ptrDel);
            updateHeight(ptrDel);

            return ptrDel;
        } else {
            avlnode* retVal = root->left != NULL ? root->left : root->right;
            free(root);

            return retVal;
        }
    }

    if (delVal < root->data) {
      root->left = del(root->left, ptrDel);
    } else {
      root->right = del(root->right, ptrDel);
    }

    root = rebalance(root);
    updateHeight(root);

    return root;
}
