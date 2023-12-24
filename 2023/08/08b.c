#include <stdio.h>
#include "../string.c"
#include <math.h>

typedef struct Node {
    char *name;
    char *left;
    char *right;
} Node;

int shouldRemove(char a) {
    if (a == ')' || a == '(') {
        return 1;
    }
    return 0;
}

long kgv(long a, long b) {
    if (b > a) {
        //tausche a und b
        a = a + b;
        b = a - b;
        a = a - b;
    }
    while(a % b != 0) {
        long rest = a % b;
        a = b;
        b = rest;
    }
    return b;
}

void* mapToNode(char *text) {
    Node *node = malloc(sizeof(Node));
    node->name = chain(text).trim().split(" = ").get(0).end;
    node->left = chain(text).trim().split(" = ").get(1).removeWhen(shouldRemove).split(", ").get(0).end;
    node->right = chain(text).trim().split(" = ").get(1).removeWhen(shouldRemove).split(", ").get(1).end;
    return node;
}

int isFinished(list *nodes) {
    for (int i = 0; i < nodes->length; i++) {
        Node *cNode = listGet(nodes, i);
        if (!endsWith(cNode->name, "Z")) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char **blocks = readFile("adventofcode.com_2023_day_8_input.txt").split("\n\n").end;
    //char **blocks = readFile("test.txt").split("\n\n").end;
    char *directions = trim(blocks[0]);
    size_t dirLength = strlen(directions);
    list nodes = chain(blocks[1]).trim().split("\n").collect(mapToNode, sizeof(Node));
    list nextNodes = listCreate(sizeof(Node));
    for (int i = 0; i < nodes.length; i++) {
        Node *cNode = listGet(&nodes, i);
        if (endsWith(cNode->name, "A")) {
            listAdd(&nextNodes, cNode);
        }
    }
    long steps = 0;
    int dirIndex = 0;
    long stepsToZ[] = {0, 0, 0, 0, 0, 0};
    while(!isFinished(&nextNodes)) {
        for (int i = 0; i < nextNodes.length; i++) {
            Node *nextNode = listGet(&nextNodes, i);
            if (endsWith(nextNode->name, "Z")) {
                continue;
            }
            char *target = nextNode->left;
            if (directions[dirIndex] == 'R') {
                target = nextNode->right;
            }
            for (int j = 0; j < nodes.length; j++) {
                Node *cNode = listGet(&nodes, j);
                if (substrCount(cNode->name, target) == 1) {
                    listSet(&nextNodes, i, cNode);
                    if (endsWith(cNode->name, "Z")) {
                        stepsToZ[i] = steps + 1;
                    }
                    break;
                }
            }
        }
        steps++;
        dirIndex++;
        if (dirIndex == dirLength) {
            dirIndex = 0;
        }
        
    }

    long result = 1;
    for (int i = 0; i < 6; i++) {
        result = result * stepsToZ[i] / kgv(result, stepsToZ[i]);
    }
    printf("steps = %ld\n", result);
}