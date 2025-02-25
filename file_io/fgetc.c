#include<stdio.h>

int main() {
    FILE *fp, *fp_out;
    char ch;

    fp = fopen("in.txt", "a+");
    fp_out = fopen("out.txt", "w");

    if (fp == NULL || fp_out == NULL) { return 1; }

    // r opens for reading
    // w creates a file for for writing. Will replace file if exists
    // a appends to a file
    // r+ open a file for read/write. File must exist
    // w+ creates a file for read/write. Creates and truncates file. Data will be lost if exists.
    // a+ appends or creates new file. Will be created if doesn't exist

    fseek(fp, 0, SEEK_SET);

    while (!feof(fp)) {
        ch = fgetc(fp);
        
        if (ch != EOF) {
            printf("%c", ch);
            fputc(ch, fp_out);
        }
    }

    if (fclose(fp) != 0) { return 1; } 
    if (fclose(fp_out) != 0) { return 1; } 
    return 0;
}