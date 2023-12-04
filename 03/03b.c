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
    int num = 0;
    int numberPow = 0;
    //go as far to the right as possible
    while(col < 140 - 1 && isNumber(cubicle[row][col + 1])) {
        col++;
    }

    while(col >= 0 && isNumber(cubicle[row][col])) {
        //bool left = col > 0 && isSymbol(cubicle[row][col - 1]);
        //bool right = col < 140 - 1 && isSymbol(cubicle[row][col + 1]);
        //bool top = row > 0 && isSymbol(cubicle[row - 1][col]);
        //bool bottom = row < 140 - 1 && isSymbol(cubicle[row + 1][col]);
        //bool topLeft = row > 0 && col > 0 && isSymbol(cubicle[row - 1][col - 1]);
        //bool topRight = row > 0 && col < 140 - 1 && isSymbol(cubicle[row - 1][col + 1]);
        //bool bottomLeft = row < 140 - 1 && col > 0 && isSymbol(cubicle[row + 1][col - 1]);
        //bool bottomRight = row < 140 - 1 && col < 140 - 1 && isSymbol(cubicle[row + 1][col + 1]); 
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
                    nums[0] = cubicle[row][col - 1];
                }
                else {

                }
        //bool right = col < 140 - 1 && isSymbol(cubicle[row][col + 1]);
        //bool top = row > 0 && isSymbol(cubicle[row - 1][col]);
        //bool bottom = row < 140 - 1 && isSymbol(cubicle[row + 1][col]);
        //bool topLeft = row > 0 && col > 0 && isSymbol(cubicle[row - 1][col - 1]);
        //bool topRight = row > 0 && col < 140 - 1 && isSymbol(cubicle[row - 1][col + 1]);
        //bool bottomLeft = row < 140 - 1 && col > 0 && isSymbol(cubicle[row + 1][col - 1]);
        //bool bottomRight = row < 140 - 1 && col < 140 - 1 && isSymbol(cubicle[row + 1][col + 1]); 

                
            }
            col--;
        }
        printf("%s", cubicle[row]);
        printf("%d\n", sum - lol);
    }
    printf("sum = %d\n", sum);
}