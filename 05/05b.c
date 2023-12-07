#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../string.c"
#include "../output.c"

#define MAPS_COUNT 7

typedef struct seed {
    long from;
    long to;
} seed;

int shouldRemove(char a) {
    return (a < '0' || a > '9') && a != ' ' && a != '\n';
}

int main() {
    char **blocks = readFile("adventofcode.com_2023_day_5_input.txt").split("\n\n").end;
    //char **blocks = readFile("test.txt").split("\n\n").end;
    long *seeds = chain(blocks[0]).removeWhen(shouldRemove).split(" ").collectLong(NULL);
    for (int i = 1; i <= MAPS_COUNT; i++) {
        int numberCount; 
        long *numbers = chain(blocks[i]).removeWhen(shouldRemove).replace("\n", " ").split(" ").collectLong(&numberCount);
        for (int s = 0; s < SEEDS_COUNT; s++) {
            for (int j = 0; j < numberCount; j+=3) {
                long sourceStart = numbers[j + 1];
                long sourceEnd = sourceStart + numbers[j + 2] - 1;
                //printf("start: %ld end: %ld number: %ld", sourceStart, sourceEnd, seeds[s]);
                if (seeds[s] >= sourceStart && seeds[s] <= sourceEnd) {
                    long destStart = numbers[j];
                    seeds[s] = destStart + seeds[s] - sourceStart;
                    break;
                }
            }
        }
        printLongs(seeds, SEEDS_COUNT);
    }
    long min = seeds[0];
    for (int i = 1; i < SEEDS_COUNT; i++) {
        if (seeds[i] < min) {
            min = seeds[i];
        }
    }
    printf("minimum = %ld\n", min);
}