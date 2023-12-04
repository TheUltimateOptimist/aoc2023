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

bool isSymbol(char character) {
    return (character < '0' || character > '9') && character != '.';
}

int readNum(char** cubicle, int row, int col, int* continueIndex) {
    int num = 0;
    bool shouldCount = false;
    int numberPow = 0;
    while(col >= 0 && cubicle[row][col] >= '0' && cubicle[row][col] <= '9') {
        bool left = col > 0 && isSymbol(cubicle[row][col - 1]);
        bool right = col < 140 - 1 && isSymbol(cubicle[row][col + 1]);
        bool top = row > 0 && isSymbol(cubicle[row - 1][col]);
        bool bottom = row < 140 - 1 && isSymbol(cubicle[row + 1][col]);
        bool topLeft = row > 0 && col > 0 && isSymbol(cubicle[row - 1][col - 1]);
        bool topRight = row > 0 && col < 140 - 1 && isSymbol(cubicle[row - 1][col + 1]);
        bool bottomLeft = row < 140 - 1 && col > 0 && isSymbol(cubicle[row + 1][col - 1]);
        bool bottomRight = row < 140 - 1 && col < 140 - 1 && isSymbol(cubicle[row + 1][col + 1]); 
        if (left || right || top || bottom || topLeft || topRight || bottomLeft || bottomRight) {
            shouldCount = true;
        }
        num = num + (cubicle[row][col] - 48)*power(10, numberPow);
        col--;
        numberPow++;
    }
    *continueIndex = col;
    if (shouldCount) {
        return num;
    }
    else {
        return 0;
    }
}

int main() {
    //von 1 - 140
    char** cubicle;
    FILE *filePointer;
    filePointer = fopen("adventofcode.com_2023_day_3_input.txt", "r"); 
    if (filePointer == NULL) {
        printf("error opening the file!");
    }

    //read input
    for (int i = 0; i < 140; i++) {
        fgets(cubicle[i], 140, filePointer);
    }

    int sum = 0;
    for (int row = 0; row < 140; row++) {
        int col = 139;
        while(col >= 0) {
            if (cubicle[row][col] >= '0' && cubicle[row][col] <= '9') {
                sum += readNum(cubicle, row, col, &col);
            }
            else {
                col--;
            }
        }
    }
    printf("sum = %d\n", sum);
}