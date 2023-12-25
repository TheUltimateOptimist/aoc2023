#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "string.c"

typedef struct Option {
    
} Option;

typedef struct LeafCommand {

    int a;
} LeafCommand;

typedef struct NodeCommand {
    NodeCommand *nodeCommands;
    LeafCommand *leafCommands;
} NodeCommand;

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