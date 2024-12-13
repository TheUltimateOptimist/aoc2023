#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INITIALSIZE 8
#define SOME(...) __VA_ARGS__[0]
#define LIST(type, name) \
    typedef struct name##_list {\
        size_t length;\
        size_t capacity;\
        size_t elementSize;\
        type *data;\
        void (*add)(struct name##_list self, type *value);\
        void (*set)(struct name##_list self, int at, type *value);\
        type (*get)(struct name##_list self, int at);\
        type (*pop)(struct name##_list self);\
        type (*popAt)(struct name##_list self, int at);\
        void (*clear)(struct name##_list self);\
    } name##_list;\
    name##_list name##_list_create() {\
        name##_list new_list;\
        new_list.length = 0;\
        new_list.capacity = INITIALSIZE;\
        new_list.elementSize = sizeof(type);\
        new_list.data = malloc(INITIALSIZE*sizeof(type));\
        new_list.add = (void (*)(name##_list self, type *value)) listAdd;\
        new_list.set = (void (*)(name##_list self, int at, type *value)) listSet;\
        new_list.get = (type (*)(name##_list self, int at)) listGet;\
        new_list.pop = (type (*)(name##_list self)) listPop;\
        new_list.popAt = (type (*)(name##_list self, int at)) listPopAt;\
        new_list.clear = (void (*)(name##_list self)) listClear;\
        return new_list;\
    }


//list implementation with resizing arrays (insertion in O(1) amortized)
typedef struct list {
    size_t length;
    size_t capacity;
    size_t elementSize; 
    void *data;
} list;

SOME(hallo, 4)

static int _parseIndex(list *list, int index) {
    if (index < 0) {
        index = list->length + index;
    }
    if (index < 0 || index >= list->length) {
        printf("WARNING: Index %d not in 0..%lu!\n", index, list->length - 1);
    }
    return index;
}

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

void listSet(list *list, int at, void *new) {
    memcpy((char*)list->data + _parseIndex(list, at) * list->elementSize, new, list->elementSize);
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
    void *result = malloc(list->elementSize);
    memcpy(result, (char*)list->data + list->length*list->elementSize, list->elementSize);
    list->length--;
    return result;
}

void* listPopAt(list *list, int at) {
    at = _parseIndex(list, at);
    if (at < 0 || at >= list->length) {
        return NULL;
    }
    if (list->length == 1) {
        return listPop(list);
    }
    if (list->capacity > 8 && list->capacity / list->length == 4) {
        list->capacity = list->capacity / 2;
        list->data = realloc(list->data, list->capacity*list->elementSize);
    }
    void *result = malloc(list->elementSize);
    memcpy(result, (char*)list->data + at*list->elementSize, list->elementSize);
    for (int i = at; i < list->length - 1; i++) {
            listSet(list, i, (char*)list->data + (i + 1)*list->elementSize);
    }
    list->length--;
    return result;
}


void listClear(list *list) {
    free(list->data);
    list->data = malloc(INITIALSIZE*list->elementSize);
    list->length = 0;
    list->capacity = INITIALSIZE;
}

void* listGet(list *list, int index) {
    index = _parseIndex(list, index);
    if (index < 0 || index >= list->length) {
        return NULL;
    } 
    return (char*)list->data + _parseIndex(list, index)*list->elementSize;
}

void* create(void *a) {
    return a;
}

LIST(int, int)

int main() {
    int_list another = int_list_create();
    for (int i = 0; i < 20; i++) {
        another.add(another, *(i + 100));
    }
    printf("%lu\n", another.capacity);
    for (int i = 0; i < another.length; i++) {
        printf("%d = %d\n", i, another.get(another, i));
    }
    // struct some {
    //     int (*create)(int a);
    // };

    // struct some another;
    // another.create = (int (*)(int)) create;
    // printf("%d\n", another.create(4));
}