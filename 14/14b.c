#include <stdio.h>
#include "../string.c"
#include <time.h>

#define GRIDSIZE 100

typedef enum Direction {
    top,
    left,
    bottom,
    right
} Direction;

int getNewRow(Direction direction, int row) {
    switch(direction) {
        case top: return row - 1;
        case left: return row;
        case bottom: return row + 1;
        case right: return row;
    }
}

int getNewCol(Direction direction, int col) {
    switch(direction) {
        case top: return col;
        case left: return col - 1;
        case bottom: return col;
        case right: return col + 1;
    }
}

void rollOver(char **grid, Direction direction, int row, int col) {
    int newRow = getNewRow(direction, row);
    int newCol = getNewCol(direction, col);
    while(newRow >= 0 && newRow < GRIDSIZE && newCol >= 0 && newCol < GRIDSIZE && grid[newRow][newCol] == '.') {
        grid[newRow][newCol] = 'O';
        grid[row][col] = '.';
        row = newRow;
        col = newCol;
        newRow = getNewRow(direction, newRow);
        newCol = getNewCol(direction, newCol);
    }
}

int main() {
    //char **grid = readFile("test.txt").trim().split("\n").end;
    char **grid = readFile("adventofcode.com_2023_day_14_input.txt").trim().split("\n").end;
    list sums = listCreate(sizeof(long));
    list ids = listCreate(sizeof(long));
    while (1) {
        // roll over in all 4 directions
        for (int i = 0; i < 4; i++) {
            for (int l = 0; l < GRIDSIZE; l++) {
                int ll = l;
                if (i == bottom) {
                    ll = GRIDSIZE - 1 - l;
                }
                for (int m = 0; m < GRIDSIZE; m++) {
                    int mm = m;
                    if (i == right) {
                        mm = GRIDSIZE - 1 - m;
                    }
                    if (grid[ll][mm] == 'O') {
                        rollOver(grid, i, ll, mm);
                    }
                }
            }
        }
        // add id and sum
        long sum = 0;
        long id = 0;
        for (int l = 0; l < GRIDSIZE; l++) {
            for (int m = 0; m < GRIDSIZE; m++) {
                if (grid[l][m] == 'O') {
                    id += (l*GRIDSIZE + m);
                    sum += GRIDSIZE - l;
                }
            }
        }
        listAdd(&sums, &sum);
        listAdd(&ids, &id);
        // detect cycle
        for (int i = 0; i < ids.length - 1; i++) {
            long *cId = listGet(&ids, i);
            if (*cId == id) {
                int cycleLength = ids.length - 1 - i;
                long cycles = 1000000000;
                long *res = listGet(&sums, i + (cycles - i) % cycleLength - 1);
                printf("result: %ld\n", *res);
                return 0;
            }
        }
    }
}