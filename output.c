#include <stdio.h>

void printInts(int numbers[], long numbersLength) {
    for (int i = 0; i < numbersLength; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void printLongs(long numbers[], long numbersLength) {
    for (int i = 0; i < numbersLength; i++) {
        printf("%ld ", numbers[i]);
    }
    printf("\n");
}