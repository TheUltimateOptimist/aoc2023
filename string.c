#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.c"

// working with files

long fgetSize(FILE *filepointer);
struct string readFile(char *fileName);


// working with strings

struct string {
    char *end;
    int (*isEmpty)();
    int (*isEmptyW)();
    struct string (*strAdd)(char *addition);
    int (*equals)(char *other);
    struct string (*substr)(long from, long to);
    int (*substrCount)(char *substr);
    int (*startsWith)(char *with);
    int (*endsWith)(char *with);
    struct string (*replace)(char *substr, char *with);
    struct string (*removeWhen)(int(*removePredicate)(char a));
    struct string (*trimLeft)();
    struct string (*trimLeftWith)(char with);
    struct string (*trimRight)();
    struct string (*trimRightWith)(char with);
    struct string (*trim)();
    struct string (*trimWith)(char with);
    struct stringarray (*split)(char* by);
};
struct string chain(char *input);
static struct string _createString(char *input);

int isEmpty(char *input);
static int _isEmpty();
int isEmptyW(char *input);
static int _isEmptyW();
char* strAdd(char *input, char *addition);
static struct string _strAdd(char *addition);
int strEquals(char *this, char *other);
int _strEquals(char *other);
char* substr(char *input, long from, long to);
static struct string _substr(long from, long to);
int substrCount(char *input, char *substr);
static int _substrCount(char *substr);
int startsWith(char *input, char *with);
static int _startsWith(char *with);
int endsWith(char *input, char *with);
static int _endsWith(char *with);
char* replace(char *input, char *substr, char *with);
struct string _replace(char *substr, char *with);
char* removeWhen(char *input, int(*removePredicate)(char a));
static struct string _removeWhen(int(*removePredicate)(char a));
char* trimLeft(char *input);
static struct string _trimLeft();
char* trimLeftWith(char *input, char with);
static struct string _trimLeftWith(char with);
char* trimRight(char *input);
static struct string _trimRight();
char* trimRightWith(char *input, char with);
static struct string _trimRightWith(char with);
char* trim(char *input);
static struct string _trim();
char* trimWith(char *input, char with);
static struct string _trimWith(char with);
char** split(char *input, char *by);
static struct stringarray _split(char* by);
static void _fillWithParts(char *input, char *substring, char **parts);


// working with an array of strings

struct stringarray {
    char **end;
    struct string (*get)(int index);
    struct string (*join)(char*);
    list (*collect)(void*(*map)(char *text), size_t elementSize);
    long* (*collectLong)(int* length);
};
int strarraylen(char **stringArray);
void strarrayfree(char **stringArray);
void strarrayprint(char **stringArray);
static struct stringarray _createStringArray(char **input);

char *get(char **input, int index);
static struct string _get(int index);
char* join(char **input, char *by);
static struct string _join(char *by);
list collect(char **input, void*(*map)(char *text), size_t elementSize);
static list _collect(void* (*map)(char *text), size_t elementSize);
long* collectLong(char **input, int *length);
static long* _collectLong(int *length);



//////////Start Definitions///////////////

// global variables for chain calling

void *global;
bool shouldConsume = false;

static void _replaceGlobalString(void *newGlobal) {
    if (shouldConsume) {
        free(global);
    }
    else {
        shouldConsume = true;
    }
    global = newGlobal;
}

static void _replaceGlobalStringArray(void *newGlobal) {
    if (shouldConsume) {
        strarrayfree(global);
    }
    else {
        shouldConsume = true;
    }
    global = newGlobal;
}


///files///

long fgetSize(FILE *filepointer) {
    fpos_t original;
    fgetpos(filepointer, &original);
    fseek(filepointer, 0, SEEK_END);
    long result = ftell(filepointer);
    fsetpos(filepointer, &original);
    return result;
}

struct string readFile(char *fileName) {
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
    fclose(filePointer);
    shouldConsume = true;
    global = content;
    return _createString(content);
}


///strings///

/// @brief creates a string from the char pointer to start a chain
/// @param input the char pointer to use as a starting point
/// @return a string
struct string chain(char *input) {
    shouldConsume = false;
    global = input;
    return _createString(input);
}

static struct string _createString(char *input) {
    struct string s = {
        input,
        _isEmpty,
        _isEmptyW,
        _strAdd,
        _strEquals,
        _substr,
        _substrCount,
        _startsWith,
        _endsWith,
        _replace,
        _removeWhen,
        _trimLeft,
        _trimLeftWith,
        _trimRight,
        _trimRightWith,
        _trim,
        _trimWith,
        _split
    };
    return s;
}

/// @brief checks if the given string is empty
/// @param input the string whose emptieness should be checked
/// @return empty - 1 nonempty - 0
int isEmpty(char* input) {
    return strlen(input) == 0;
}

static int _isEmpty() {
    int res = isEmpty(global);
    _replaceGlobalString(&res);
    return res;
}

/// @brief checks if the given string is empty if whitespace is ignored
/// @param input the string whose emptieness should be checked
/// @return empty - 1 nonempty - 0
int isEmptyW(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t') {
            return 0;
        }
    }
    return 1;
}

static int _isEmptyW() {
    int res = isEmptyW(global);
    _replaceGlobalString(&res);
    return res;
}

char *strAdd(char *input, char *addition) {
    unsigned long inputLength = strlen(input);
    unsigned long additionLength = strlen(addition);
    char *newString = malloc(inputLength + additionLength + 1);
    int index = 0;
    for (int i = 0; i < inputLength; i++, index++) {
        newString[index] = input[i];
    }
    for (int i = 0; i < additionLength; i++, index++) {
        newString[index] = addition[i];
    }
    newString[index] = '\0';
    return newString;
}

struct string _strAdd(char *addition) {
    char *res = strAdd(global, addition);
    _replaceGlobalString(res);
    return _createString(res);
}

int strEquals(char *this, char *other) {
    size_t thisLength = strlen(this);
    size_t otherLength = strlen(other);
    if (thisLength != otherLength) {
        return 0;
    }
    for (int i = 0; i < thisLength; i++) {
        if (this[i] != other[i]) {
            return 0;
        }
    }
    return 1;
}

int _strEquals(char *other) {
    int res = strEquals(global, other);
    _replaceGlobalString(&res);
    return res;
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

static struct string _substr(long from, long to) {
    char* res = substr(global, from, to);
    _replaceGlobalString(res);
    return _createString(res);
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

static int _substrCount(char *substr) {
    int res = substrCount(global, substr);
    _replaceGlobalString(&res);
    return res;
}

int startsWith(char *input, char *with) {
    unsigned long inputLength = strlen(input);
    unsigned long withLength = strlen(with);
    if (withLength > inputLength) {
        return 0;
    }
    for (int i = 0; i < withLength; i++) {
        if (i >= inputLength || input[i] != with[i]) {
            return 0;
        }
    }
    return 1;
}

static int _startsWith(char *with) {
    int res = startsWith(global, with);
    _replaceGlobalString(&res);
    return res;
}

int endsWith(char *input, char *with) {
    unsigned long inputLength = strlen(input);
    unsigned long withLength = strlen(with);
    if (withLength > inputLength) {
        return 0;
    }
    for (int i = 1; i <= withLength; i++) {
        if (inputLength - i < 0 || input[inputLength - i] != with[withLength - i]) {
            return 0;
        }
    }
    return 1;
}

static int _endsWith(char *with) {
    int res = endsWith(global, with);
    _replaceGlobalString(&res);
    return res;
}

char* replace(char *input, char *substr, char *with) {
    if (isEmpty(substr)) {
        return input;
    }
    char **parts = split(input, substr);
    char *res = join(parts, with);
    strarrayfree(parts);
    return res;
}

struct string _replace(char *substr, char *with) {
    char *res = replace(global, substr, with);
    _replaceGlobalString(res);
    return _createString(res);
}

/// @brief creates a new string with every character for which removePredicate returns 1 removed
/// @param input the string to remove characters from 
/// @param removePredicate a function that takes in a char and returns 1 if it should be removed
/// @return pointer to the newly created string
char* removeWhen(char *input, int(*removePredicate)(char a)) {
    unsigned long inputLength = strlen(input);
    int removeCount = 0;
    for (long i = 0; i < inputLength; i++) {
        if (removePredicate(input[i])) {
            removeCount++;
        }
    }
    char *newArray = malloc(inputLength - removeCount + 1);
    long index = 0;
    for (long i = 0; i < inputLength; i++) {
        if (!removePredicate(input[i])) {
            newArray[index] = input[i];
            index++;
        }
    }
    newArray[inputLength - removeCount] = '\0';
    return newArray;
}

static struct string _removeWhen(int(*removePredicate)(char a)) {
    char *res = removeWhen(global, removePredicate);
    _replaceGlobalString(res);
    return _createString(res);
}

/// @brief creates a new string with preceding whitespace removed
/// @param input the string whose prededing whitespace should be removed
/// @return pointer to the newly created string 
char* trimLeft(char *input) {
    unsigned long inputLength = strlen(input);
    int includeFrom = 0;
    while (input[includeFrom] == ' ' || input[includeFrom] == '\n' || input[includeFrom] == '\t') {
        includeFrom++;
    }
    return substr(input, includeFrom, inputLength - 1);
}

static struct string _trimLeft() {
    char *res = trimLeft(global);
    _replaceGlobalString(res);
    return _createString(res);
}

char* trimLeftWith(char *input, char with) {
    unsigned long inputLength = strlen(input);
    int includeFrom = 0;
    while (input[includeFrom] == ' ' || input[includeFrom] == '\n' || input[includeFrom] == '\t' || input[includeFrom] == with) {
        includeFrom++;
    }
    return substr(input, includeFrom, inputLength - 1);
}

static struct string _trimLeftWith(char with) {
    char *res = trimLeftWith(global, with);
    _replaceGlobalString(res);
    return _createString(res);
}

/// @brief creates a new string with trailing whitespace removed
/// @param input the string whose trailing whitespace should be removed
/// @return pointer to the newly created string 
char* trimRight(char *input) {
    unsigned long inputLength = strlen(input);
    int includeTil = inputLength - 1;
    while (input[includeTil] == ' ' || input[includeTil] == '\n' || input[includeTil] == '\t') {
        includeTil--;
    }
    return substr(input, 0, includeTil);
}

static struct string _trimRight() {
    char *res = trimRight(global);
    _replaceGlobalString(res);
    return _createString(res);
}

char* trimRightWith(char *input, char with) {
    unsigned long inputLength = strlen(input);
    int includeTil = inputLength - 1;
    while (input[includeTil] == ' ' || input[includeTil] == '\n' || input[includeTil] == '\t' || input[includeTil] == with) {
        includeTil--;
    }
    return substr(input, 0, includeTil);
}

static struct string _trimRightWith(char with) {
    char *res = trimRightWith(global, with);
    _replaceGlobalString(res);
    return _createString(res);
}

/// @brief creates a new string with prededing and trailing whitespace removed
/// @param input the string whose preceding and trailing whitespace should be removed 
/// @return pointer to the newly created string 
char* trim(char *input) {
    char *leftRemoved = trimLeft(input);
    char *rightRemoved = trimRight(leftRemoved);
    free(leftRemoved);
    return rightRemoved;
}

static struct string _trim() {
    char *res = trim(global);
    _replaceGlobalString(res);
    return _createString(res);
}

char* trimWith(char *input, char with) {
    char *leftRemoved = trimLeftWith(input, with);
    char *rightRemoved = trimRightWith(leftRemoved, with);
    free(leftRemoved);
    return rightRemoved;
}

static struct string _trimWith(char with) {
    char *res = trimWith(global, with);
    _replaceGlobalString(res);
    return _createString(res);
}

/// @brief splits the given input with by
/// @param input the string to split with by
/// @param by the string to split the input with 
/// @return a pointer to char pointers  
/// @return the pointer array is terminated with a NULL pointer
char** split(char *input, char *by) {
    unsigned long inputLength = strlen(input);
    if (strlen(by) == 0) {
        char **result = malloc((inputLength + 1)*sizeof(char *));
        for (int i = 0; i < inputLength; i++) {
            result[i] = malloc(2);
            result[i][0] = input[i];
            result[i][1] = '\0';
        }
        result[inputLength] = NULL;
        return result;
    }
    int occurrences = substrCount(input, by);
    char **result = malloc((occurrences+2)*sizeof(char *));
    _fillWithParts(input, by, result);
    result[occurrences + 1] = NULL;
    return result;
}

static struct stringarray _split(char* by) {
    char **res = split(global, by);
    _replaceGlobalString(res);
    return _createStringArray(res);
}

/// @brief Fills two dimensional char array parts with the remaining strings if input is split with substring
/// @param input the string to split with substring
/// @param substr the string input should be split by
/// @param parts the two dimensional string array that gets filled with the parts
static void _fillWithParts(char *input, char *substring, char **parts) {
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


///array of strings///

/// @brief determines the array length by iterating through until it reaches a NULL pointer
/// @param stringArray the string array whose length needs to be determined
/// @return the length of the string array 
int strarraylen(char **stringArray) {
    int length = 0;
    while(stringArray[length] != NULL) {
        length++;
    }
    return length;
}

/// @brief frees the memory of the given string array  
/// @brief only works if the string array is terminated by a NULL pointer
/// @param stringArray the string array whose memory should be freed
void strarrayfree(char **stringArray) {
    int index = 0;
    while (stringArray[index] != NULL) {
        free(stringArray[index]);
        index++;
    }
    free(stringArray[index]);
}

static struct stringarray _createStringArray(char **input) {
    struct stringarray s = {
        input,
        _get,
        _join,
        _collect,
        _collectLong
    };
    return s;
}

void strarrayprint(char **stringArray) {
    printf("[");
    for (int i = 0; i < strarraylen(stringArray); i++) {
        printf("'%s', ", stringArray[i]);
    }
    printf("]\n");
}

char* get(char **input, int index) {
    return input[index];
}

static struct string _get(int index) {
    char *res = get(global, index);
    char **parts = global;
    for (int i = 0; i < strarraylen(global); i++) {
        if (i != index) {
            free(parts[i]);
        }
    }
    free(global);
    global = res;
    return _createString(res);
}

/// @brief joins the given strings in the input with by  
/// @brief the array of strings needs to be terminated with a NULL pointer
/// @param input the strings to join with by 
/// @param by the string to join the input with 
/// @return the resulting char array if input is joined with by 
char* join(char **input, char *by) {
    int inputLength = strarraylen(input);
    unsigned long byLength = strlen(by);
    long size = 1;
    for (int i = 0; i < inputLength; i++) {
        if (i > 0) {
            size += byLength;
        }
        size += strlen(input[i]);
    }
    char *result = malloc(size);
    int index = 0;
    for (int i = 0; i < inputLength; i++) {
        if (i > 0) {
            for (int j = 0; j < byLength; j++) {
                result[index] = by[j];
                index++;
            }
        }
        for (int j = 0; j < strlen(input[i]); j++) {
            result[index] = input[i][j];
            index++;
        }
    }
    result[index] = '\0';
    return result;
}

static struct string _join(char *by) {
    char *res = join(global, by);
    _replaceGlobalStringArray(res);
    return _createString(res);
}

list collect(char **input, void* (*map)(char *text), size_t elementSize) {
    list collected = listCreate(elementSize);
    for (int i = 0; i < strarraylen(input); i++) {
        void *savedGlobal = global;
        void* result = map(input[i]);
        global = savedGlobal;
        if (result != NULL) {
            listAdd(&collected, result);
            free(result);
        }
    }
    return collected;
}

static list _collect(void* (*map)(char *text), size_t elementSize) {
    list res = collect(global, map, elementSize);
    _replaceGlobalStringArray(&res);
    return res;
}

long* collectLong(char **input, int *length) {
    int inputLength = strarraylen(input);
    int numberCount = 0;
    for (int i = 0; i < inputLength; i++) {
        if (!isEmptyW(input[i])) {
            numberCount++;
        }
    }
    long *numberList = malloc(numberCount*sizeof(long));
    if (length != NULL) {
        *length = numberCount;
    }
    numberCount = 0;
    char *end;
    for (int i = 0; i < inputLength; i++) {
        if (!isEmptyW(input[i])) {
            numberList[numberCount] = strtol(input[i], &end, 10);
            numberCount++;
        }
    }
    return numberList;
}

static long* _collectLong(int *length) {
    long *res = collectLong(global, length);
    _replaceGlobalStringArray(res);
    return res;
}