#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SIZE 100

typedef struct{
    char stack[SIZE];
    int size;
    int top;
} Stack;

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }
    return 0;  
}

void scanString(Stack *stack, char *str, char *res) {
    int size = strlen(str);
    int i = 0;
    int index = 0;
    while (i < size) {
        if (isalnum(str[i])) {
            res[index++] = str[i];
        } else if (str[i] == '('){
            if (stack->top == SIZE - 1) {
                printf("Stack overflow\n");
                exit(1);
            }
            stack->stack[++stack->top] = '(';
        } else if (str[i] == ')') {
            // pop until find '('
            char cur;
            if (stack->top < 0) {
                printf("Stack underflow\n");
                exit(1);
            }
            cur = stack->stack[stack->top--];
            while (cur != '(' && stack->top >= 0){
                res[index++] = cur;
                cur = stack->stack[stack->top--];
            }
            if (stack->top == -1 && cur != '(') {
                printf("Unopened ()\n");
                exit(1);
            }
        } else {
            // if it's an operator
            while (stack->top >= 0 && precedence(stack->stack[stack->top]) >= precedence(str[i])) {
                res[index++] = stack->stack[stack->top--];
            }
            stack->stack[++stack->top] =  str[i];
        }
        i++;
    }
    
    while (stack->top >= 0) {
        res[index++] = stack->stack[stack->top--];
    }
}

int main() {
    Stack stack = { {}, SIZE, -1 };

    char str[SIZE] = "4*2+3+8/4";
    char res[SIZE];

    scanString(&stack, str, res);
    printf("%s\n", res);

    return 0;
}