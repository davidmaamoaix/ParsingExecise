#include "SimpleJsonParser.h"

#include <stdlib.h>
#include <stdio.h>

#define WHITE(x) x == ' ' || x == '\n' || x == '\t'

Json *parseJson(const char *input, int length) {
    Parser *parser = malloc(sizeof(Parser));
    parser->error = 0;
    parser->next = input;
    parser->end = input + length;

    Json *output = obj(parser);

    if (!parser->error && parser->next != parser->end) {
        parser->error = 1;
        printf("JSON ended %ld characters early\n", parser->end - parser->next);
    }

    if (parser->error) {
        printf("Syntax Error: %d", parser->error); // TODO: meaningful msgs
    }

    return output;
}

/*
 * optStatements -> EPSILON | statement | statement, statements
 *
 * FIRST(statement) = {'"'}
 */
void optStatements(Parser *parser, Json *json) {
    stripWhitespace(parser);
    if (*parser->next == '"') {
        statements(parser, json);
    }
}

void statements(Parser *parser, Json *json) {

    // TODO: figure out a proper place for error checking and aborting early
    if (parser->error) return;

    statement(parser, json);

    stripWhitespace(parser);
    if (*parser->next == ',') {
        match(parser, ',');
        statements(parser, json);
    }
}

void statement(Parser *parser, Json *json) {
     char *key = STR_TOKEN(parser);
     stripMatch(parser, ':');
     Elem value = element(parser);

     appendJson(json, key, value);
}

void stripWhitespace(Parser *parser) {
    while (WHITE(*parser->next))  {
        ++parser->next;
    }
}

void match(Parser *parser, const char token) {
    if (parser->error) return;

    if (parser->next == parser->end) {
        parser->error = 1;
        printf("EOF reached!\n");
    } else if (*(parser->next++) != token) {
        parser->error = 1;
        printf("Expected: '%c'; instead got '%c'", token, *(parser->next - 1));
        printf("(Position %ld)\n", parser->end - parser->next);
    }
}

void stripMatch(Parser *parser, const char token) {
    stripWhitespace(parser);
    match(parser, token);
}

void appendJson(Json *json, char *key, Elem elem) {
    json->keys[json->length] = key;
    json->values[json->length] = elem;
    ++json->length;
}

Elem element(Parser *parser) {
    Elem elem = {ERROR, NULL};
    stripWhitespace(parser);
    char next = *parser->next;

    if (next == '"') {
        elem.type = STR;
        elem.data = STR_TOKEN(parser);
    } else if (next >= 48 && next <= 57) {
        elem.type = INT;
        elem.data = malloc(sizeof(int));
        *((int *) elem.data) = INT_TOKEN(parser);
    } else if (next == 't' || next == 'f') {
        elem.type = BOOL;
        elem.data = malloc(sizeof(int));
        *((int *) elem.data) = BOOL_TOKEN(parser);
    } else if (next == '{') {
        elem.type = OBJ;
        elem.data = obj(parser);
    } else if (next == '[') {
        elem.type = ARRAY;
        elem.data = array(parser);
    }

    return elem;
}

Json *obj(Parser *parser) {
    Json *json = malloc(sizeof(Json));
    json->length = 0;
    json->keys = malloc(sizeof(char *) * MAX_JSON_LENGTH);
    json->values =  malloc(sizeof(Elem) * MAX_JSON_LENGTH);

    stripMatch(parser, '{');
    optStatements(parser, json);
    stripMatch(parser, '}');

    if (parser->error) {
        free(json->keys);
        free(json->values);
        free(json);

        return NULL;
    }

    return json;
}

Array *array(Parser *parser) {
    Array *array = malloc(sizeof(Array));
    array->length = 0;
    array->values = malloc(sizeof (Elem *) * MAX_ARRAY_LENGTH);

    stripMatch(parser, '[');
    optElements(parser, array);
    stripMatch(parser, ']');

    if (parser->error) {
        free(array->values);
        free(array);

        return NULL;
    }

    return array;
}

void optElements(Parser *parser, Array *array) {
    stripWhitespace(parser);
    char next = *parser->next;

    // FIRST(elem) = {FIRST(STR), FIRST(INT), FIRST(OBJ), FIRST(BOOL), FIRST(ARRAY)}
    int nonInt = next == '"' || next == '{' || next == 't' || next == 'f' || next == '[';
    if (nonInt || (next >= 48 && next <= 57)) {
        elements(parser, array);
    }
}

void elements(Parser *parser, Array *array) {

    array->values[array->length++] = element(parser);

    stripWhitespace(parser);
    if (*parser->next == ',') {
        match(parser, ',');
        elements(parser, array);
    }
}

/*
 * Stripping is done once in the element grammar already;
 * however, the token grammar is also used elsewhere.
 *
 * Therefore we strip despite the redundant element stripping.
 */
char *STR_TOKEN(Parser *parser) {
    stripMatch(parser, '"');

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
    stripWhitespace(parser);

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

int BOOL_TOKEN(Parser *parser) {
    stripWhitespace(parser);

    int value = 0;

    if (*parser->next == 't') {
        match(parser, 't');
        match(parser, 'r');
        match(parser, 'u');
        match(parser, 'e');
        value = 1;
    } else {
        match(parser, 'f');
        match(parser, 'a');
        match(parser, 'l');
        match(parser, 's');
        match(parser, 'e');
    } // no other case, as checked in element

    return value;
}