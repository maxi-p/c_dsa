#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct empl {
    int id;
    char name[20];
    double salary;
};

typedef struct {
    int id;
    char *name;
} Book;

int main() {
    struct empl maxi, *dynamicEmpl;

    maxi.id = 1;
    strcpy(maxi.name, "Maxi");
    maxi.salary = 120000;

    dynamicEmpl = (struct empl*) malloc(sizeof(struct empl));
    dynamicEmpl->id = 2;
    strcpy(dynamicEmpl->name, "asd");
    dynamicEmpl->salary = 100000;

    printf("ID: %d, name: %s, sal: %lf\n", maxi.id, maxi.name, maxi.salary);
    printf("ID: %d, name: %s, sal: %lf\n", (*dynamicEmpl).id, (*dynamicEmpl).name, (*dynamicEmpl).salary);

    Book book1 = { 1, "C programming" };
    Book *book2 = (Book *) malloc(sizeof(Book));

    book2->id = 2;
    book2->name = (char *) malloc(sizeof(char) * 5);
    strcpy(book2->name, "java");
    book2->name[4] = '\0';

    printf("id: %d, name: %s\n", book1.id, book1.name);
    printf("id: %d, name: %s\n", book2->id, book2->name);


    free(book2->name);
    free(book2);
    free(dynamicEmpl);

    return 0;
}