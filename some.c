#include <stdio.h>
#include "parser.h"
#include <stdlib.h>
#include <stdbool.h>

int add(int a, int b, char *third, bool yes) {
    printf("third: %s\n", third);
    printf("%d + %d = %d\n", a, b, a + b);
}

int main(int argc, char **argv) {
    PARSER *parser = parget();
    pardescribeShort(parser, NULL, "some command");
    pardescribeLong(parser, NULL, "a long description");
    //FLAG *noexecute = paraddFlag("no-execute", false);
    //FLAG *execute = paraddFlag("execute", true);
    int *first = paraddPosInt(parser, "first");
    pargreater(parser, first, 10);
    parsmallerEquals(parser, first, 15);
    double *second = paraddPosDouble(parser, "second");
    parsmaller(parser, second, 4.5);
    char **third = paraddOptString(parser, "third", "default");
    pargreaterEquals(parser, third, 10);
    bool *flag = paraddFlag(parser, "flag");
    parse(parser, argv);
    add(*first, *second, *third, *flag);
}