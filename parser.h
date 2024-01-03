#ifndef LOL_H
#define LOL_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct PARSER PARSER;
PARSER* parget();
void parshortDescription(PARSER *parser, char *description);
void parlongDescription(PARSER *parser, char *description);
void parse(PARSER* parser, char **argv);

typedef struct INT INT;
long long int parintValue(INT *parameter);
INT* paraddPosInt(PARSER *parser, char *name);
INT* paraddOptInt(PARSER *parser, char *name, long long int value);
void parintShortDescription(INT *parameter, char *description);
void parintLongDescription(INT *parameter, char *description);
void parintGreater(INT *parameter, long long int than);
void parintSmaller(INT *parameter, long long int than);
void parintGreaterEquals(INT *parameter, long long int than);
void parintSmallerEquals(INT *parameter, long long int than);
//void parintFiniteValues(INT *parameter,  long long int possibleValues[], size_t length);

typedef struct DOUBLE DOUBLE;
double pardoubleValue(DOUBLE *parameter);
DOUBLE* paraddPosDouble(PARSER *parser, char *name);
DOUBLE* paraddOptDouble(PARSER *parser, char *name, double value);
void pardoubleShortDescription(DOUBLE *parameter, char *description);
void pardoubleLongDescription(DOUBLE *parameter, char *description);
void pardoubleGreater(DOUBLE *parameter, double than);
void pardoubleSmaller(DOUBLE *parameter, double than);
void pardoubleGreaterEquals(DOUBLE *parameter, double than);
void pardoubleSmallerEquals(DOUBLE *parameter, double than);
//void pardoubleFiniteValues(DOUBLE *parameter, double possibleValues[], size_t length);

typedef struct STRING STRING;
char *parstringValue(STRING *parameter);
STRING* paraddPosString(PARSER *parser, char *name);
STRING* paraddOptString(PARSER *parser, char *name, char *value);
void parstringShortDescription(STRING *parameter, char *description);
void parstringLongDescription(STRING *parameter, char *description);
void parstringMinLength(STRING *parameter, size_t length);
void parstringMaxLength(STRING *parameter, size_t length);
//void parstringFiniteValues(STRING *parameter, char **possibleValues, size_t length);

typedef struct FLAG FLAG;
bool parflagValue(FLAG *flag);
FLAG* paraddFlag(PARSER *parser, char *name);
void parflagShortDescription(FLAG *flag, char *description);
void parflagLongDescription(FLAG *flag, char *description);
#endif 