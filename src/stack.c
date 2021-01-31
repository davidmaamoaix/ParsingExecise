#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

Stack *makeStack() {
  Stack *stack = malloc(sizeof(Stack));
  stack->tokens = malloc(sizeof(Token *) * MAX_STACK);
  stack->size = 0;

  return stack;
};

void push(Stack *stack, Token *token) {
    stack->tokens[stack->size++] = token;
}

Token *pop(Stack *stack) {
    if (stack->size == 0) {
        printf("[Error] Poping from empty stack");
    }

    return stack->tokens[stack->size--];
}