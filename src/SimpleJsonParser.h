#ifndef PARSINGEXERCISE_JSONPARSER_H
#define PARSINGEXERCISE_JSONPARSER_H

// A simple JSON parser.

#define MAX_LENGTH 256

#define INT 1
#define BOOL 2
#define STR 3
#define ARRAY 4
#define OBJ 5

// difference of type between key and value is
// enforced programmatically
typedef struct Elem {
    unsigned char type;
    void *data;
} Elem;

typedef struct Json {
    Elem *keys;
    Elem *values;
    int length;
} Json;

Json *parseJson(const char *);

#endif //PARSINGEXERCISE_JSONPARSER_H
