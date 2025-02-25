#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int id;
    char name[50];
} Person;

int main() {
    FILE *fp;
    char ch;

    fp = fopen("db", "rb+");
    if (fp == NULL) {
        fp = fopen("db", "wb+");
    }

    Person buffer;

    // reading all records
    fseek(fp, 0, SEEK_SET); // go to the beginning of the file
    while (fread(&buffer, sizeof(Person), 1, fp)) {
        printf("%d - %s\n", buffer.id, buffer.name);
    }

    // adding 
    
    // get id
    printf("Enter id: ");
    scanf("%d", &buffer.id);
    while ( (ch = getchar()) != '\n' && ch != EOF); // eat the extra new line after scanf
    
    // get name
    printf("Enter name: ");
    scanf("%s", buffer.name);
    
    if (!fwrite(&buffer, sizeof(Person), 1, fp)) { return 1; }
    
    printf("cursor position: %ld\n", ftell(fp)); // ftell(fp) returns the position of the cursor

    // reading all records
    fseek(fp, 0, SEEK_SET); // go to the beginning of the file
    printf("cursor position: %ld\n", ftell(fp));
    while (fread(&buffer, sizeof(Person), 1, fp)) {
        printf("%d - %s\n", buffer.id, buffer.name);
    }

    fclose(fp);
}