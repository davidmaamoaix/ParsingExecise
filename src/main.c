#include <stdio.h>

#include "RecursiveDescent.h"

int main() {
    Token tokens[] = {
        "5",
        "*",
        "(",
        "728",
        "+",
        "52",
        ")"
    };

    printf("Final: %d\n", isValid(tokens, 7));

    return 0;
}