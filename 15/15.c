#include <stdio.h>
#include "../string.c"

long hashString(char *string) {
    long currentValue = 0;
    for (int i = 0; i < strlen(string); i++) {
        currentValue += string[i];
        currentValue *= 17;
        currentValue = currentValue % 256;
    }
    return currentValue;
}

typedef struct Lens {
    char *label;
    int focusLength;
} Lens;

int main() {
    char **strings = readFile("adventofcode.com_2023_day_15_input.txt").split("\n").join("").split(",").end;
    long sum = 0;
    for (int i = 0; strings[i] != NULL; i++) {
        sum += hashString(strings[i]);
    }
    printf("result: %ld\n", hashString("qp"));
}