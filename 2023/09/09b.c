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
        list firstDigits = listCreate(sizeof(long));
        listAdd(&firstDigits, &row[0]);
        while(!allZero(row, rowLength)) {
            int index = 0;
            for (int j = 0; j < rowLength - 1; j++) {
                row[index] = row[j + 1] - row[j];
                index++;
            }
            listAdd(&firstDigits, &row[0]);
            rowLength--;
        } 
        long result =  0;
        for (int j = firstDigits.length - 2; j >= 0; j--) {
            long *firstDigit = listGet(&firstDigits, j);
            result = *firstDigit - result;
        }
        sum += result;
    }
    printf("sum = %ld\n", sum);
}

