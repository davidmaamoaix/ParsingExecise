#include "RecursiveDescent.h"

#include <stdlib.h>

bool isValid(Token *tokens, int length) {
    RDParser *parser = makeRD(tokens, 7);
    return expression(parser) && parser->next == parser->end;
}

RDParser *makeRD(char **tokens, int length) {
    RDParser *parser = malloc(sizeof(RDParser));
    parser->next = tokens;
    parser->end = tokens + length;

    return parser;
}

bool isToken(TokenChecker checker, RDParser *parser) {
    return parser->next != parser->end && checker(parser->next++);
}

bool termNumber(RDParser *parser) {
    return isToken(NUMBER, parser);
}

bool termTimes(RDParser *parser) {
    return isToken(NUMBER, parser) && isToken(TIMES, parser) && term(parser);
}

bool termParan(RDParser *parser) {
    return isToken(OPEN, parser) && expression(parser) && isToken(CLOSE, parser);
}

bool term(RDParser *parser) {
    Token *save = parser->next;

    return
        (parser->next = save, termParan(parser)) ||
        (parser->next = save, termTimes(parser)) ||
        (parser->next = save, termNumber(parser));
}

bool expressionTerm(RDParser *parser) {
    return term(parser);
}

bool expressionPlus(RDParser *parser) {
    return term(parser) && isToken(PLUS, parser) && expression(parser);
}

bool expression(RDParser *parser) {
    Token *save = parser->next;

    return
        (parser->next = save, expressionPlus(parser)) ||
        (parser->next = save, expressionTerm(parser));
}