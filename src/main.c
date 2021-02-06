#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SimpleJsonParser.h"
#include "testing.h"

int main() {
    const char *foo = "{\"a\":32123123,\"a\":\"a b\",\"a\":true}";
    char *jsonStr = readFile("texts/json_sample.json");

    Json *json = parseJson(jsonStr, (int) strlen(jsonStr));

    return 0;
}