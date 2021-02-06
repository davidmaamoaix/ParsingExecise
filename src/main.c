#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SimpleJsonParser.h"

int main() {
    const char *foo = "{\"a\":\"a b\",\"a\":\"a b\",\"a\":\"a b\",\"a\":\"a b\",\"a\":\"a b\",\"a\":\"a b\"}";

    Json *json = parseJson(foo, (int) strlen(foo));

    return 0;
}