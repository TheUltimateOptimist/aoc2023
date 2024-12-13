#include <stdio.h>
#include <time.h>

typedef struct File {
    int id;
    int pos;
    int size;
} File;

typedef struct Space {
    int pos;
    int size;
    int maxsize;
} Space;

typedef union Object {
    File file;
    Space space;
} Object;

void printfs(Object objects[], int length) {
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            printf("id: %d;si: %d;po: %d|", objects[i].file.id, objects[i].file.size, objects[i].file.pos);
        }
        else {
            printf("mi: %d;si: %d;po: %d|", objects[i].space.maxsize, objects[i].space.size, objects[i].space.pos);
        }
    }
    printf("\n");
}

int main() {
    FILE *file = fopen("input.txt", "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Seek to the end to determine file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file); // Reset file pointer to the beginning 
    char buffer[file_size + 1];
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';

    Object objects[bytes_read];
    int id = 0;
    int pos = 0;
    for (int i = 0; i < bytes_read; i++) {
        Object object;
        if (i % 2 == 0) {
            File file = {.id = id, .pos = pos, .size = buffer[i] - '0'};
            object.file = file;
            id += 1;
        }
        else {
            Space space = {.pos = pos, .size = buffer[i] - '0', .maxsize = buffer[i] - '0'};
            object.space = space;
        }
        pos += buffer[i] - '0';
        objects[i] = object; 
    }

    printfs(objects, bytes_read);
    fflush(stdout);
     clock_t start, end;
    double time_taken;

    // Start measuring time
    start = clock();

    int jumper[] = {1,1,1,1,1,1,1,1,1,1};
    int index = bytes_read - 1;
    int previousId = -1;
    if (index % 2 != 0) {
        index--;
    }
    while (index >= 0) {
        File file = objects[index].file;
        if (previousId != -1 && file.id != previousId - 1) {
            index -= 2;
            continue;
        }
        int sindex = jumper[file.size];
        while (sindex < index) {
            Space space = objects[sindex].space;
            if (space.size >= file.size) {
                objects[index].file.pos = space.pos + (space.maxsize - space.size);
                objects[sindex].space.size = space.size - file.size;
                break;
            }
            sindex += 2;
        }
        jumper[file.size] = sindex;
        index-=2;
    }

long double sum = 0;
for (int i = 0; i < bytes_read; i+=2) {
    Space space = objects[i].space;
    File file = objects[i].file;
    for (int k = 0; k < file.size; k++) {
        sum += (file.pos + k)*file.id;
    }
}
 end = clock();

    // Calculate time taken in milliseconds
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;  // milliseconds

    printf("Time taken: %.3f milliseconds\n", time_taken);
printf("%Lf\n", sum);
    /**

index = len(fs) - 1
previousid: int | None = None
while index >= 0:
    object = fs[index]
    if isinstance(object, File) and (previousid == None or object.id == previousid - 1):
        previousid = object.id
        sindex = jump_list[object.size]
        while sindex < index:
            second = fs[sindex]
            if isinstance(second, Space) and second.size >= object.size:
                fs[index] = File(object.id, second.pos + (second.maxsize - second.size), object.size)
                fs[sindex] = Space(second.pos, second.size - object.size, second.maxsize)
                break
            sindex += 1
        jump_list[object.size] = sindex
    index -= 1

sum = 0
for entry in fs:
    if isinstance(entry, File):
        for i in range(entry.size):
            sum += (entry.pos + i)*entry.id 
     * 
     */
}