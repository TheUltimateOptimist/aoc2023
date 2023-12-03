#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int power(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result = result * base;
    } 
    return result;
}

int getNumberCount(char* line) {
    int numberCount = 0;
    bool countsAsNew = true;
    for (int i = 0; i < sizeof(line); i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            if (countsAsNew) {
                numberCount++;
                countsAsNew = false;
            }
        }
        else {
            countsAsNew = true;
        }
    }
}

void fillWithNumbers(char* line, int* numbers) {
    int numberIndex = 0;
    int numberPow = 0;
    int number = 0;
    for (int i = sizeof(line) - 1; i >= 0; i--) {
        if (line[i] >= '0' && line[i] <= '9') {
            number = number + (line[i] - 48)*power(10, numberPow);
            numberPow++;
        }
        else if (number != 0 || numberPow != 0){
            int base = numberIndex*3;
            numbers[base] = number;
            numbers[base + 1] = i + 1;
            numbers[base + 2] = i + numberPow;
            numberIndex++;
            numberPow = 0;
            number = 0;
        }
    }
    if (number != 0 || numberPow != 0) {
        int base = numberIndex*3;
        numbers[base] = number;
        numbers[base + 1] = 0;
        numbers[base + 2] = numberPow - 1;
    }
}

int main() {
    //char line[] = "....401.............425.......323......791......697...............963............................................420........................\n";
    //von 1 - 140
    char cubicle[140][140];
    FILE *filePointer;
    filePointer = fopen("adventofcode.com_2023_day_3_input.txt", "r"); 
    if (filePointer == NULL) {
        printf("error opening the file!");
    }

    for (int i = 0; i < 140; i++) {
        fgets(cubicle[i], 140, filePointer);
    }

    int sum = 0;
    for (int i = 0; i < 140; i++) {
        int numberCount = getNumberCount(cubicle[i]);
        int numbers[numberCount*3];
        fillWithNumbers(cubicle[i], numbers);
        for (int j = 0; j < sizeof(numbers) / sizeof(int); j+=3) {
            int left = numbers[j + 1] > 0 && cubicle[i][numbers[j + 1] - 1] != '.';
            if ()
        }
        if (i > 0) {
        }
        if (i == )
        fgets(i % 2 == 0 ? lineOne : lineTwo, 140, filePointer);
        int numbersCount = 


    }

}