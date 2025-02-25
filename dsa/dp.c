#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int max(int a, int b){
    return (a > b) ? a : b;
}

int lcs(int **cache, char *str1, char *str2, int i, int j) {
    int size1 = strlen(str1);
    int size2 = strlen(str2);

    if (i >= size1 || j >= size2) {
        return 0;
    }

    if (cache[i][j] != -1) {
        return cache[i][j];
    }

    int one, two = 0, three, four;
    // str1: "ab"
    // str2: "cb"

    // skip both
    one = lcs(cache, str1, str2, i + 1, j + 1);

    if (str1[i] == str2[j]) {
        // skip both but we are counting 
        two = 1 + one;
    } 

    // skip first
    three = lcs(cache, str1, str2, i + 1, j);

    // skip second
    four = lcs(cache, str1, str2, i, j + 1);

    two = max(one, two);
    three = max(three, four);
    cache[i][j] = max(two, three);

    return cache[i][j];
}

int main() {
    int** cache;
    char *str1 = "go0000000000odness";
    char *str2 = "go0000000000odmorning";

    cache = (int **) malloc(sizeof(int *) * (strlen(str1) + 1));

    for (int i = 0; i < strlen(str1) + 1; i++) {
        cache[i] = (int *) malloc(sizeof(int) * (strlen(str2) + 1));

        // empty value in cache
        for (int j = 0; j < strlen(str2) + 1; j++) {
            cache[i][j] = -1;
        }
    }

    printf("LCS of %s and %s is: %d\n", str1, str2, lcs(cache, str1, str2, 0, 0));

    for (int i = 0; i < strlen(str1) + 1; i++) {
        free(cache[i]);
    }
    free(cache);
    return 0;
}