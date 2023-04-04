#ifndef VOXINE_SHADER_H
#define VOXINE_SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <voxine/thirdparty/include/GLAD/glad.h>

typedef GLuint vox_shader;
typedef GLuint vox_program;

vox_shader  vox_load_shader(GLenum type, const char* path);
vox_program vox_shader_program(const char* vert_path, const char* frag_path);
void        vox_use_program(vox_program program);

#endif // VOXINE_SHADER_H
