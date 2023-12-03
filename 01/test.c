#include <stdio.h>
#include <string.h>

void replace(char * input, const char * from, char to) {
    int start = 0;
    int fromLength = strlen(from);
    printf("%s %d\n", from, fromLength);
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == from[start]) {
            if (start == fromLength - 1) {
                input[i - 1] = to;
                start = 0;
            }
            else {
                start++;
            }
        }
        else if (input[i] == from[0]){
            start = 1;
        }
        else {
            start = 0;
        }
    }
}

int main() {
    char line[] = "83hqrd1sixsevennine\n";
    printf("%s", line);
    replace(line, "nine", '9');
        replace(line, "eight", '8');
        replace(line, "seven", '7');
        replace(line, "six", '6');
        replace(line, "five", '5');
        replace(line, "four", '4');
        replace(line, "three", '3');
        replace(line, "two", '2');
        replace(line, "one", '1');
        printf("%s", line);
    printf("%s", line);
}