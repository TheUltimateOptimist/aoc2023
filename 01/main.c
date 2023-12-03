#include <stdio.h>
#include <string.h>

void replace(char * input, const char * from, char to) {
    int start = 0;
    int fromLength = strlen(from);
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == from[start]) {
            if (start == fromLength - 1) {
                input[i - 1] = to;
                start = 0;
            }
            else {
                start++;
            }
        }
        else if (input[i] == from[0]){
            start = 1;
        }
        else {
            start = 0;
        }
    }
}

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
        replace(line, "nine", '9');
        replace(line, "eight", '8');
        replace(line, "seven", '7');
        replace(line, "six", '6');
        replace(line, "five", '5');
        replace(line, "four", '4');
        replace(line, "three", '3');
        replace(line, "two", '2');
        replace(line, "one", '1');
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