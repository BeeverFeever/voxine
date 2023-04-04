#include "shader.h"

static FILE* open_file(const char* path, const char* mode) {
    FILE* in = fopen(path, mode);
    if (in == NULL) {
        fprintf(stderr, "ERROR: could not open %s\n%s", path, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return in;
}

char* read_file(const char* path) {
    char* buffer;
    FILE* file = open_file(path, "r");

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length + 1);

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';

    return buffer;
}
