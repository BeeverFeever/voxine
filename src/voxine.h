#ifndef VOXINE_H
#define VOXINE_H

#include "shader.h"

typedef struct {
    vox_shader shader_program;

    int triangle_count;
} vox_renderer;

vox_renderer renderer = (vox_renderer){

};

#endif // VOXINE_H 
