#ifndef PARSINGEXERCISE_STACK_H
#define PARSINGEXERCISE_STACK_H

#include "Token.h"

#define MAX_STACK 1024

typedef struct Stack {
    Token **tokens;
    int size;
} Stack;

Stack *makeStack();
void push(Stack *, Token *);
Token *pop(Stack *);

#endif //PARSINGEXERCISE_STACK_H
