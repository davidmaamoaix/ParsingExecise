#ifndef PARSINGEXERCISE_TOKEN_H
#define PARSINGEXERCISE_TOKEN_H

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef char * Token;
typedef bool(*TokenChecker)(Token *);

bool NUMBER(Token *);
bool TIMES(Token *);
bool PLUS(Token *);
bool OPEN(Token *);
bool CLOSE(Token *);

#endif //PARSINGEXERCISE_TOKEN_H
