#include <stdio.h>
#include "../string.c"
#include <time.h>

#define GRIDSIZE 100

int main() {
    //char **grid = readFile("test.txt").trim().split("\n").end;
    char **grid = readFile("adventofcode.com_2023_day_14_input.txt").trim().split("\n").end;

    // roll over
    for (int l = 1; l < GRIDSIZE; l++) {
        for (int m = 0; m < GRIDSIZE; m++) {
            if (grid[l][m] == 'O') {
                int crow = l;
                while (crow > 0 && grid[crow - 1][m] == '.') {
                    grid[crow][m] = '.';
                    grid[crow - 1][m] = 'O';
                    crow--;
                }
            }
        }
    }

    // calc result
    long sum = 0;
    for (int l = 0; l < GRIDSIZE; l++) {
        for (int m = 0; m < GRIDSIZE; m++) {
            if (grid[l][m] == 'O') {
                sum += GRIDSIZE - l;
            }
        }
    }
    printf("sum = %ld\n", sum);
}