#include <stdio.h>
#include <stdlib.h>

#define INITIALSIZE 8
#define NT i;int
#define NT u;unsigned int
#define NT ld;long
#define T int

typedef struct Nlist {
    T length;
    T capacity;
    T *data;
} Nlist;

Nlist NlistCreate() {
    T *data = malloc(INITIALSIZE*sizeof(T));
    Nlist new = {.capacity = INITIALSIZE, .length = 0, .data = data};
    return new;
}

void NlistAdd(Nlist *list, int new) {
    if (list->capacity == list->length) {
        list->capacity = 2*list->capacity;
        list->data = realloc(list->data, list->capacity*sizeof(T));
    }
    list->data[list->length] = new; 
    list->length++;
}

T NlistPop(Nlist *list) {
    if (list->capacity > 8 && list->capacity / list->length == 4) {
        list->capacity = list->capacity / 2;
        list->data = realloc(list->data, list->capacity*sizeof(T));
    }
    list->length--;
    return list->data[list->length];
}

T NlistGet(Nlist *list, int index) {
    if (index < 0) {
        index = list->length + index;
    }
    if (index < 0 || index >= list->length) {
        printf("EXITED: Index %d not in 0..%d!\n", index, list->length - 1);
        exit(1);
    }
    return list->data[index];
}

// int main() {
//     intlist list = intlistCreate();
//     for (int i = 0; i < 1000; i++) {
//         intlistAdd(&list, i); 
//     }
//     int capacity = list.capacity;
//     while(list.capacity == capacity) {
//         intlistPop(&list);
//     }
//     printf("%d\n", list.length);
//     printf("%d\n", list.capacity);
// }