#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define STR 20
#define SIZE 100

void genr_rand_str(char* dest, int size) {
  char *rand_str = (char *) malloc(sizeof(char) * size);
  if (rand_str == NULL) {
    printf("Could not allocate space\n");
    exit(1);
  }

  for (int i = 0; i < size - 1; i++) {
    char rand_char = (char)((rand() % 26) + 97);
    rand_str[i] = rand_char;
  }
  rand_str[size] = '\0';

  strcpy(dest, rand_str);
  free(rand_str);
}

void init_arr(char ** arr, int size, int str_size) {
  char* gend_str = (char *) malloc(sizeof(char) * str_size);
  char* temp = (char *) malloc(sizeof(char) * str_size);
  if (gend_str == NULL || temp == NULL) {
    printf("Could not allocate memory\n");
    exit(1);
  }

  for (int i = 0; i < size; i++) {
    int count = 0;
    // put new str in gend_str
    genr_rand_str(gend_str, str_size);

    while (count < i && strcmp(arr[count], gend_str) < 0 ) {
      count++;
    }

    while (count <= i) {
      strcpy(temp, arr[count]);
      strcpy(arr[count], gend_str);
      strcpy(gend_str, temp);
      count++;
    }
  }

  free(gend_str);
  free(temp);
}

int search(char** arr, char* target, int size) {
  int l = 0, r = size - 1;
  while(l <= r) {
    int m = (l + r) / 2; // int division
    int cmp = strcmp(arr[m], target);
    if (cmp == 0) {
      return m;
    } else if (cmp < 0) {
      l = m + 1;
    } else {
      // (cmp > 0)
      r = m - 1;
    }
  }
  return -1;
}

int main() {
  int size = SIZE;
  int str_size = STR;
  char* dict[SIZE];

  srand(time(NULL)); // generating seed for "random" nums

  for (int i = 0; i < size; i++) {
    dict[i] = (char *) malloc(sizeof(char) * STR);
    if (dict[i] == NULL) {
      printf("Error allocation space for a string\n");
      exit(1);
    }
  }

  init_arr(dict, size, str_size);

  for (int i = 0; i < size; i++) {
    printf("%d: %s\n", i,  dict[i]);
  }

  int val = 0;
  char buffer[STR] = "";
  while (strcmp(buffer, "-1") != 0) {
    printf("Enter string (-1 to exit): ");
    scanf("%19[^\n]s", buffer);
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("String %s is at index %d\n",
      buffer, search(dict, buffer, size));
  }

  for (int i = 0; i < size; i++) {
    free(dict[i]);
  }

  return 0;
}
