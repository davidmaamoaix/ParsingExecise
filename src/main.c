#include <stdio.h>
#include <stdlib.h>

#include "SimpleJsonParser.h"

int main() {
    const char *foo = "{a}";

    Json *json = parseJson(foo, 2);

    return 0;
}