#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *path) {
    char *buf = 0;
    FILE *f = fopen(path, "rb");
    unsigned long size;

    if (!f) {
        printf("Reading %s failed\n", path);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size = (unsigned long) ftell(f);

    fseek(f, 0, SEEK_SET);
    buf = malloc(size * sizeof(char));
    fread(buf, sizeof(char), size, f);
    fclose(f);

    return buf;
}