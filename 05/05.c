#include <stdio.h>
#include <stdbool.h>
#include "../aoc.c"

int main() {
    FILE *filePointer;
    filePointer = fopen("adventofcode.com_2023_day_5_input.txt", "r");
    if (filePointer == NULL) {
        printf("error opening the file!");
        return 1;
    }

    char line[212];
    fgets(line, 212, filePointer);

    long seeds[20];
    extractNumbers(line, seeds, 20);

    jumpLines(filePointer, 2);
    long numbers[3];
    fgets(line, 212, filePointer);
    extractNumbers(line, numbers, 3);

    printLongs(seeds, 20);
    printLongs(numbers, 3);

    for (int i = 0; i < 7; i++) {

    }

    //printNumbers(seeds, 20);
}