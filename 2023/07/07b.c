#include <stdio.h>
#include "../string.c"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

char cardRanks[] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

typedef struct Hand {
    char * cards;
    int value;
} Hand;

int getHandTypeStrength(const Hand *hand) {
    int strength = 0;
    int largestCount = 0;
    int jCount = 0;
    for (int i = 0; i < 5; i++) {
        int count = 0;
        for (int j = 0; j < 5; j++) {
            if (hand->cards[j] == hand->cards[i] && j < i) {
                break;
            }
            else if (hand->cards[j] == hand->cards[i] && hand->cards[i] == 'J') {
                jCount++;
            }
            else if (hand->cards[j] == hand->cards[i]) {
                count++;
            }
        }
        if (count > largestCount) {
            strength += pow(10, largestCount);
            largestCount = count;
        }
        else {
            strength += pow(10, count);
        }
    }
    if (jCount > 0 && largestCount > 0) {
        strength += pow(10, largestCount + jCount);
    }
    else if (jCount > 0) {
        strength += pow(10, jCount);
    }
    else {
        strength += pow(10, largestCount);
    }
    return strength;
}


int compareHands(const void *a, const void *b) {
    const Hand *handOne = a;
    const Hand *handTwo = b;
    int firstStrength = getHandTypeStrength(handOne);
    int secondStrength = getHandTypeStrength(handTwo);
    if (firstStrength == secondStrength) {
        int index = 0;
        while(handOne->cards[index] == handTwo->cards[index]) {
            index++;
        }
        for (int i = 0; i < 13; i++) {
            if (handTwo->cards[index] == cardRanks[i]) {
                return -1;
            }
            else if (handOne->cards[index] == cardRanks[i]) {
                return 1;
            }
        }
    }
    return firstStrength - secondStrength;
}

void* mapToHand(char *text) {
    char **parts = chain(text).trim().split(" ").end;
    int value = strtol(parts[1], NULL, 10);
    Hand *hand = malloc(sizeof(Hand));
    hand->cards = parts[0];
    hand->value = value;
    return hand;
}

int main() {
    list hands = readFile("adventofcode.com_2023_day_7_input.txt").trim().split("\n").collect(mapToHand, sizeof(Hand));
    qsort(hands.data, 1000, sizeof(Hand), compareHands);
    long result = 0;
    for (int i = 0; i < 1000; i++) {
        Hand *hand = listGet(&hands, i);
        result += (i + 1)*hand->value;
    }
    printf("total winnings: %ld\n", result);
}