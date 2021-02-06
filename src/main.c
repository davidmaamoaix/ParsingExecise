#include <stdio.h>
#include <stdlib.h>

#include "SimpleJsonParser.h"

int main() {
    const char *foo = "{\"a\",\"a\"}";

    Json *json = parseJson(foo, 9);

    return 0;
}