#include <stdio.h>

typedef struct Game {
    long time;
    long record;
} Game;

int main() {
    Game game  = {.time = 45977295, .record = 305106211101695};
    int ways = 0;
    for (long holdFor = 0; holdFor <= game.time; holdFor++) {
        long distance = holdFor*(game.time - holdFor);
        if (distance > game.record) {
            ways++;
        }
    }
    printf("%d\n", ways);
}