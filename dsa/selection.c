#include <stdio.h>

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void selectionSort(int arr[], int n) {
	int i, j, min_idx, temp;
	for (i = 0; i < n-1; i++) {
		min_idx = i;
		for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

		temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;

		printArray(arr, n);
	}
}


int main() {
    int arr[] = { 5,	8,	3,	1,	4,	7,	6,	2};
    int n = 8;

    printArray(arr, n);
    selectionSort(arr, n);
    printArray(arr, n);

    return 0;
}
