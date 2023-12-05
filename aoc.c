#include <stdio.h>
#include <stdbool.h>
#include <string.h>

long power(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    long result = 1;
    for (int i = 0; i < exp; i++) {
        result = result * base;
    } 
    return result;
}

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

bool isNumber(char character) {
    return character >= '0' && character <= '9';
}

long fgetSize(FILE *filePointer) {
    fpos_t original;
    fgetpos(filePointer, &original);
    fseek(filePointer, 0, SEEK_END);
    long result = ftell(filePointer);
    fsetpos(filePointer, &original);
    return result;
}

int lineLength(char *line) {
    int length = 0;
    int index = 0;
    while (line[index] != '\n' && line[index] != '\0') {
        length++;
        index++;
    }
    return length;
}

int countNumbers(char *line) {
    int count = 0;
    bool previousIsNumber = false;
    for (int i = lineLength(line) - 1; i >= 0; i--) {
        if (isNumber(line[i]) && !previousIsNumber) {
            count++;
            previousIsNumber = true;
        }
        if (!isNumber(line[i])) {
            previousIsNumber = false;
        }
    }
    return count;
}

void extractNumbers(char *line, long* numbers, int numbersLength) {
    int index = numbersLength - 1;
    int numberPow = 0;
    long number = 0;
    for (int i = lineLength(line) - 1; i >= 0; i--) {
        if (isNumber(line[i])) {
            number += (line[i] - 48)*power(10, numberPow);
            numberPow++;
        }
        if ((i == 0 || !isNumber(line[i])) && numberPow > 0) {
            numbers[index] = number;
            number = 0;
            numberPow = 0;
            index--;
        }
    }
}

void initWithLong(long *numbers, long value, int length) {
    for (int i = 0; i < length; i++) {
        numbers[i] = value;
    }
}

void initWithInt(int *numbers, int value, int length) {
    for (int i = 0; i < length; i++) {
        numbers[i] = value;
    }
}

int jumpLines(FILE *filePointer, int lines) {
    for (int i = 0; i < lines; i++) {
        while(true){
            char cha = fgetc(filePointer);
            if (cha == '\n') {
                break;
            }
            if (cha == EOF) {
                return 1;
            }
        }
    }
    return 0;
}