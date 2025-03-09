#include <stdio.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n) {
   int i, j,temp;
   for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
           if (arr[j] > arr[j+1]) {
             temp=arr[j];
             arr[j]=arr[j+1];
             arr[j+1]=temp;
           }
           printArray(arr, n);
        }

    }
}

void printArray(int arr[], int size) {
    int i;
    for (i=0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5,1,4,2,8};
    int n = 5;

    printf("bofore sorting: \n");
    printArray(arr, n);

    bubbleSort(arr, n);
    printf("sorted array: \n");
    printArray(arr, n);
    return 0;
}
