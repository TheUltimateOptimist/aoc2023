#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc.c"

// long fgetSize(FILE *filePointer) {
//     fpos_t original;
//     fgetpos(filePointer, &original);
//     fseek(filePointer, 0, SEEK_END);
//     long result = ftell(filePointer);
//     fsetpos(filePointer, &original);
//     return result;
// }

char* readFile(char *fileName) {
    FILE *filePointer;
    filePointer = fopen(fileName, "r");
    if (filePointer == NULL) {
        printf("Opening the file: '%s' failed!", fileName);
        exit(1);
    }
    long size = fgetSize(filePointer);
    char *content = malloc(size + 1);
    long index = 0;
    for (long i = 0; i < size; i++) {
        content[i] = fgetc(filePointer);
    }
    content[size] = '\0';
    return content;
}

/// @brief creates a string that goes from input[from] to input[to]  
/// @brief an empty string will be created if from is greater than to or if from or to is out of bounds
/// @param input the string to scan through
/// @param from the starting index 
/// @param to the ending index 
/// @return a pointer to the string that goes from input[from] to input[to]
char* substr(char *input, long from, long to) {
    if (from > to || from < 0 || to >= strlen(input)) {
        char *string = malloc(1);
        string[0] = '\0';
        return string;
    }
    char *string = malloc(to - from + 2);
    int index = 0;
    for (int i = from; i <= to; i++) {
        string[index] = input[i];
        index++;
    }
    string[index] = '\0';
    return string;
}

/// @brief Counts the number of occurrences of the substr in the input.
/// @param input the string to scan through
/// @param substr the substring to find in the input
/// @return the number of occurrences of the substr in the input (0 if substr is empty)
int substrCount(char *input, char *substr) {
    unsigned long inputLength = strlen(input);
    unsigned long substrLength = strlen(substr);
    int matchCount = 0;
    int nextMatch = 0;
    for (int i = 0; i < inputLength; i++) {
        if (input[i] == substr[nextMatch]) {
            if (nextMatch == substrLength - 1) {
                matchCount++;
                nextMatch = 0;
            }
            else {
                nextMatch++;
            }
        }
        else {
            nextMatch = 0;
        }
    }
    return matchCount;
}

/// @brief Fills two dimensional char array parts with the remaining strings if input is split with substring
/// @param input the string to split with substring
/// @param substr the string input should be split by
/// @param parts the two dimensional string array that gets filled with the parts
void fillWithParts(char *input, char *substring, char **parts) {
    unsigned long inputLength = strlen(input);
    unsigned long substringLength = strlen(substring);
    int matchCount = 0;
    long previousEnd = -1;
    long startIndex = 0;
    int nextMatch = 0;
    for (int i = 0; i < inputLength; i++) {
        if (input[i] == substring[nextMatch]) {
            if (nextMatch == substringLength - 1) {
                parts[matchCount] = substr(input, previousEnd + 1, startIndex - 1);
                matchCount++;
                nextMatch = 0;
                startIndex = i + 1;
                previousEnd = i;
            }
            else {
                nextMatch++;
            }
        }
        else {
            nextMatch = 0;
            startIndex = i + 1;
        }
    }
    parts[matchCount] = substr(input, previousEnd + 1, startIndex - 1);
}

typedef struct {
    int length;
    char **data;
} split_result;

/// @brief splits the given input with by
/// @param input the string to split with by
/// @param by the string to split the input with 
/// @return a split result struct 
split_result split(char *input, char *by) {
    unsigned long inputLength = strlen(input);
    if (strlen(by) == 0) {
        char **result = malloc(inputLength*sizeof(char *));
        for (int i = 0; i < inputLength; i++) {
            result[i] = malloc(2);
            result[i][0] = input[i];
            result[i][1] = '\0';
        }
        split_result s = {1, result};
        return s;
    }
    int occurrences = substrCount(input, by);
    char **result = malloc((occurrences+1)*sizeof(char *));
    fillWithParts(input, by, result);
    split_result s = {occurrences + 1, result};
    return s;
}

/// @brief splits the given input with by 
/// @brief consumes the given input (deallocates it)
/// @param input the string to split with by
/// @param by the string to split the input with 
/// @return a split result struct 
split_result csplit(char *input, char *by) {
    split_result s = split(input, by); 
    free(input);
    return s;
}

/// @brief joins the given strings in the split_result with by
/// @param input the strings to join with by 
/// @param by the string to join the input with 
/// @return the resulting char array if input is joined with by 
char* join(split_result input, char *by) {
    unsigned long byLength = strlen(by);
    long size = 1;
    for (int i = 0; i < input.length; i++) {
        if (i > 0) {
            size += byLength;
        }
        size += strlen(input.data[i]);
    }
    char *result = malloc(size);
    int index = 0;
    for (int i = 0; i < input.length; i++) {
        if (i > 0) {
            for (int j = 0; j < byLength; j++) {
                result[index] = by[j];
                index++;
            }
        }
        for (int j = 0; j < strlen(input.data[i]); j++) {
            result[index] = input.data[i][j];
            index++;
        }
    }
    return result;
}

/// @brief joins the given strings in the split_result with by 
/// @brief consumes the split_result (deallocates it)
/// @param input the strings to join with by
/// @param by the string to join the input with 
/// @return the resulting char array if input is joined with by 
char* cjoin(split_result input, char *by) {
    char *result = join(input, by);
    for (int i = 0; i < input.length; i++) {
        free(input.data[i]);
    }
    free(input.data);
    return result;
}

int main() {
    //printf("%s", readFile("some.txt"));
    // char *input = "a1a1a1a1a1a1a";
    // char *by = "a";
    // int subCount = substrCount(input, by);
    // printf("%d\n", subCount);
    // split_result r = split(input, by);
    // char **parts = r.data;
    // for (int i = 0; i < subCount + 1; i++) {
    //     printf("%s\n", parts[i]);
    // }
    // printf("%s\n", join(r, "a"));
    char *input = "halloichheiseejonathan";
    split_result r = csplit(input, "");
    
}