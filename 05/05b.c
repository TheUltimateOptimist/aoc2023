#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../string.c"

#define MAPS_COUNT 7
#define SEEDSCOUNT 20

typedef struct seed {
    long from;
    long to;
} seed;

void printLong(void *element) {
    printf("%ld", *((long*) element));
}

void printSeed(void *element) {
    seed *seedElement = element;
    printf("Seed: %ld;%ld", seedElement->from, seedElement->to);
}

int main() {
    char **blocks = readFile("adventofcode.com_2023_day_5_input.txt").split("\n\n").end;

    //extract seeds
    long *individualSeeds = chain(blocks[0]).split(":").get(1).split(" ").collectLong(NULL);
    list seeds = listCreate(sizeof(seed));
    for (int i = 0; i < SEEDSCOUNT; i+=2) {
        seed finalSeed = {.from = individualSeeds[i], .to = individualSeeds[i] + individualSeeds[i + 1] - 1};
        listAdd(&seeds, &finalSeed);
    }

    for (int i = 1; i <= MAPS_COUNT; i++) {
        int numberCount;
        list nextSeeds = listCreate(sizeof(seed));
        long *numbers = chain(blocks[i]).split(":").get(1).replace("\n", " ").split(" ").collectLong(&numberCount);
        seed *range = listPop(&seeds);
        while (range != NULL){
            for (int j = 0; j < numberCount; j+=3) {
                long sourceStart = numbers[j + 1];
                long sourceEnd = sourceStart + numbers[j + 2] - 1;
                long destStart = numbers[j];
                if (range->from >= sourceStart && range->to <= sourceEnd) {
                    //completely inside
                    seed newSeed = {
                        .from = destStart + range->from - sourceStart,
                        .to = destStart + range->to - sourceStart
                    };
                    listAdd(&nextSeeds, &newSeed);
                    break;
                }
                else if (range->from < sourceStart && range->to >= sourceStart && range->to <= sourceEnd) {
                    //end inside
                    seed outerSeed = {
                        .from = range->from,
                        .to = sourceStart - 1
                    };
                    seed innerSeed = {
                        .from = destStart,
                        .to = destStart + range->to - sourceStart
                    };
                    listAdd(&nextSeeds, &innerSeed);
                    listAdd(&seeds, &outerSeed);
                    break;
                }
                else if (range->from >= sourceStart && range->from <= sourceEnd && range->to > sourceEnd) {
                    //start inside
                    seed outerSeed = {
                        .from = sourceEnd + 1,
                        .to = range->to 
                    };
                    seed innerSeed = {
                        .from = destStart + range->from - sourceStart,
                        .to = destStart + sourceEnd - sourceStart //check when mistake
                    };
                    listAdd(&nextSeeds, &innerSeed);
                    listAdd(&seeds, &outerSeed);
                    break;
                }
                else if (range->from < sourceStart && range->to > sourceEnd) {
                    //completely outside
                    seed leftOuterSeed = {
                        .from = range->from,
                        .to = sourceStart - 1
                    };
                    seed rightOuterSeed = {
                        .from = sourceEnd + 1,
                        .to = range->to
                    };
                    seed innerSeed = {
                        .from = destStart,
                        .to = destStart + sourceEnd - sourceStart //check when mistake
                    };
                    listAdd(&nextSeeds, &innerSeed);
                    listAdd(&seeds, &leftOuterSeed);
                    listAdd(&seeds, &rightOuterSeed);
                    break;
                }
                else if (j == numberCount - 3) {
                    listAdd(&nextSeeds, range);
                }
            }
            range = listPop(&seeds);
        }
        free(seeds.data);
        seeds = nextSeeds;
    }

    seed *min = listGet(&seeds, 0);
    for (int i = 1; i < seeds.length; i++) {
        seed *newSeed = listGet(&seeds, i);
        if (newSeed->from < min->from) {
            min = newSeed;
        }
    }
    printf("minimum = %ld\n", min->from);
}