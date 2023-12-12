#include <stdio.h>

typedef struct game {
    int time;
    int record;
} game;

int main() {
    game games[] = {{.time = 45, .record = 305}, {.time = 97, .record = 1062}, {.time = 72, .record = 1110}, {.time = 95, .record = 1695}};
    int result = 1;
    for (int i = 0; i < 4; i++) {
        printf("time: %d, record: %d\n", games[i].time, games[i].record);
        int ways = 0;
        for (int j = 0; j <= games[i].time; j++) {
            printf("%d\n", games[i].time);
            int distance = j*(games[i].time - j);
            printf("distance: %d\n", distance);
            if (distance > games[i].record) {
                ways++;
            }
        }
        if (ways > 0) {
            result *= ways;
        }
    }
    printf("%d\n", result);
}