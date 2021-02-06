#ifndef PARSINGEXERCISE_JSONPARSER_H
#define PARSINGEXERCISE_JSONPARSER_H

// A simple JSON parser.

#define MAX_JSON_LENGTH 256
#define MAX_ARRAY_LENGTH 256
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
    const char *start;
    const char *next;
    const char *end;
} Parser;

typedef struct Array {
    int length;
    Elem *values;
} Array;

Json *parseJson(const char *, int);

void optStatements(Parser *, Json *);
void statements(Parser *, Json *);
void statement(Parser *, Json *);

void stripWhitespace(Parser *);
void match(Parser *, char);
void stripMatch(Parser *, char);
void appendJson(Json *, char *, Elem);

Elem element(Parser *);
Json *obj(Parser *);
Array *array(Parser *);
void optElements(Parser *, Array *);
void elements(Parser *, Array *);
char *STR_TOKEN(Parser *);
int INT_TOKEN(Parser *);
int BOOL_TOKEN(Parser *);

#endif //PARSINGEXERCISE_JSONPARSER_H
