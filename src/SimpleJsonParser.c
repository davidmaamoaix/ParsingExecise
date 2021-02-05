#include "SimpleJsonParser.h"

#include <stdlib.h>
#include <stdio.h>

Json *parseJson(const char *input, int length) {
    Parser *parser = malloc(sizeof(Parser));
    parser->error = 0;
    parser->next = input;
    parser->end = input + length;

    Json *output = obj(parser);

    if (parser->error != 0) {
        printf("Whelp %d", parser->error); // TODO: meaningful msgs
    }

    return output;
}

Json *obj(Parser *parser) {
    Json *json = malloc(sizeof(Json));
    json->keys = malloc(sizeof(char *) * MAX_LENGTH);
    json->values =  malloc(sizeof(Elem) * MAX_LENGTH);

    match(parser, '{');
    match(parser, '}');

    if (parser->error) return NULL;

    return json;
}

void match(Parser *parser, const char token) {
    if (parser->error) return;
    if (parser->next == parser->end || *(parser->next++) != token) {
        printf("wat");
        parser->error = 1;
    }
}