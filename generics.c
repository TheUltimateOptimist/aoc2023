#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "string.c"

#define IDENTIFIER "<generic>"

typedef struct generic {
    char *name;
    char *sourceCode;
} generic;

typedef struct genericslist {
    unsigned long length;
    unsigned long capacity;
    generic *data;
    
} genericslist;


generic createGeneric(char **lines, char *fileName, char *dirPath);

void genericAdd(genericslist *list, generic gen) {
    if (list->length == list->capacity) {
        list->data = realloc(list->data, 2*list->length*sizeof(generic));
        list->capacity*=2;
    }
    list->data[list->length] = gen;
    list->length++;
}

genericslist createGenericsList() {
    unsigned long initialSize = 8;
    genericslist l = {
        .capacity = 8,
        .length = 0,
        .data = malloc(initialSize*sizeof(generic))
    };
    return l;
}

void extractGenerics(DIR *dir, char *path, genericslist *generics) {
    struct dirent *entry;
    while (1) {
        entry = readdir(dir);
        if (entry == NULL) {
            break;
        }
        if (entry->d_type == 4 && entry->d_name[0] != '.') { // 4 -> directory
            char *newPath = chain(path).strAdd("/").strAdd(entry->d_name).end;
            DIR *nextDir = opendir(newPath);
            extractGenerics(nextDir, newPath, generics);
            free(newPath);
            closedir(nextDir);
        }
        else if (entry->d_type == 8 && startsWith(entry->d_name, "G") && endsWith(entry->d_name, ".c")) { // 8 -> file
            char *filePath = chain(path).strAdd("/").strAdd(entry->d_name).end;
            char **lines = readFile(filePath).split("\n").end;
            genericAdd(generics, createGeneric(lines, entry->d_name, path));

        }
    }
}

generic createGeneric(char **lines, char *fileName, char *dirPath) {
    int defineCount = 0;
    for (int i = 0; lines[i] != NULL; i++) {
        if (substrCount(lines[i], "#define") && substrCount(lines[i], "NT")) {
            defineCount++;
        } 
    }
    char **realGenerics[defineCount];
    char **newLines = malloc((strarraylen(lines) - defineCount + 1)*sizeof(char*));
    int index = 0;
    int newIndex = 0;
    for (int i = 0; lines[i] != NULL; i++) {
        if (substrCount(lines[i], "#define") && substrCount(lines[i], "NT")) {
            char **parts = chain(lines[i]).split("NT").get(1).trim().split(";").end;
            realGenerics[index] = parts;
            index++;
            free(lines[i]);
        }
        else if (substrCount(lines[i], "#define") && substrCount(lines[i], "T")) {
            continue;
        }
        else {
            newLines[newIndex] = lines[i];
            newIndex++;
        }
    }
    newLines[newIndex] = NULL;
    char *sourceCode = join(newLines, "\n");
    char *name = chain(fileName).split(".c").get(0).split("G").get(1).end;  
    for (int i = 0; i < defineCount; i++) {
        char *newDirPath = chain(dirPath).strAdd("/").strAdd(name).end;
        if (mkdir(newDirPath, 0777) == 0) {
            char *filePath = chain(newDirPath).strAdd("/").strAdd(realGenerics[i][0]).strAdd(name).strAdd(".c").end;
            FILE *filePointer = fopen(filePath, "w");
            char *content = chain(sourceCode).replace("N", realGenerics[i][0]).replace("T", realGenerics[i][1]).end;
            fprintf("%s", content);
            free(content);
            free(filePath);
            fclose(filePointer);
        } else {
            perror("Error creating directory");
            exit(1);
        } 
        strarrayfree(realGenerics[i]);
    }
    generic gen = {.name = name, .sourceCode = sourceCode};
    strarrayfree(newLines);
    free(lines);
    return gen;
}




int main() {
    DIR *dir = opendir(".");
    genericslist list = createGenericsList();
    char *path = getcwd(NULL, 0);
    extractGenerics(dir, path, &list);
    printf("%lu\n", list.length);
    for (int i = 0; i < list.length; i++) {
        printf("name: %s\ncode:\n%s\n", list.data[i].name, list.data[i].sourceCode);
    }
}
