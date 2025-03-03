#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *) malloc(5 * sizeof(int));
    
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    // either resizes up or down the original memory
    // the original contents won't be touched
    int *new_arr = (int *) realloc(arr, 10 * sizeof(int));

    if (new_arr == NULL) {
        // if fails, returns NULL and original pointer is untouched
        free(arr);
        return 1;
    }

    for (int i = 5; i < 10; i++) {
        new_arr[i] = i + 1;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", new_arr[i]);
    }

    free(new_arr);
    return 0;
}
