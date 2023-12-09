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

generic* findGeneric(genericslist *list, char *name) {
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->data[i].name, name) == 0) {
            return &list->data[i];
        }
    }
    return NULL;
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
        else if (substrCount(lines[i], "#define") && substrCount(lines[i], " T ")) {
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
    char *newDirPath = chain(dirPath).strAdd("/").strAdd("G").strAdd(name).end;
    if (mkdir(newDirPath, 0777) == 1) {
        perror("Error creating directory");
        exit(1);
    }
    for (int i = 0; i < defineCount; i++) {
        char *filePath = chain(newDirPath).strAdd("/").strAdd(realGenerics[i][0]).strAdd(name).strAdd(".c").end;
        FILE *filePointer = fopen(filePath, "w");
        char *content = chain(sourceCode).replace("N", realGenerics[i][0]).replace("T", realGenerics[i][1]).end;
        fprintf(filePointer, "%s", content);
        free(content);
        free(filePath);
        fclose(filePointer);
        strarrayfree(realGenerics[i]);
    }
    generic gen = {.name = name, .sourceCode = sourceCode};
    strarrayfree(newLines);
    free(lines);
    return gen;
}

void createFileGenerics(DIR *dir, char *path, genericslist *generics) {
    struct dirent *entry;
    while (1) {
        entry = readdir(dir);
        if (entry == NULL) {
            break;
        }
        if (entry->d_type == 4 && entry->d_name[0] != '.' && entry->d_name[0] != 'G') { // 4 -> directory
            char *newPath = chain(path).strAdd("/").strAdd(entry->d_name).end;
            DIR *nextDir = opendir(newPath);
            createFileGenerics(nextDir, newPath, generics);
            free(newPath);
            closedir(nextDir);
        }
        else if (entry->d_type == 8 && endsWith(entry->d_name, ".c") && !endsWith(entry->d_name, "generics.c") && !startsWith(entry->d_name, "G")) { // 8 -> file
            char *filePath = chain(path).strAdd("/").strAdd(entry->d_name).end;
            char **lines = readFile(filePath).split("\n").end;
            int genericsCount = 0;
            for (int i = 0; lines[i] != NULL; i++) {
                if (substrCount(lines[i], "#define") && substrCount(lines[i], " NT ")) {
                    genericsCount++;
                }
            }
            if (!genericsCount) {
                continue;
            }
            char *newFilePath = chain(filePath).split(".c").get(0).strAdd("_gen.c").end;
            FILE *filePointer = fopen(newFilePath, "w");
            if (filePointer == NULL) {
                printf("opening file %s failed!\n", newFilePath);
            }
            for (int i = 0; lines[i] != NULL; i++) {
                if (substrCount(lines[i], "#define") && substrCount(lines[i], " NT ")) {
                    char **parts = chain(lines[i]).split("NT").get(1).trim().split(";").end;
                    generic *gen = findGeneric(generics, parts[0]);
                    if (gen == NULL) {
                        printf("Invalid generic name: %s!\n", parts[0]);
                        exit(1);
                    }
                    fprintf(filePointer, "// Code for generic: %s\n", gen->name);
                    char *content = chain(gen->sourceCode).replace("N", parts[1]).replace("T", parts[2]).end;
                    fprintf(filePointer, "%s\n\n", content);
                    free(content);
                    strarrayfree(parts);
                }
            }
            fclose(filePointer);
            free(newFilePath);
        }
    }
}


int main() {
    DIR *dir = opendir(".");
    genericslist list = createGenericsList();
    char *path = getcwd(NULL, 0);
    extractGenerics(dir, path, &list);
    closedir(dir);
    dir = opendir(".");
    createFileGenerics(dir, path, &list);
    closedir(dir);
}
