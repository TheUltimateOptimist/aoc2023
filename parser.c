#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "string.c"

//TODO: when adding parameters the names need to be validated
//also see if name is available
//TODO: add good validation messages
//TODO: int instead of long long int
//TODO: eliminate DATATYPE pointers use double* etc instead with tricks
//TODO: good messages when wrong input
//TODO: --help
//TODO: all names descriptions etc should be cloned to avoid dangling pointers

#define ERROR_ADDED_SHORT_DESCRIPTION_TWICE \
    "pardescribeShort failed with the following Exception:\n"\
    "Can not add short description twice.\n"\
    "You tried to add a short description even though it was already added before."

#define ERROR_ADDED_LONG_DESCRIPTION_TWICE \
    "pardescribeLong failed with the following Exception:\n"\
    "Can not add long description twice.\n"\
    "You tried to add a long description even though it was already added before."

#define ERROR_ADDED_SMALLER_TWICE \
    "parsmaller failed with the following Exception:\n"\
    "Can not "

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

typedef union Value {
    int *intValue;
    double *doubleValue;
    char *stringValue;
} Value;

typedef struct Parameter {
    FieldInfo info;
    Constraints constraints;
    Value value;
    DataType dataType;
} Parameter;

typedef struct Flag {
    FieldInfo info;
    bool value;
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

void pardescribeShort(PARSER *parser, void *field, char *description) {
    if (field == NULL) {
        if (parser->shortDescription != NULL) {
            raise(ERROR_ADDED_SHORT_DESCRIPTION_TWICE);
        }
        parser->shortDescription = strclone(description); 
        return;
    }
    FieldInfo *info = findFieldInfo(parser, field);
    if (info->shortDescription != NULL) {
        raise(ERROR_ADDED_SHORT_DESCRIPTION_TWICE);
    }
    info->shortDescription = strclone(description);
}

void pardescribeLong(PARSER *parser, void *field, char *description) {
    if (field == NULL) {
        if (parser->longDescription != NULL) {
            raise(ERROR_ADDED_LONG_DESCRIPTION_TWICE);
        }
        parser->longDescription = strclone(description); 
        return;
    }
    FieldInfo *info = findFieldInfo(parser, field);
    if (info->longDescription != NULL) {
        raise(ERROR_ADDED_LONG_DESCRIPTION_TWICE);
    }
    info->longDescription = strclone(description);
}

void parsmaller(PARSER *parser, void *field, double than) {

}



void parshortDescription(PARSER *parser, char *description) {
    parser->shortDescription = description;
}

void parlongDescription(PARSER *parser, char *description) {
    parser->longDescription = description;
} 

static void parseParameter(char *input, Parameter *parameter) {
    char *endptr = "";
    Value value;
    switch(parameter->dataType) {
            case tint: {
                long long int *parsedValue = malloc(sizeof(long long int));
                *parsedValue = strtoll(input, &endptr, 10);
                value.intValue = parsedValue;
            }
            break;
            case tdouble: {
                double *parsedValue = malloc(sizeof(double));
                *parsedValue = strtod(input, &endptr);
                value.doubleValue = parsedValue;
            }
            break;
            case tstring: {
                value.stringValue = input;
            }
        }
    if (endptr[0] != '\0') {
        printf("parsing the input failed\n");
        exit(1);
    } 
    parameter->value = value;
}

static void validateParameter(Parameter *parameter) {
    fflush(stdout);
    double *greater = parameter->constraints.greater;
    double *greaterEquals = parameter->constraints.greaterEquals;
    double *smaller = parameter->constraints.smaller;
    double *smallerEquals = parameter->constraints.smallerEquals;
    if (parameter->dataType == tstring) {
        size_t strLength = strlen(parameter->value.stringValue);
        if (greaterEquals != NULL && strLength < *greaterEquals) {
            printf("string to short\n");
            exit(1);
        }
        if (smallerEquals != NULL && strLength > *smallerEquals) {
            printf("string to long\n");
            exit(1);
        }
        return;
    }
    double value = 0;
    if (parameter->dataType == tint) {
        value = *(parameter->value.intValue);
    }
    if (parameter->dataType == tdouble) {
        value = *(parameter->value.doubleValue);
    }
    if (greater != NULL && !(value > *greater)) {
        printf("value not greater than greater\n");
        exit(1);
    }
    if (smaller != NULL && !(value < *smaller)) {
        printf("value not smaller than smaller\n");
        exit(1);
    }
    if (greaterEquals != NULL && !(value >= *greaterEquals)) {
        printf("value not greater equals greater equals\n");
        exit(1);
    }
    if (smallerEquals != NULL && !(value <= *smallerEquals)) {
        printf("value not smaller equals smaller equals\n");
        exit(1);
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
    // printf("%s\n", parser->shortDescription);
    // printf("%s\n", parser->longDescription);
    // printf("%lu\n", parser->positionalParameters.length);
    // printf("%d\n", parser->hasParsed);
    // fflush(stdout);
    // for (int i = 0; i < parser->flags.length; i++) {
    //     Flag *flag = listGet(&parser->flags, i);
    //     printf("flag %d: %s %d\n", i, flag->info.name, flag->value);
    // }
    // printf("sdf\n");
    // fflush(stdout);
    // for (int i = 0; i < parser->positionalParameters.length; i++) {
    //     printf("%d\n", i);
    //     fflush(stdout);
    //     Parameter *param = listGet(&parser->positionalParameters, i);
    //     printf("%d\n", i);
    //     printf("%d\n", param->dataType);
    //     fflush(stdout);
    //     printf("pos %d: %s", i, param->info.name);
    // }
    // printf("hallo\n");
    // fflush(stdout);
    //extract positional parameters
    for (int i = 0; i < parser->positionalParameters.length; i++) {
        if (argv[i + 1] == NULL) {
            printf("a pos param missing\n");
            exit(1);
        }
        Parameter *posParameter = listGet(&parser->positionalParameters, i);
        parseParameter(argv[i + 1], posParameter);
        validateParameter(posParameter);

    }

    // extract optional parameters and flags
    // note: passing a flag or optional multiple times will work
    // in case of optionals the value of the last one will win
    int index = 1 + parser->positionalParameters.length;
    while (argv[index] != NULL) {
        if (!startsWith(argv[index], "--")) {
            printf("unrecognized input no dashes: %s\n", argv[index]);
            exit(1);
        }
        Parameter *optParameter = findOptional(argv[index], &parser->optionalParameters);
        printf("%p\n", optParameter);
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
            printf("no match found for %s\n", argv[index]);
            exit(1);
        }
        flag->value = true;
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

static Info createInfo(char *name) {
    Info info = {
        .name = name,
        .shortDescription = NULL, 
        .longDescription = NULL
    };
    return info;
}

static Parameter createParameter(char *name, DataType dataType, void *dValue) {
    Value value;
    switch (dataType) {
        case tint: value.intValue = dValue;
        break;
        case tdouble: value.doubleValue = dValue;
        break;
        case tstring: value.stringValue = dValue;
    }
    Parameter parameter = {
        .constraints = createConstraints(),
        .dataType = dataType,
        .info = createInfo(name),
        .value = value
    };
    return parameter;
}

static ParameterFinder createParameterFinder(PARSER *parser, bool isPositional, int index) {
    ParameterFinder parameterFinder;
    parameterFinder.parser = parser;
    parameterFinder.isPositional = isPositional;
    parameterFinder.index = index;
    return parameterFinder;
}

INT* paraddPosInt(PARSER *parser, char *name) {
    Parameter parameter = createParameter(name, tint, NULL);
    listAdd(&parser->positionalParameters, &parameter);
    INT *result = malloc(sizeof(INT));
    result->parameterFinder = createParameterFinder(
        parser,
        true,
        parser->positionalParameters.length - 1
    );
    return result;
}

INT* paraddOptInt(PARSER *parser, char *name, long long int value) {
    long long int *valuePtr = malloc(sizeof(long long int));
    *valuePtr = value;
    Parameter parameter = createParameter(name, tint, valuePtr);
    listAdd(&parser->optionalParameters, &parameter);
    INT *result = malloc(sizeof(INT));
    result->parameterFinder = createParameterFinder(
        parser,
        false,
        parser->optionalParameters.length - 1
    );
    return result;
}

static Parameter* getParameter(ParameterFinder parameterFinder) {
    Parameter *parameter;
    if (parameterFinder.isPositional) {
        parameter = listGet(&parameterFinder.parser->positionalParameters, parameterFinder.index);
    }
    else {
        parameter = listGet(&parameterFinder.parser->optionalParameters, parameterFinder.index);
    }
    return parameter;
}

static void validateAccess(PARSER *parser) {
    if (!parser->hasParsed) {
        printf("getting the values before parsing is not allowed!\n");
        exit(1);
    }
}

long long int parintValue(INT *parameter) {
    Parameter *data = getParameter(parameter->parameterFinder); 
    validateAccess(parameter->parameterFinder.parser);
    return *data->value.intValue;
}

void parintShortDescription(INT *parameter, char *description) {
    Parameter *data = getParameter(parameter->parameterFinder); 
    data->info.shortDescription = description;
}

void parintLongDescription(INT *parameter, char *description) {
    Parameter *data = getParameter(parameter->parameterFinder);
    data->info.longDescription = description;
}

void parintGreater(INT *parameter, long long int than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.greater != NULL || data->constraints.greaterEquals != NULL) {
        printf("assigning int greater or greaterEquals twice not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.greater = value;
}


void parintSmaller(INT *parameter, long long int than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.smaller != NULL || data->constraints.smallerEquals != NULL) {
        printf("assigning int smaller or smaller equals twice is not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.smaller = value;
}

void parintGreaterEquals(INT *parameter, long long int than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.greater != NULL || data->constraints.greaterEquals != NULL) {
        printf("assigning int greater or greaterEquals twice not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.greaterEquals = value;
}

void parintSmallerEquals(INT *parameter, long long int than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.smaller != NULL || data->constraints.smallerEquals != NULL) {
        printf("assigning int smaller or smaller equals twice is not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.smallerEquals = value;
}

DOUBLE* paraddPosDouble(PARSER *parser, char *name) {
    Parameter parameter = createParameter(name, tdouble, NULL);
    listAdd(&parser->positionalParameters, &parameter);
    DOUBLE *result = malloc(sizeof(DOUBLE));
    result->parameterFinder = createParameterFinder(
        parser,
        true,
        parser->positionalParameters.length - 1
    );
    return result;
}

DOUBLE* paraddOptDouble(PARSER *parser, char *name, double value) {
    double *valuePtr = malloc(sizeof(double));
    *valuePtr = value;
    Parameter parameter = createParameter(name, tdouble, valuePtr);
    listAdd(&parser->optionalParameters, &parameter);
    DOUBLE *result = malloc(sizeof(DOUBLE));
    result->parameterFinder = createParameterFinder(
        parser,
        false,
        parser->optionalParameters.length - 1
    );
    return result;
}


double pardoubleValue(DOUBLE *parameter) {
    Parameter *data = getParameter(parameter->parameterFinder); 
    validateAccess(parameter->parameterFinder.parser);
    return *data->value.doubleValue;
}

void pardoubleShortDescription(DOUBLE *parameter, char *description) {
    Parameter *data = getParameter(parameter->parameterFinder); 
    data->info.shortDescription = description;
}

void pardoubleLongDescription(DOUBLE *parameter, char *description) {
    Parameter *data = getParameter(parameter->parameterFinder);
    data->info.longDescription = description;
}

void pardoubleGreater(DOUBLE *parameter, double than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.greater != NULL || data->constraints.greaterEquals != NULL) {
        printf("assigning int greater or greaterEquals twice not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.greater = value;
}

void pardoubleSmaller(DOUBLE *parameter, double than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.smaller != NULL || data->constraints.smallerEquals != NULL) {
        printf("assigning int smaller or smaller equals twice is not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.smaller = value;
}

void pardoubleGreaterEquals(DOUBLE *parameter, double than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.greater != NULL || data->constraints.greaterEquals != NULL) {
        printf("assigning int greater or greaterEquals twice not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.greaterEquals = value;
}

void pardoubleSmallerEquals(DOUBLE *parameter, double than) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.smaller != NULL || data->constraints.smallerEquals != NULL) {
        printf("assigning int smaller or smaller equals twice is not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = than;
    data->constraints.smallerEquals = value;
}

STRING* paraddPosString(PARSER *parser, char *name) {
    Parameter parameter = createParameter(name, tstring, NULL);
    listAdd(&parser->positionalParameters, &parameter);
    STRING *result = malloc(sizeof(STRING));
    result->parameterFinder = createParameterFinder(
        parser,
        true,
        parser->positionalParameters.length - 1
    );
    return result;
}

STRING* paraddOptString(PARSER *parser, char *name, char *value) {
    Parameter parameter = createParameter(name, tstring, value);
    listAdd(&parser->optionalParameters, &parameter);
    STRING *result = malloc(sizeof(STRING));
    result->parameterFinder = createParameterFinder(
        parser,
        false,
        parser->optionalParameters.length - 1
    );
    return result;
}


char *parstringValue(STRING *parameter) {
    Parameter *data = getParameter(parameter->parameterFinder); 
    validateAccess(parameter->parameterFinder.parser);
    return data->value.stringValue;
}

void parstringShortDescription(STRING *parameter, char *description) {
    Parameter *data = getParameter(parameter->parameterFinder); 
    data->info.shortDescription = description;
}

void parstringLongDescription(STRING *parameter, char *description) {
    Parameter *data = getParameter(parameter->parameterFinder);
    data->info.longDescription = description;
}

void parstringMinLength(STRING *parameter, size_t length) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.greaterEquals != NULL) {
        printf("assigning min length twice is not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = length;
    data->constraints.greaterEquals = value;
}

void parstringMaxLength(STRING *parameter, size_t length) {
    Parameter *data = getParameter(parameter->parameterFinder);
    if (data->constraints.smallerEquals != NULL) {
        printf("assigning max length twice is not allowed\n");
        exit(1);
    }
    double *value = malloc(sizeof(double));
    *value = length;
    data->constraints.smallerEquals = value;
}

FLAG* paraddFlag(PARSER *parser, char *name) {
    Flag flag = {
        .info = createInfo(name),
        .value = false
    };
    listAdd(&parser->flags, &flag);
    FLAG *result = malloc(sizeof(FLAG));
    result->index = parser->flags.length - 1;
    result->parser = parser;
    return result;
}

bool parflagValue(FLAG *flag) {
    validateAccess(flag->parser);
    Flag *data = listGet(&flag->parser->flags, flag->index);
    return data->value;
}

void parflagShortDescription(FLAG *flag, char *description) {
    Flag *data = listGet(&flag->parser->flags, flag->index);
    data->info.shortDescription = description;
}

void parflagLongDescription(FLAG *flag, char *description) {
    Flag *data = listGet(&flag->parser->flags, flag->index);
    data->info.longDescription = description;
}