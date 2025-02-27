#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 100
#define RANGE 10000

// O(n^2) runtime array population
// ((1 + n) * n) / 2  = (n^2 + n) / 2 ~ n^2 / 2 ~ n^2
void populateArr(int *arr, int size) {
  srand(time(NULL));

  for (int i = 0; i < size; i++){
    int cur = 0;
    int num = (rand() % RANGE) + 1;

    // finding the right spot to insert
    while (cur < i && arr[cur] <= num) {
      cur++;
    }

    // shifting the old elements
    while (cur <= i) {
      int temp = arr[cur];
      arr[cur] = num;
      num = temp;
      cur++;
    }
  }
}

void printArr(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// [1, 2, 3, 4, 5] - target 4

// [1, 2, 4, 5] - target 5

// search index in array arr. If not found then -1
int search(int *arr, int target, int size) {
  int res = -1;
  int l = 0, r = size - 1, m = 0;

  while (l <= r) {
    m = (l + r) / 2; // int division
    if (arr[m] == target) {
      return m;
    } else if (arr[m] > target){
      r = m - 1;
    } else {
      // arr[m] < target
      l = m + 1;
    }
  }

  return -1;
}

int main() {
  char c;  int size = SIZE;
  int* arr = (int *) malloc(sizeof(int) * size);
  if (arr == NULL) {
    printf("Could not allocate an array\n");
    exit(1);
  }

  populateArr(arr, size);
  printArr(arr, size);

  int inpt = 0, val = 0;
  while (inpt != -1) {
    printf("Enter number to search (-1 to exit): ");
    scanf("%d", &inpt);
    while ((c = getchar()) != '\n' && c != EOF); // empty buffer
    val = search(arr, inpt, size);
    printf("Value %d is at index: %d\n\n", inpt, val);
  }

  free(arr);
  return 0;
}
