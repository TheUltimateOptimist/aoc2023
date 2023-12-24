#include <stdio.h>
#include "../string.c"

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

void* mapToNode(char *text) {
    Node *node = malloc(sizeof(Node));
    node->name = chain(text).trim().split(" = ").get(0).end;
    node->left = chain(text).trim().split(" = ").get(1).removeWhen(shouldRemove).split(", ").get(0).end;
    node->right = chain(text).trim().split(" = ").get(1).removeWhen(shouldRemove).split(", ").get(1).end;
    return node;
}

void printNode(void *a) {
    Node *node = a;
    printf("Node %s;%s;%s", node->name, node->left, node->right);
}

int main() {
    char **blocks = readFile("adventofcode.com_2023_day_8_input.txt").split("\n\n").end;
    char *directions = trim(blocks[0]);
    size_t dirLength = strlen(directions);
    list nodes = chain(blocks[1]).trim().split("\n").collect(mapToNode, sizeof(Node));
    //listPrint(&nodes, printNode);
    Node *nextNode = listGet(&nodes, 0);
    int index = 1;
    while(substrCount(nextNode->name, "AAA") == 0) {
        nextNode = listGet(&nodes, index);
        index++;
    }
    int steps = 0;
    int dirIndex = 0;
    while(substrCount(nextNode->name, "ZZZ") == 0) {
        char *target = nextNode->left;
        if (directions[dirIndex] == 'R') {
            target = nextNode->right;
        }
        for (int i = 0; i < nodes.length; i++) {
            Node *cNode = listGet(&nodes, i);
            if (substrCount(cNode->name, target) == 1) {
                nextNode = cNode;
                steps++;
                dirIndex++;
                break;
            }
        }
        if (dirIndex == dirLength) {
            dirIndex = 0;
        }
    }
    printf("steps = %d\n", steps);
}