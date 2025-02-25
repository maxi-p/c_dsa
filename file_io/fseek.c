#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int id;
    char name[50];
} Person;

int main() {
    FILE *fp;
    int id, found = 0;
    char ch;
    Person buffer;

    fp = fopen("db", "rb+");
    if (fp == NULL) {
        fp = fopen("db", "wb+");
        if (fp == NULL) {
            return 1;
        }
    }

    printf("Enter the id you want to update: ");
    scanf("%d", &id);
    while( (ch = getchar()) != '\n' && ch != EOF);

    printf("Searching...\n");

    fseek(fp, 0, SEEK_SET); // set to beginning
    while(fread(&buffer, sizeof(Person), 1, fp) != 0) {
        if (buffer.id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", buffer.name);
            while ((ch = getchar()) != '\n' && ch != EOF); // consuming the new line
            
            fseek(fp, -sizeof(Person), SEEK_CUR); // moving cursor back to update the found record
            fwrite(&buffer, sizeof(Person), 1, fp);
            break;
        }
    }

    if (found == 1) {
        printf("updated the person with id %d\n", id);
    } else {
        printf("id not found\n");
    }

    fclose(fp);
}