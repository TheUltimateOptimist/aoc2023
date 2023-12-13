#include <stdio.h>
#include "../string.c"

int allZero(long *list, int length) {
    for (int i = 0; i < length; i++) {
        if (list[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char **histories = readFile("adventofcode.com_2023_day_9_input.txt").trim().split("\n").end;
    //char **histories = readFile("test.txt").trim().split("\n").end;
    long sum = 0;
    for (int i = 0; i < strarraylen(histories); i++) {
        int rowLength;
        long *row = chain(histories[i]).trim().split(" ").collectLong(&rowLength);
        list lastDigits = listCreate(sizeof(long));
        listAdd(&lastDigits, &row[rowLength - 1]);
        while(!allZero(row, rowLength)) {
            int index = 0;
            for (int j = 0; j < rowLength - 1; j++) {
                row[index] = row[j + 1] - row[j];
                index++;
            }
            listAdd(&lastDigits, &row[index - 1]);
            rowLength--;
        } 
        for (int j = 0; j < lastDigits.length; j++) {
            long *lastDigit = listGet(&lastDigits, j);
            printf("lastd: %ld\n", *lastDigit);
            sum += *lastDigit;
        }
    }
    printf("sum = %ld\n", sum);
}