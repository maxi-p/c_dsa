#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t buffer_size = 5; // initial buffer size
    char input_string[5];
    char *dynamic_string;

    printf("Enter a string: ");
    
    // Read input using scanf
    scanf("%4[^\n]", input_string);

    // Null-terminate the string
    input_string[buffer_size] = '\0';

    printf("You entered: %s\n", input_string);
    int len = strlen(input_string);
    dynamic_string = (char*) malloc(sizeof(char) * (len + 1));
    
    strcpy(dynamic_string, input_string);
    // Null-terminate the string
    dynamic_string[len + 1] = '\0';

    printf("The dynamic string: %s of the size: %d\n", dynamic_string, len);

    free(dynamic_string);
    return 0;
}
