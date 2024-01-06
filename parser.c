#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "string.c"
#include <math.h>

//TODO: when adding parameters the names need to be validated
//also see if name is available
//TODO: --help
#define ERROR_FLAG_CONSTRAINT(functionName) \
    #functionName" failed with the following Exception:\n"\
    "Can not add a constraint to a boolean flag.\n"\
    "You tried to apply "#functionName" to a flag."

char* ERROR_PARAM_MISSING(char *paramName) {
    return chain("No value was given for the parameter ").
        strAdd(paramName).
        strAdd(".\n").
        strAdd("Please make sure to provide a value for ").
        strAdd(paramName).
        end;
}

char* ERROR_UNRECOGNIZED_INPUT(char *input) {
    return chain("Unrecognized Input: '").strAdd(input).strAdd("'").end;
}

char* ERROR_NOT_AN_INT(char *input, char *paramName) {
    return chain("Converting '"). 
        strAdd(input).strAdd("'"). 
        strAdd(" failed!\n"). 
        strAdd("Please make sure to provide a valid integer for "). 
        strAdd(paramName). 
        end;
}

char* ERROR_NOT_A_DOUBLE(char *input, char *paramName) {
    return chain("Converting '"). 
        strAdd(input).strAdd("'"). 
        strAdd(" failed!\n"). 
        strAdd("Please make sure to provide a valid decimal number for "). 
        strAdd(paramName). 
        end;
}

char* ERROR_STRING_TO_SHORT(char *input, char *paramName, size_t minLength) {
    char buffer[20];
    sprintf(buffer, "%lu", minLength);
    return chain("'").strAdd(input).strAdd("' is too short.\n"). 
        strAdd("The string for ").strAdd(paramName). 
        strAdd(" needs to be at least "). 
        strAdd(buffer).strAdd(" characters long.").end;
}

char* ERROR_STRING_TO_LONG(char *input, char *paramName, size_t maxLength) {
    char buffer[20];
    sprintf(buffer, "%lu", maxLength);
    return chain("'").strAdd(input).strAdd("' is too long.\n"). 
        strAdd("The string for ").strAdd(paramName). 
        strAdd(" can't be more than "). 
        strAdd(buffer).strAdd(" characters long.").end;
}

char *ERROR_NOT_SMALLER(double input, char *paramName, double smaller) {
    char inputBuffer[50];
    char smallerBuffer[50];
    sprintf(inputBuffer, "%lf", input);
    sprintf(smallerBuffer, "%lf", smaller);
    return chain(inputBuffer). 
        strAdd(" is not smaller than ").strAdd(smallerBuffer). 
        strAdd(".\n"). 
        strAdd("The value for ").strAdd(paramName). 
        strAdd(" needs to be smaller than ").strAdd(smallerBuffer).
        strAdd(".").end;
}

char *ERROR_NOT_SMALLEREQUALS(double input, char *paramName, double smallerEquals) {
    char inputBuffer[50];
    char smallerEqualsBuffer[50];
    sprintf(inputBuffer, "%lf", input);
    sprintf(smallerEqualsBuffer, "%lf", smallerEquals);
    return chain(inputBuffer). 
        strAdd(" is not smaller or equal to ").strAdd(smallerEqualsBuffer). 
        strAdd(".\n"). 
        strAdd("The value for ").strAdd(paramName). 
        strAdd(" needs to be smaller or equal to ").strAdd(smallerEqualsBuffer).
        strAdd(".").end;
}

char *ERROR_NOT_GREATER(double input, char *paramName, double greater) {
    char inputBuffer[50];
    char greaterBuffer[50];
    sprintf(inputBuffer, "%lf", input);
    sprintf(greaterBuffer, "%lf", greater);
    return chain(inputBuffer). 
        strAdd(" is not greater than ").strAdd(greaterBuffer). 
        strAdd(".\n"). 
        strAdd("The value for ").strAdd(paramName). 
        strAdd(" needs to be greater than ").strAdd(greaterBuffer).
        strAdd(".").end;
}

char *ERROR_NOT_GREATEREQUALS(double input, char *paramName, double greaterEquals) {
    char inputBuffer[50];
    char greaterEqualsBuffer[50];
    sprintf(inputBuffer, "%lf", input);
    sprintf(greaterEqualsBuffer, "%lf", greaterEquals);
    return chain(inputBuffer). 
        strAdd(" is not greater or equal to ").strAdd(greaterEqualsBuffer). 
        strAdd(".\n"). 
        strAdd("The value for ").strAdd(paramName). 
        strAdd(" needs to be greater or equal to ").strAdd(greaterEqualsBuffer).
        strAdd(".").end;
}

static size_t getMinLength(double value, bool inclusive) {
    if (value == round(value)) {
        return inclusive ? value : value + 1; 
    }
    return ceil(value);
}

static size_t getMaxLength(double value, bool inclusive) {
    if (value == round(value)) {
        return inclusive ? value : value - 1;
    }
    return floor(value);
}

typedef struct Constraints {
    double *greater;
    double *smaller;
    double *greaterEquals;
    double *smallerEquals;
} Constraints;

typedef struct FieldInfo {
    char *name;
    char *shortDescription;
    char *longDescription;
} FieldInfo;

typedef enum DataType {
    tint,
    tdouble,
    tstring
} DataType;

typedef struct Parameter {
    FieldInfo info;
    Constraints constraints;
    void *identifier; //double* or int* or char**
    void *value;// double* or int* or char**
    DataType dataType;
} Parameter;

typedef struct Flag {
    FieldInfo info;
    int *identifier;
} Flag;

typedef struct PARSER {
    char *shortDescription;
    char *longDescription;
    list positionalParameters;
    list optionalParameters;
    list flags;
    bool hasParsed;
} PARSER;

void raise(char *exception) {
    printf("%s\n", exception);
    exit(1);
}

PARSER* parget() {
    PARSER *parser = malloc(sizeof(PARSER));
    parser->shortDescription = NULL;
    parser->longDescription = NULL;
    parser->positionalParameters = listCreate(sizeof(Parameter));
    parser->optionalParameters = listCreate(sizeof(Parameter));
    parser->flags = listCreate(sizeof(Flag));
    parser->hasParsed = false;
    return parser;
}

static char* strclone(char *input) {
    size_t inputLength = strlen(input);
    char *clone = malloc((inputLength + 1)*sizeof(char));
    for (int i = 0; i < inputLength; i++) {
        clone[i] = input[i];
    }
    clone[inputLength] = '\0';
    return clone;
}

FieldInfo* findFieldInfo(PARSER *parser, void *field) {
    int id = *((int*)field);
    switch (id % 3) {
        case 0: {
            Flag *flag = listGet(&parser->flags, id / 3);
            return &flag->info;
        }
        case 1: {
            Parameter *parameter = listGet(&parser->positionalParameters, (id - 1) / 3);
            return &parameter->info;
        }
        case 2: {
            Parameter *parameter = listGet(&parser->optionalParameters, (id - 2) / 3);
            return &parameter->info;
        }
        default: raise("findFieldInfo: unexpected exception!");
    }
}

Constraints* findConstraints(PARSER *parser, void *field) {
    int id = *((int*)field);
    switch (id % 3) {
        case 0: return NULL;
        case 1: {
            Parameter *parameter = listGet(&parser->positionalParameters, (id - 1) / 3);
            return &parameter->constraints;
        }
        case 2: {
            Parameter *parameter = listGet(&parser->optionalParameters, (id - 2) / 3);
            return &parameter->constraints;
        }
        default: raise("findConstraints: unexpected exception!");
    }
}

void pardescribeShort(PARSER *parser, void *field, char *description) {
    if (field == NULL) {
        if (parser->shortDescription != NULL) {
            free(parser->shortDescription);
        }
        parser->shortDescription = strclone(description); 
        return;
    }
    FieldInfo *info = findFieldInfo(parser, field);
    if (info->shortDescription != NULL) {
        free(info->shortDescription);
    }
    info->shortDescription = strclone(description);
}

void pardescribeLong(PARSER *parser, void *field, char *description) {
    if (field == NULL) {
        if (parser->longDescription != NULL) {
            free(parser->longDescription);
        }
        parser->longDescription = strclone(description); 
        return;
    }
    FieldInfo *info = findFieldInfo(parser, field);
    if (info->longDescription != NULL) {
        free(info->longDescription);
    }
    info->longDescription = strclone(description);
}

void parsmaller(PARSER *parser, void *field, double than) {
    Constraints *constraints = findConstraints(parser, field);
    if (constraints == NULL) {
        raise(ERROR_FLAG_CONSTRAINT(parsmaller));
    }
    if (constraints->smallerEquals != NULL) {
        free(constraints->smallerEquals);
        constraints->smallerEquals = NULL;
    }
    if (constraints->smaller == NULL) {
        constraints->smaller = malloc(sizeof(double));
    }
    *constraints->smaller = than;
}

void parsmallerEquals(PARSER *parser, void *field, double than) {
    Constraints *constraints = findConstraints(parser, field);
    if (constraints == NULL) {
        raise(ERROR_FLAG_CONSTRAINT(parsmallerEquals));
    }
    if (constraints->smaller != NULL) {
        free(constraints->smaller);
        constraints->smaller = NULL;
    }
    if (constraints->smallerEquals == NULL) {
        constraints->smallerEquals = malloc(sizeof(double));
    }
    *constraints->smallerEquals = than;
}

void pargreater(PARSER *parser, void *field, double than) {
    Constraints *constraints = findConstraints(parser, field);
    if (constraints == NULL) {
        raise(ERROR_FLAG_CONSTRAINT(pargreater));
    }
    if (constraints->greaterEquals != NULL) {
        free(constraints->greaterEquals);
        constraints->greaterEquals = NULL;
    }
    if (constraints->greater == NULL) {
        constraints->greater = malloc(sizeof(double));
    }
    *constraints->greater = than;
}

void pargreaterEquals(PARSER *parser, void *field, double than) {
    Constraints *constraints = findConstraints(parser, field);
    if (constraints == NULL) {
        raise(ERROR_FLAG_CONSTRAINT(pargreaterEquals));
    }
    if (constraints->greater != NULL) {
        free(constraints->greater);
        constraints->greater = NULL;
    }
    if (constraints->greaterEquals == NULL) {
        constraints->greaterEquals = malloc(sizeof(double));
    }
    *constraints->greaterEquals = than;
}

static void parseParameter(char *input, Parameter *parameter) {
    char *endptr = "";
    switch(parameter->dataType) {
            case tint: {
                int parsedValue = strtol(input, &endptr, 10);
                if (endptr[0] != '\0') {
                    raise(ERROR_NOT_AN_INT(input, parameter->info.name));
                }
                *((int *) parameter->identifier) = parsedValue;
            }
            break;
            case tdouble: {
                double parsedValue = strtod(input, &endptr);
                if (endptr[0] != '\0') {
                    raise(ERROR_NOT_A_DOUBLE(input, parameter->info.name));
                }
                *((double*) parameter->identifier) = parsedValue;
            }
            break;
            case tstring: {
                *((char **) parameter->identifier) = strclone(input);
            }
        }
}

static void validateParameter(Parameter *parameter) {
    double *greater = parameter->constraints.greater;
    double *greaterEquals = parameter->constraints.greaterEquals;
    double *smaller = parameter->constraints.smaller;
    double *smallerEquals = parameter->constraints.smallerEquals;
    if (parameter->dataType == tstring && (greater != NULL || greaterEquals != NULL)) {
        size_t strLength = strlen(*(char **) parameter->identifier);
        size_t minLength = getMinLength(greater != NULL ? *greater : *greaterEquals, greaterEquals != NULL);
        if (strLength < minLength) {
            raise(ERROR_STRING_TO_SHORT(*((char **)parameter->identifier), parameter->info.name, minLength));
        }
        return;
    }
    if (parameter->dataType == tstring && (smaller != NULL || smallerEquals != NULL)) {
        size_t strLength = strlen(*(char **) parameter->identifier);
        size_t maxLength = getMaxLength(smaller != NULL ? *smaller : *smallerEquals, smallerEquals != NULL);
        if (strLength > maxLength) {
            raise(ERROR_STRING_TO_LONG(*((char **)parameter->identifier), parameter->info.name, maxLength));
        }
        return;
    }
    double value = 0;
    if (parameter->dataType == tint) {
        value = *((int *) parameter->identifier);
    }
    else if (parameter->dataType == tdouble) {
        value = *((double *) parameter->identifier);
    }
    if (greater != NULL && !(value > *greater)) {
        raise(ERROR_NOT_GREATER(value, parameter->info.name, *greater));
    }
    if (smaller != NULL && !(value < *smaller)) {
        raise(ERROR_NOT_SMALLER(value, parameter->info.name, *smaller));
    }
    if (greaterEquals != NULL && !(value >= *greaterEquals)) {
        raise(ERROR_NOT_GREATEREQUALS(value, parameter->info.name, *greaterEquals));
    }
    if (smallerEquals != NULL && !(value <= *smallerEquals)) {
        raise(ERROR_NOT_SMALLEREQUALS(value, parameter->info.name, *smallerEquals));
    }
}

static Flag* findFlag(char *name, list *flags) {
    for (int i = 0; i < flags->length; i++) {
        Flag *flag = listGet(flags, i);
        if (chain("--").strAdd(flag->info.name).equals(name)) {
            return flag;
        }
    }
    return NULL;
}

static Parameter* findOptional(char *name, list *optParameters) {
    for (int i = 0; i < optParameters->length; i++) {
        Parameter *parameter = listGet(optParameters, i);
        if (chain("--").strAdd(parameter->info.name).equals(name)) {
            return parameter;
        }
    }
    return NULL;
}

void parse(PARSER* parser, char **argv) {
    for (int i = 0; i < parser->positionalParameters.length; i++) {
        Parameter *posParameter = listGet(&parser->positionalParameters, i);
        if (argv[i + 1] == NULL) {
            raise(ERROR_PARAM_MISSING(posParameter->info.name));
        }
        parseParameter(argv[i + 1], posParameter);
        validateParameter(posParameter);
    }

    // set all flags to false
    for (int i = 0; i < parser->flags.length; i++) {
        Flag *flag = listGet(&parser->flags, i);
        *flag->identifier = 0;
    }

    // set all deafault values
    for (int i = 0; i < parser->optionalParameters.length; i++) {
        Parameter *optParameter = listGet(&parser->optionalParameters, i);
        switch (optParameter->dataType) {
            case tint: *((int *) optParameter->identifier) = *((int *) optParameter->value);
            break;
            case tdouble: *((double *) optParameter->identifier) = *((double *) optParameter->value);
            break;
            case tstring: *((char **) optParameter->identifier) = *((char **) optParameter->value);
        }
    }

    // extract optional parameters and flags
    // note: passing a flag or optional multiple times will work
    // in case of optionals the value of the last one will win
    int index = 1 + parser->positionalParameters.length;
    while (argv[index] != NULL) {
        if (!startsWith(argv[index], "--")) {
            raise(ERROR_UNRECOGNIZED_INPUT(argv[index]));
        }
        Parameter *optParameter = findOptional(argv[index], &parser->optionalParameters);
        if (optParameter != NULL) {
            if (argv[index + 1] == NULL) {
                printf("no value was given for opt param: %s\n", optParameter->info.name);
                exit(1);
            }
            parseParameter(argv[index + 1], optParameter);
            validateParameter(optParameter);
            index += 2;
            continue;
        }
        Flag *flag = findFlag(argv[index], &parser->flags);
        if (flag == NULL) {
            raise(ERROR_UNRECOGNIZED_INPUT(argv[index]));
        }
        *flag->identifier = 1;
        index += 1;
    }
    parser->hasParsed = true;
}

static Constraints createConstraints() {
    Constraints constraints = {
        .greater = NULL,
        .greaterEquals = NULL,
        .smaller = NULL,
        .smallerEquals = NULL
    };
    return constraints;
}

static FieldInfo createFieldInfo(char *name) {
    FieldInfo info = {
        .name = name,
        .shortDescription = NULL, 
        .longDescription = NULL
    };
    return info;
}

static Parameter createParameter(char *name, DataType dataType, void *identifier, void *value) {
    Parameter parameter = {
        .constraints = createConstraints(),
        .dataType = dataType,
        .info = createFieldInfo(name),
        .identifier = identifier,
        .value = value
    };
    return parameter;
}

int* paraddPosInt(PARSER *parser, char *name) {
    int *identifier = malloc(sizeof(int));
    *identifier = parser->positionalParameters.length*3 + 1;
    Parameter parameter = createParameter(strclone(name), tint, identifier, NULL);
    listAdd(&parser->positionalParameters, &parameter);
    return identifier;
}

int* paraddOptInt(PARSER *parser, char *name, int value) {
    int *identifier = malloc(sizeof(int));
    *identifier = parser->optionalParameters.length*3 + 2;
    int *defaultValue = malloc(sizeof(int));
    *defaultValue = value;
    Parameter parameter = createParameter(strclone(name), tint, identifier, defaultValue);
    listAdd(&parser->optionalParameters, &parameter);
    return identifier;
}

double* paraddPosDouble(PARSER *parser, char *name) {
    double *identifier = malloc(sizeof(double));
    *((unsigned long long *) identifier) = parser->positionalParameters.length*3 + 1;
    Parameter parameter = createParameter(strclone(name), tdouble, identifier, NULL);
    listAdd(&parser->positionalParameters, &parameter);
    return identifier;
}
        
double* paraddOptDouble(PARSER *parser, char *name, double value) {
    double *identifier = malloc(sizeof(double));
    *((unsigned long long *) identifier) = parser->optionalParameters.length*3 + 2;
    double *defaultValue = malloc(sizeof(double));
    *defaultValue = value;
    Parameter parameter = createParameter(strclone(name), tdouble, identifier, defaultValue);
    listAdd(&parser->optionalParameters, &parameter);
    return identifier;
}

char** paraddPosString(PARSER *parser, char *name) {
    char **identifier = malloc(sizeof(char*));
    *((unsigned long long *) identifier) = parser->positionalParameters.length*3 + 1;
    Parameter parameter = createParameter(strclone(name), tstring, identifier, NULL);
    listAdd(&parser->positionalParameters, &parameter);
    return identifier;
}

char** paraddOptString(PARSER *parser, char *name, char *value) {
    char **identifier = malloc(sizeof(char*));
    *((unsigned long long *) identifier) = parser->optionalParameters.length*3 + 2;
    char **defaultValue = malloc(sizeof(char*));
    *defaultValue = strclone(value);
    Parameter parameter = createParameter(strclone(name), tstring, identifier, defaultValue);
    listAdd(&parser->optionalParameters, &parameter);
    return identifier;
}

bool* paraddFlag(PARSER *parser, char *name) {
    Flag flag = {
        .info = createFieldInfo(strclone(name)),
        .identifier = malloc(sizeof(int)) 
    };
    *flag.identifier = parser->flags.length * 3;
    listAdd(&parser->flags, &flag);
    return (void *) flag.identifier;
}