#include <stdio.h>
#include "../string.c"

long hashString(char *string) {
    long currentValue = 0;
    for (int i = 0; i < strlen(string); i++) {
        currentValue += string[i];
        currentValue *= 17;
        currentValue = currentValue % 256;
    }
    return currentValue;
}

typedef struct Lens {
    char *label;
    int focusLength;
} Lens;

int main() {
    list boxes[256];
    for (int i = 0; i < 256; i++) {
        boxes[i] = listCreate(sizeof(Lens));
    }
    char **strings = readFile("adventofcode.com_2023_day_15_input.txt").split("\n").join("").split(",").end;
    //char **strings = chain("rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7").split(",").end;
    for (int i = 0; strings[i] != NULL; i++) {
        if (substrCount(strings[i], "=") == 1) {
            char **parts = split(strings[i], "=");
            Lens lens = {
                .label = parts[0],
                .focusLength = strtol(parts[1], NULL, 10)
            };
            long hash = hashString(lens.label);
            int index = -1;
            for (int i = 0; i < boxes[hash].length; i++) {
                Lens *cLens = listGet(&boxes[hash], i);
                if (substrCount(cLens->label, lens.label) == 1 && substrCount(lens.label, cLens->label) == 1) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                listAdd(&boxes[hash], &lens);
            }
            else {
                listSet(&boxes[hash], index, &lens);
            }
            free(parts[1]);
            free(parts);
        } 
        else {
            char *label = chain(strings[i]).split("-").get(0).end;
            long hash = hashString(label);
            printf("hash: %ld\n", hash);
            int index = -1;
            for (int i = 0; i < boxes[hash].length; i++) {
                Lens *cLens = listGet(&boxes[hash], i);
                if (substrCount(cLens->label, label) == 1 && substrCount(label, cLens->label) == 1) {
                    index = i;
                    break;
                }
            }
            if (index >= 0) {
                printf("entered\n");
                free(listPopAt(&boxes[hash], index));
            }
            free(label);
        }
        for (int y = 0; y < 256; y++) {
            if (boxes[y].length > 0) {
                printf("Box %d: ", y);
                for (int z = 0; z < boxes[y].length; z++) {
                    Lens *lens = listGet(&boxes[y], z);
                    printf("%s;%d, ", lens->label, lens->focusLength);
                }
                printf("\n");
            }
        }
        printf("///////////////////////\n");
    }
    long sum = 0;
    for (int i = 0; i < 256; i++) {
        for (int l = 0; l < boxes[i].length; l++) {
            Lens *lens = listGet(&boxes[i], l);
            sum += (i + 1)*(l + 1)*(lens->focusLength);
        }
    }
    printf("result: %ld\n", sum);
}