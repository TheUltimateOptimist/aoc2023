#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

static size_t  _findNextPowerOf2(size_t length) {
    size_t start = 8;
    while(start <= length) {
        start *= 2;
    }
    return start;
}

list listCreateFrom(void *data, size_t elementSize, size_t length) {
    size_t capacity = _findNextPowerOf2(length);
    void *listData = malloc(capacity*elementSize);
    for (int i = 0; i < length; i++) {
        memcpy((char*)listData + i*elementSize, (char*)data + i*elementSize, elementSize);
    }
    list res = {.capacity = capacity, .data = listData, .elementSize = elementSize, .length = length};
    return res;
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

void listPrint(list *list, void (*printElement)(void* element)) {
    printf("[");
    for (int i = 0; i < list->length; i++) {
        printElement((char*) list->data + i*list->elementSize);
        if (i < list->length - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void* listPop(list *list) {
    if (list->length == 0) {
        return NULL;
    }
    if (list->capacity > 8 && list->capacity / list->length == 4) {
        list->capacity = list->capacity / 2;
        list->data = realloc(list->data, list->capacity*list->elementSize);
    }
    list->length--;
    return (char*)list->data + list->length*list->elementSize;
}

void listClear(list *list) {
    free(list->data);
    list->data = malloc(INITIALSIZE*list->elementSize);
    list->length = 0;
    list->capacity = INITIALSIZE;
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