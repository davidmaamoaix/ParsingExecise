#include "SimpleJsonParser.h"

#include <stdlib.h>

Json *parseJson(const char *input, int length) {
    Parser *parser = malloc(sizeof(Parser));
    parser->next = input;
    parser->end = input + length;
}

Json *obj(Parser *parser) {
    /*Json *json = malloc(sizeof(Json));
    json->keys = malloc(sizeof(char *) * MAX_LENGTH);
    json->values =  malloc(sizeof(Elem) * MAX_LENGTH);*/



    if (parser->error) return NULL;
}

void match(Parser *parser, const char token) {
    if (parser->error) return;
    if (*(parser->next++) != token) parser->error = 1;
}