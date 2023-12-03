#include <stdio.h>

int main() {
    FILE *filePointer;
    char line[100];
    filePointer = fopen("adventofcode.com_2023_day_1_input.txt", "r");
    if (filePointer == NULL) {
        printf("Error opening the file!\n");
        return 1;
    }
    int sum = 0;
    while(fgets(line, sizeof(line), filePointer) != NULL) {
        printf("%s", line);
        char firstNumber = 'a';
        char secondNumber = 'a';
        for (int i = 0; line[i] != '\n'; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                if (firstNumber == 'a') {
                    firstNumber = line[i];
                }
                else {
                    secondNumber = line[i];
                }
            }
        }
        if (secondNumber == 'a') {
            secondNumber = firstNumber;
        }
        //0 - 48, 9 - 57
        sum = sum + ((int) firstNumber - 48)*10 + (int) secondNumber - 48;
    }
    printf("%d\n", sum);
}