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

    int cardCounts[213];

    //initialize array
    for (int i = 0; i < 213; i++) {
        cardCounts[i] = 1;
    }

    for (int row = 0; row < 213; row++) {
        printf("%s", input[row]);
        int winners = 0;
        for (int col = 42; col < 116; col+=3) {
            for (int colM = 10; colM <= 37; colM+=3) {
                if (input[row][col] == input[row][colM] && input[row][col + 1] == input[row][colM + 1]) {
                    winners++;
                    break;
                }
            }
        }
        for (int i = 1; i < winners + 1; i++) {
            if (row + i < 213) {
                cardCounts[row + i] += cardCounts[row];
            } 
        }
        row++;
    }
    int sum = 0;
    for (int i = 0; i < 213; i++) {
        sum += cardCounts[i];
    }
    printf("%d\n", sum);
}