#include <stdio.h>
#include "../string.c"

int reflectHorizontally(char **grid, int row) {
    int rows = strarraylen(grid);
    for (int i = 0; i < strlen(grid[0]); i++) {
        int cRow = row;
        int tRow = i + 1 + i - cRow;;
        while(cRow >= 0 && tRow < rows) {
            if ()
        }
    }
}

int main() {
    char **patterns = readFile("test.txt").trim().split("\n\n").end;
    //char **patterns = readFile("adventofcode.com_2023_day_13_input.txt").trim().split("\n\n").end;
    long sum = 0;
    for (int i = 0; patterns[i] != NULL; i++) {
        char **pattern = chain(patterns[i]).split("\n").end;
        int cols = strlen(pattern[0]);
        int rows = strarraylen(pattern);

        // find horizontal reflection
        for (int row = 0; row < rows - 1; row++) {

        }
    }
    printf("result: %ld\n", sum);
}