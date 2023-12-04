#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    //initializations
    char input[213][118];
    FILE *filePointer;
    filePointer = fopen("adventofcode.com_2023_day_4_input.txt", "r");
    if (filePointer == NULL) {
        printf("Error opening the file!\n");
        return 1;
    }

    // read file
    for (int i = 0; i < 213; i++) {
        fgets(input[i], 118, filePointer);
    }

    //parse input
    int sum = 0;
    int row = 0;
    for (int row = 0; row < 213; row++) {
        int winners = 0;
        printf("%s", input[row]);
        for (int col = 42; col < 116; col+=3) {
            printf("%c%c\n", input[row][col], input[row][col + 1]);
            for (int colM = 10; colM <= 37; colM+=3) {
                printf("%c%c ", input[row][colM], input[row][colM + 1]);
                if (input[row][col] == input[row][colM] && input[row][col + 1] == input[row][colM + 1]) {
                    winners++;
                    break;
                }
            }
            printf("\n");
        }
        printf("\n");
        printf("%d\n", winners);
        if (winners > 0) {
            int value = 1;
            for (int i = 1; i < winners; i++) {
                value *= 2;
            }
            sum += value;
        }
    }
    printf("%d\n", sum);
}