#ifndef PARSINGEXERCISE_JSONPARSER_H
#define PARSINGEXERCISE_JSONPARSER_H

// A simple JSON parser.

#define MAX_JSON_LENGTH 256
#define MAX_KEY_LENGTH 64

#define ERROR 0
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
    int length;
    char **keys;
    Elem *values;
} Json;

typedef struct Parser {
    int error;
    const char *next;
    const char *end;
} Parser;

Json *parseJson(const char *, int);

Json *obj(Parser *);
void optStatements(Parser *, Json *);
void statements(Parser *, Json *);
void statement(Parser *, Json *);

void match(Parser *, char);
void appendJson(Json *, char *, Elem);

Elem element(Parser *);
char *STR_TOKEN(Parser *);
int INT_TOKEN(Parser *);

#endif //PARSINGEXERCISE_JSONPARSER_H
