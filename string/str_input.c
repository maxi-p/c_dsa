#include<stdio.h>
#include<string.h>

int main() {
    char s[10] = "cat";
    char *inv = "cat"; // valid but this is const

    char name[20];
    printf("Enter name: ");
    // scanf will skip everything after SPACE
    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Your name is: ");
    puts(name);

    printf("Again, your name: ");
    scanf("%[^\n]", name);

    printf("Your name is: %s\n", name);

    return 0;
}