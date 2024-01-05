#ifndef LOL_H
#define LOL_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct PARSER PARSER;
PARSER* parget();
void pardescribeShort(PARSER *parser, void *field, char *description);
void pardescribeLong(PARSER *parser, void *field, char *description);
void parsmaller(PARSER *parser, void *field, double than);
void parsmallerEquals(PARSER *parser, void *field, double than);
void pargreater(PARSER *parser, void *field, double than);
void pargreaterEquals(PARSER *parser, void *field, double than);
void parse(PARSER* parser, char **argv);

int* paraddPosInt(PARSER *parser, char *name);
int* paraddOptInt(PARSER *parser, char *name, int value);
//void parintFiniteValues(INT *parameter,  long long int possibleValues[], size_t length);

double* paraddPosDouble(PARSER *parser, char *name);
double* paraddOptDouble(PARSER *parser, char *name, double value);
//void pardoubleFiniteValues(DOUBLE *parameter, double possibleValues[], size_t length);

char** paraddPosString(PARSER *parser, char *name);
char** paraddOptString(PARSER *parser, char *name, char *value);
//void parstringFiniteValues(STRING *parameter, char **possibleValues, size_t length);

bool* paraddFlag(PARSER *parser, char *name);
#endif 