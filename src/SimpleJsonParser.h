#ifndef PARSINGEXERCISE_JSONPARSER_H
#define PARSINGEXERCISE_JSONPARSER_H

// A simple JSON parser.

#define MAX_LENGTH 256

#define INT 1
#define BOOL 2
#define STR 3
#define ARRAY 4
#define OBJ 5

typedef struct Elem {
    unsigned char type;
    void *data;
} Elem;

typedef struct Json {
    char **keys;
    Elem *values;
    int length;
} Json;

typedef struct Parser {
    const char *next;
    const char *end;
} Parser;

Json *parseJson(const char *, int);

Json *obj(const char *next);

#endif //PARSINGEXERCISE_JSONPARSER_H
