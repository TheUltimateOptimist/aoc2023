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

bool isNumber(char character) {
    return character >= '0' && character <= '9';
}

int readNum(char cubicle[140][142], int row, int col) {
    //go as far to the right as possible
    while(col < 140 - 1 && isNumber(cubicle[row][col + 1])) {
        col++;
    }

    int num = 0;
    int numberPow = 0;
    while(col >= 0 && isNumber(cubicle[row][col])) {
        num = num + (cubicle[row][col] - 48)*power(10, numberPow);
        cubicle[row][col] = '.';
        col--;
        numberPow++;
    }
    return num;
}

void initWith0(int array[8]) {
    for (int i = 0; i < 8; i++) {
        array[i] = 0;
    }
}

int main() {
    //von 1 - 140
    char cubicle[140][142];
    FILE *filePointer;
    filePointer = fopen("adventofcode.com_2023_day_3_input.txt", "r"); 
    if (filePointer == NULL) {
        printf("error opening the file!");
    }

    //read input
    for (int i = 0; i < 140; i++) {
        fgets(cubicle[i], 142, filePointer);
    }

    int sum = 0;
    for (int row = 0; row < 140; row++) {
        int col = 139;
        int lol = sum;
        while(col >= 0) {
            if (cubicle[row][col] == '*') {
                int nums[8];
                initWith0(nums);
                if (col > 0 && isNumber(cubicle[row][col - 1])) {
                    nums[0] = readNum(cubicle, row, col - 1); //left
                }
                if (col < 140 - 1 && isNumber(cubicle[row][col + 1])) {
                    nums[1] = readNum(cubicle, row, col + 1); //right
                }
                if (row > 0 && isSymbol(cubicle[row - 1][col])) {
                    nums[2] = readNum(cubicle, row - 1, col); //top
                }
                if (row < 140 - 1 && isNumber(cubicle[row + 1][col])) {
                    nums[3] = readNum(cubicle, row + 1, col); //bottom
                }
                if (row > 0 && col > 0 && isNumber(cubicle[row - 1][col - 1])) {
                    nums[4] = readNum(cubicle, row - 1, col - 1); //topLeft
                }
                if (row > 0 && col < 140 - 1 && isNumber(cubicle[row - 1][col + 1])) {
                    nums[5] = readNum(cubicle, row - 1, col + 1); //topRight
                }
                if (row < 140 - 1 && col > 0 && isNumber(cubicle[row + 1][col - 1])) {
                    nums[6] = readNum(cubicle, row + 1, col - 1); //bottomLeft
                }
                if (row < 140 - 1 && col < 140 - 1 && isNumber(cubicle[row + 1][col + 1])) {
                    nums[7] = readNum(cubicle, row + 1, col + 1); //bottomRight
                }
                int numberCount = 0;
                int gearRatio = 1;
                for (int i = 0; i < 8; i++) {
                    if (nums[i] != 0) {
                        gearRatio *= nums[i];
                        numberCount++;
                    }
                }
                if (numberCount == 2) {
                    sum += gearRatio;
                }
            }
            col--;
        }
    }
    printf("sum = %d\n", sum);
}