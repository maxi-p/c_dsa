#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct trie {
    int isWord;
    struct trie* next[26];
};

struct trie* init() {
    struct trie* myTree = malloc(sizeof(struct trie));
    myTree->isWord = 0;

    int i;
    for (i=0; i<26; i++) {
        myTree->next[i] = NULL;
    }

    return myTree;
}

int isEmpty(struct trie* root) {
    for (int i = 0; i < 26; i++) {
        if (root->next[i]) {
            return 0;
        }
    }
    return 1;
}

struct trie* del(struct trie* root, char key[], int k) {
    if (!root) {
        return NULL;
    }
    
    if (k == strlen(key)) {
        if (root->isWord) {
            root->isWord = 0; 
        }
    
        if (isEmpty(root)) {
            free (root);
            root = NULL;
        }
        return root;
    }
    
    int index = key[k] - 'a';
    root->next[index] = del(root->next[index], key, k + 1);
    
    if (isEmpty(root) && root->isWord == 0) {
        free (root);
        root = NULL;
    }
    return root;
}

void insert(struct trie* tree, char word[], int k) {
    if (k == strlen(word)) {
        tree->isWord = 1;
        return;
    }

    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL) {
        tree->next[nextIndex] = init();
    }
    insert(tree->next[nextIndex], word, k+1);
}

int search(struct trie* tree, char word[], int k) {
    if (k == strlen(word)) {
        return tree->isWord;
    }

    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL) {
        return 0;
    }
    return search(tree->next[nextIndex], word, k+1);
}

void freeDictionary(struct trie* tree) {
    int i;
    for (i=0; i<26; i++) {
        if (tree->next[i] != NULL) {
            freeDictionary(tree->next[i]);
        }
    }
    free(tree);
}

void printAll(struct trie* tree, char cur[]) {
    if (tree == NULL) {
        return;
    }

    if (tree->isWord) {
        printf("%s\n", cur);
    }
    
    int len = strlen(cur);
    int i;
    for (i=0; i<26; i++) {
        cur[len] = (char)('a'+i);
        cur[len+1] = '\0';
        printAll(tree->next[i], cur);
    }
}

int main() {
    struct trie* myDictionary = init();
    int i, n;
    FILE* ifp = fopen("dictionary.txt", "r");
    fscanf(ifp, "%d", &n);

    for (i=0; i<n; i++) {
        char word[100];
        fscanf(ifp, "%s", word);
        insert(myDictionary, word, 0);
    }

    char searchKey[100];
    printf("Enter a word to search: ");
    scanf("%s", searchKey);

    if (search(myDictionary, searchKey, 0)){
        printf("Found %s\n", searchKey);
    } else {
        printf("Not found %s\n", searchKey);
    }
    printf("Printing all the words: \n");
    
    char word[100];
    word[0] = '\0';
    printAll(myDictionary, word);
    
    char deleteKey[50];
    printf("Enter a word to remove: ");
    scanf("%s", deleteKey);
    
    myDictionary= del(myDictionary, deleteKey, 0);
    word[0] = '\0';
    
    printAll(myDictionary, word);
    
    fclose(ifp);
    freeDictionary(myDictionary);
    return 0;
}