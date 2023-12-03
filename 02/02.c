#include <stdio.h>
#include <string.h>

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

int isGameValid(char * line, int beginning, int maxRed, int maxGreen, int maxBlue) {
    int red = 0;
    int green = 0;
    int blue = 0;
    char number[5];
    int numberIndex = 0;
    for (int i = beginning; i < strlen(line); i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            number[numberIndex] = line[i];
            numberIndex++;
        }
        if ((line[i] == 'r' || line[i] == 'g' || line[i] == 'b') && numberIndex > 0) {
            int numberValue = 0;
            for (int j = numberIndex - 1; j >= 0; j--) {
                numberValue = numberValue + (number[numberIndex - 1 - j] - 48)*power(10, j);
            }
            printf("%c:%d ", line[i], numberValue);
            switch (line[i]) {
                case 'r': red = numberValue;
                break;
                case 'g': green = numberValue;
                break;
                case 'b': blue = numberValue;
            }
            numberIndex = 0;
        }
        if (line[i] == '\n' || line[i] == ';') {
            int isInputInvalid = red > maxRed || green > maxGreen || blue > maxBlue;
            if (isInputInvalid) {
                return 0;
            }
        }
    }
    return 1;
}

int numberOfDigits(int number) {
    int digits = 0;
    while(number != 0) {
        digits++;
        number = number / 10;
    }
    return digits;
}

int main() {
    const int maxRed = 12;
    const int maxGreen = 13;
    const int maxBlue = 14;

    FILE *filePointer;
    char line[200];
    filePointer = fopen("adventofcode.com_2023_day_2_input.txt", "r");
    if (filePointer == NULL) {
        printf("Error opening the file!\n");
        return 1;
    }
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
        fgets(line, sizeof(line), filePointer);
        if (isGameValid(line, 7 + numberOfDigits(i), maxRed, maxGreen, maxBlue)) {
            sum += i;
        }
    }
    printf("%d\n", sum);
}