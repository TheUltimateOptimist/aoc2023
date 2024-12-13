#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void printDoubleBinary(double value) {
    // Create a pointer to the double
    unsigned long long *ptr = (unsigned long long *)&value;

    // Extract the bits
    unsigned long long bits = *ptr;

    // Print the bits in binary
    printf("Binary representation: ");
    for (int i = 63; i >= 0; i--) {
        printf("%llu", (bits >> i) & 1);
        if (i == 63 || i == 52) {
            printf(" "); // Separate sign, exponent, and fraction
        }
    }
    printf("\n");
}

void raise(char *message) {
    printf("%s\n", message);
    exit(1);
}

int main() {
    // double *da = malloc(sizeof(double));
    // char **sa = malloc(sizeof(char*));
    // int *ia = malloc(sizeof(int));
    // *ia = 2;
    // unsigned long long some = 2;
    // *da = *((double *) &some);
    // *sa = *((char **) &some);
    // printf("%d\n", *((int*)sa));
    // printf("%d\n", *((int*)da));
    // printf("%d\n", *((int*)ia));
    //printDoubleBinary(*ptr);
    raise("hallo""hallo");
    return 0;
}