/*
 * This is the most trivial parser in this repo;
 * it is not even general, and certainly does not
 * automatically eliminate recursions.
 *
 * This parser parses the following syntax:
 *
 * E -> T + E | T
 * T -> INT | INT * T | ( E )
 *
 * Note that this parser does not handle left recursion.
 */

#ifndef PARSINGEXERCISE_RECURSIVEDESCENT_H
#define PARSINGEXERCISE_RECURSIVEDESCENT_H

#include <ctype.h>
#include <string.h>

#include "Token.h"

typedef struct RDParser {
    Token *next;
    Token *end;
} RDParser;

bool isValid(Token *, int);

RDParser *makeRD(char **, int);
bool isToken(TokenChecker, RDParser *);

bool termNumber(RDParser *);
bool termTimes(RDParser *);
bool termParan(RDParser *);
bool term(RDParser *);

bool expressionTerm(RDParser *);
bool expressionPlus(RDParser *);
bool expression(RDParser *);

#endif //PARSINGEXERCISE_RECURSIVEDESCENT_H
