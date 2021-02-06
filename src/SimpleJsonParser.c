#include "SimpleJsonParser.h"

#include <stdlib.h>
#include <stdio.h>

Json *parseJson(const char *input, int length) {
    Parser *parser = malloc(sizeof(Parser));
    parser->error = 0;
    parser->next = input;
    parser->end = input + length;

    Json *output = obj(parser);

    if (parser->error) {
        printf("Whelp %d", parser->error); // TODO: meaningful msgs
    }

    return output;
}

Json *obj(Parser *parser) {
    Json *json = malloc(sizeof(Json));
    json->keys = malloc(sizeof(char *) * MAX_LENGTH);
    json->values =  malloc(sizeof(Elem) * MAX_LENGTH);

    match(parser, '{');
    statements(parser, json);
    match(parser, '}');

    if (parser->error) {
        free(json->keys);
        free(json->values);
        free(json);

        return NULL;
    }

    return json;
}

void statements(Parser *parser, Json *json) {

}

void match(Parser *parser, const char token) {
    if (parser->error) return;
    if (parser->next == parser->end || *(parser->next++) != token) {
        parser->error = 1;
    }
}

void appendJson(Json *json, char *type, Elem *elem) {
    json->keys[json->length] = type;
    json->values[json->length] = elem;
    ++json->length;
}