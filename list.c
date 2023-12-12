#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIALSIZE 8

//list implementation with resizing arrays (insertion with O(1) amortified)
typedef struct list {
    size_t length;
    size_t capacity;
    size_t elementSize; 
    void *data;
} list;

list listCreate(size_t elementSize) {
    void *data = malloc(INITIALSIZE*elementSize);
    list new = {.capacity = INITIALSIZE, .length = 0, .data = data, .elementSize = elementSize};
    return new;
}

void listAdd(list *list, void *new) {
    if (list->capacity == list->length) {
        list->capacity = 2*list->capacity;
        void *newAlloc = realloc(list->data, list->capacity*list->elementSize);
        if (newAlloc == NULL) {
            printf("reallocation failed!\n");
            exit(1);
        }
        list->data = newAlloc;
    }
    memcpy((char*)list->data + list->length * list->elementSize, new, list->elementSize);
    list->length++;
}

void* listPop(list *list) {
    if (list->capacity > 8 && list->capacity / list->length == 4) {
        list->capacity = list->capacity / 2;
        list->data = realloc(list->data, list->capacity*list->elementSize);
    }
    list->length--;
    return (char*)list->data + list->length*list->elementSize;
}

void* listGet(list *list, int index) {
    if (index < 0) {
        index = list->length + index;
    }
    if (index < 0 || index >= list->length) {
        printf("EXITED: Index %d not in 0..%lu!\n", index, list->length - 1);
        exit(1);
    }
    return (char*)list->data + index*list->elementSize;
}