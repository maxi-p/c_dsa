#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER 100

int main() {
    FILE *fp, *fp_out;
    char str[BUFFER];

    fp = fopen("in.txt", "r+");
    fp_out = fopen("fgets_out.txt", "w");

    if (fp == NULL) { return 1; }
    if (fp_out == NULL) { return 1; }

    while (fgets(str, BUFFER, fp) != NULL) {
        fputs(str, fp_out);
        str[strcspn(str, "\n")] = '\0';
        puts(str);
    }

    if (fclose(fp) != 0) { return 1; }
    if (fclose(fp_out) != 0) { return 1; }

    return 0;
}