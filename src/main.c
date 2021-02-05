#include <stdio.h>

#include "SimpleJsonParser.h"

int main() {
    const char *foo = "{}";

    Json *json = parseJson(foo, 2);

    return 0;
}