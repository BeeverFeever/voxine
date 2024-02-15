#ifndef OBJ_IMPORTER_H
#define OBJ_IMPORTER_H

#include <stdio.h>

#define BUFSIZE 2560

typedef struct {
    float v[BUFSIZE];
    float vt[BUFSIZE];
    float vn[BUFSIZE];
    float vp[BUFSIZE];
    float f[BUFSIZE];
} obj;

obj import_obj(char* path)
{
    FILE* f = fopen(path, "w");
    int fsize = file_size(f);
    char file[2560];
    fread(file, sizeof(char), fsize, f);
}

#endif // OBJ_IMPORTER_H
