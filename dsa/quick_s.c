#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PRINTLIST 0
#define SIZEOFLIST 2000000
#define RUNQUICK 1


void print(int* numbers, int length) {

    int i;
    for (i = 0; i < length; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int is_sorted(int values[], int low, int high) {
    int i;

    for (i = low; i < high - 1; i++) {
        if (values[i] > values[i + 1]) {
            return 0;
        }
    }

    return 1;
}

void quicksort(int* numbers, int low, int high) {
    if (is_sorted(numbers, low, high)) { 
        return; 
    }

    int split = partition(numbers, low, high);
    quicksort(numbers, low, split - 1);
    quicksort(numbers, split + 1, high);
}


int partition(int* vals, int low, int high) {
    int temp;
    int i, lowpos;

    i = low + rand() % (high - low + 1);
    swap(&vals[low], &vals[i]);

    lowpos = low;
    low++;

    while (low <= high) {
        while (low <= high && vals[low] <= vals[lowpos]) low++;
        while (high >= low && vals[high] > vals[lowpos]) high--;
        
        if (low < high) {
            swap(&vals[low], &vals[high]);
        }
    }
    swap(&vals[lowpos], &vals[high]);

    return high;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {

    srand(time(0));
    int* list;

    list = (int*)malloc(SIZEOFLIST * sizeof(int));

    int i;
    for (i = 0; i < SIZEOFLIST; i++) {
        list[i] = rand();
    }

    if (PRINTLIST) {
        print(list, SIZEOFLIST);
    }

    int tstart = time(0);
        quicksort(list, 0, SIZEOFLIST - 1);
    int tfinish = time(0);

    if (PRINTLIST) {
        print(list, SIZEOFLIST);
    }

    if (is_sorted(list, 0, SIZEOFLIST - 1)) {
        printf("Sorted correctly.\n");
    }

    printf("Quicksort took %d seconds.\n", tfinish - tstart);

    free(list);
    return 0;
}