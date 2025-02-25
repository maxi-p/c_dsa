#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100

int main() {
    int size = SIZE;

    char *str1;
    char *str2;

    str1 = (char *) malloc(sizeof(char) * size);
    str2 = (char *) malloc(sizeof(char) * size);

    // str1 = "Hello w"; // MISTAKE
    strcpy(str1, "Hello w");
    strcpy(str2, "Hi there");

    printf("%s\n", str1);
    printf("%s\n", strcat(str1, str2));

    char* substr = strstr(str1, "w");
    printf("Found substr: %s\n", substr);

    int index = strcspn(str1, "iw");
    printf("Index: %d, substr: %s\n", index, str1 + index);

    printf("Equal \"hello\" and \"hello\": %d\n", strcmp("hello", "hello"));
    printf("Equal \"hellb\" and \"hella\" (positive): %d\n", strcmp("hellc", "hella"));
    printf("Equal \"hella\" and \"hellb\" (negative): %d\n", strcmp("hella", "hellc"));

    free(str1);
    free(str2);
}