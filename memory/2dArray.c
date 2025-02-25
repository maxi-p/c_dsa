#include<stdio.h>
#include<stdlib.h>

#define ROW 3
#define COL 4

struct array2d {
    int **arr;
    int row;
    int col;
};

int dynamicArray(int **A, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", *(*(A + i) + j));
        }
        printf("\n");
    }
    return 0;
}

int static2dArray(int A[][COL], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", *(*(A + i) + j));
        }
        printf("\n");
    }
    return 0;
}

int static2dArray2(int *A, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", *(A + i * col + j));
        }
        printf("\n");
    }
    return 0;
}

int main() {
    int row = ROW;
    int col = COL;
    
    int static2dArr[ROW][COL] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int **multiDimArray;

    // allocating an array of row integer pointers
    multiDimArray = (int **) malloc(sizeof(int *) * row);

    for (int i = 0; i < row; i++) {
        multiDimArray[i] = (int *) malloc(sizeof(int) * col);
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            multiDimArray[i][j] = i * col + j + 1;
        }
    }
    printf("Dynamic multi-dimentsional arrays are different from static ones. They are non-contiguous\n\n");

    printf("Dynamic array:  void print(int **A);\n\n");
    dynamicArray(multiDimArray, row, col);

    printf("\n\nStatic array:  void print(int A[][COL]);\n\n");
    static2dArray(static2dArr, 3, 4);

    printf("\n\nStatic array:  void print(int* A);\n\n");
    static2dArray2(*static2dArr, 3, 4);

    for (int i = 0; i < row; i++) {
        free(multiDimArray[i]);
    }
    free(multiDimArray);

    return 0;
}