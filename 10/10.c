#include <stdio.h>
#include "../string.c"

#define GRIDSIZE 140
#define SX 32
#define SY 25

char **grid;

typedef enum Direction {
    up,
    down,
    right,
    left,
    stuck,
    finished
} Direction;

Direction nextPossibleDirection(Direction goingIn, int *fromX, int *fromY) {
    switch(goingIn) {
        case up: *fromY = *fromY - 1;
        break;
        case down: *fromY = *fromY + 1;
        break;
        case left: *fromX = *fromX - 1;
        break;
        case right: *fromX = *fromX + 1;
    }
    if (*fromX < 0 || *fromX > 139 || *fromY < 0 || *fromY > 139) {
        return stuck;
    }
    switch(grid[*fromY][*fromX]) {
        case '.': return stuck;
        case 'S': return finished;
        case '|': return goingIn == down || goingIn == up ? goingIn : stuck;
        case '-': return goingIn == right || goingIn == left ? goingIn : stuck;
        case 'L': {
            if (goingIn == down) {
                return right;
            }
            else if (goingIn == left) {
                return up;
            }
            return stuck;
        }
        case 'J': {
            if (goingIn == down) {
                return left;
            }
            else if (goingIn == right) {
                return up;
            }
            return stuck;
        }
        case '7': {
            if (goingIn == right) {
                return down;
            }
            else if (goingIn == up) {
                return left;
            }
            return stuck;
        }
        case 'F': {
            if (goingIn == left) {
                return down;
            }
            else if (goingIn == up) {
                return right;
            }
            return stuck;
        }
    }
}

int main() {
    grid = readFile("adventofcode.com_2023_day_10_input.txt").trim().split("\n").end;
    //grid = readFile("test.txt").trim().split("\n").end;
    for (int i = 0; i < 4; i++) {
        long steps = 0;
        Direction direction = i;
        int pX = SX;
        int pY = SY;
        while(direction != stuck) {
            direction = nextPossibleDirection(direction, &pX, &pY);
            steps++;
            if (direction == finished) {
                printf("loop steps: %ld\n", steps / 2);     
                exit(0);
            }
        }
    }
}