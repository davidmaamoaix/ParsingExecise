#include "SimpleJsonParser.h"

#include <stdlib.h>

Json *parseJson(const char *input, int length) {
    Parser *parser = malloc(sizeof(Parser));
    parser->next = input;
    parser->end = input + length;
}

Json *obj(const char *next) {
    /*Json *json = malloc(sizeof(Json));
    json->keys = malloc(sizeof(char *) * MAX_LENGTH);
    json->values =  malloc(sizeof(Elem) * MAX_LENGTH);*/
}

