#include <math.h>
#include <stdio.h>

void insertionSort(int arr[], int n) {
    int i, item, j;
    for (i = 1; i < n; i++) {
        item = arr[i];
        for(j=i-1; j>=0; j--) {
            if(arr[j]>item) {
                arr[j+1] = arr[j];
            }
            else {
                break;
            }
        }
        
        arr[j+1] = item;
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = 5;
    printf("before sorting: ");
    printArray(arr, n);

    insertionSort(arr, n);
    printf("\nafter sorting: ");
    printArray(arr, n);

    return 0;
}
