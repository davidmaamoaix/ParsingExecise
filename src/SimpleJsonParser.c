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
        printf("Syntax Error: %d", parser->error); // TODO: meaningful msgs
    }

    return output;
}

Json *obj(Parser *parser) {
    Json *json = malloc(sizeof(Json));
    json->length = 0;
    json->keys = malloc(sizeof(char *) * MAX_JSON_LENGTH);
    json->values =  malloc(sizeof(Elem) * MAX_JSON_LENGTH);

    match(parser, '{');
    optStatements(parser, json);
    match(parser, '}');

    if (!parser->error && parser->next != parser->end) {
        parser->error = 1;
        printf("JSON ended %ld characters early\n", parser->end - parser->next);
    }

    if (parser->error) {
        free(json->keys);
        free(json->values);
        free(json);

        return NULL;
    }

    return json;
}

/*
 * optStatements -> EPSILON | statement | statement, statements
 *
 * FIRST(statement) = {'"'}
 */
void optStatements(Parser *parser, Json *json) {
    if (*parser->next == '"') {
        statements(parser, json);
    }
}

void statements(Parser *parser, Json *json) {

    // TODO: figure out a proper place for error checking and aborting early
    if (parser->error) return;

    statement(parser, json);

    if (*parser->next == ',') {
        match(parser, ',');
        statements(parser, json);
    }
}

void statement(Parser *parser, Json *json) {
     char *key = STR_TOKEN(parser);
     match(parser, ':');
     Elem value = element(parser);

     appendJson(json, key, value);
}

void match(Parser *parser, const char token) {
    if (parser->error) return;

    if (parser->next == parser->end) {
        parser->error = 1;
        printf("EOF reached!\n");
    } else if (*(parser->next++) != token) {
        parser->error = 1;
        printf("Expected: '%c'; instead got '%c'\n", token, *(parser->next - 1));
    }
}

void appendJson(Json *json, char *key, Elem elem) {
    json->keys[json->length] = key;
    json->values[json->length] = elem;
    ++json->length;
}

Elem element(Parser *parser) {
    Elem elem = {ERROR, NULL};
    char next = *parser->next;

    if (next == '"') {
        elem.type = STR;
        elem.data = STR_TOKEN(parser);
    } else if (next >= 48 && next <= 57) {
        elem.type = INT;
        elem.data = malloc(sizeof(int));
        *((int *) elem.data) = INT_TOKEN(parser);
    }

    return elem;
}

char *STR_TOKEN(Parser *parser) {
    match(parser, '"');

    char *key = malloc(sizeof(char) * MAX_KEY_LENGTH);
    int index = 0;

    while (*parser->next != '"' && parser->next != parser->end) {
        key[index++] = *(parser->next++);
    }

    if (parser->next == parser->end) {
        parser->error = 1;
        printf("EOF reached while parsing string element\n");
    }

    key[index] = '\0';

    match(parser, '"');

    return key;
}

/*
 * FOLLOW(elem) = {',', '}'}
 */
int INT_TOKEN(Parser *parser) {
    int value = 0;

    while (*parser->next != ',' && *parser->next != '}' && parser->next != parser->end) {
        value = value * 10 + *(parser->next++);
    }

    if (parser->next == parser->end) {
        parser->error = 1;
        printf("EOF reached while parsing integer element\n");
    }

    return value;
}