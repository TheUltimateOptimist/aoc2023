#include <stdio.h>

int main() {
    FILE *filePointer;
    char line[100];
    filePointer = fopen("adventofcode.com_2023_day_1_input.txt", "r");
    if (filePointer == NULL) {
        printf("Error opening the file!\n");
        return 1;
    }

    while(fgets(line, sizeof(line), filePointer) != NULL) {
        char firstNumber = NULL;
        char secondNumber = NULL;
         
         
    }
    // fpos_t fposition;
    // fgetpos(filePointer, &fposition);
    // printf("%ld", fposition.__pos);
}