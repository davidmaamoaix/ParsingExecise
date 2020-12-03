#include "Token.h"

bool NUMBER(Token *token) {
    for (int i = 0; i < strlen(*token); ++i) {
        if (!isdigit((*token)[i])) {
            return false;
        }
    }

    return true;
}

bool TIMES(Token *token) {
    return strcmp(*token, "*") == 0;
}

bool PLUS(Token *token) {
    return strcmp(*token, "+") == 0;
}

bool OPEN(Token *token) {
    return strcmp(*token, "(") == 0;
}

bool CLOSE(Token *token) {
    return strcmp(*token, ")") == 0;
}