#include<stdio.h>
#include<stdlib.h>

void printNum(int i) {
    if (i < 0) {
        return;
    }

    printNum(i - 1);
    printf("%d ", i);
}

int exponent(int base, int i) {
    if (i <= 0) {
        return 1;
    }

    return base * exponent(base, i - 1);
}

int main() {
    printNum(10);
    printf("\n");

    printf("5^3 = %d\n", exponent(5, 3));
    printf("6^2 = %d\n", exponent(6, 2));
    return 0;
}