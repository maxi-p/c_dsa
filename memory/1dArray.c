#include<stdio.h>
#include<stdlib.h>

#define SIZE 3

void dynamicArray(int* A, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(A + i));
    }
    printf("\n");
}

void staticArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(A + i));
    }
    printf("\n");
}

int main() {
    int size = SIZE;
    int staticArr[SIZE] = { 1, 2, 3 };
    int* dynamicArr = NULL;

    dynamicArr = (int *) malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        *(dynamicArr + i) = i + 1;
    }

    printf("Dynamic and static 1d arrays are interchangable");

    printf("\n\nStatic array:  void print(int A[]);\n");
    staticArray(staticArr, size);

    printf("\n\nStatic array:  void print(int* A);\n");
    dynamicArray(dynamicArr, size);

    printf("\n\nDynamic array:  void print(int A[]);\n");
    staticArray(dynamicArr, size);

    printf("\n\nDynamic array:  void print(int *A);\n");
    dynamicArray(staticArr, size);


    free(dynamicArr);

    return 0;
}