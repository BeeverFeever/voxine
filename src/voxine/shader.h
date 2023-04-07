#ifndef VOXINE_SHADER_H
#define VOXINE_SHADER_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thirdparty/include/GLAD/glad.h"
#include "voxmath.h"

typedef GLuint vox_shader;
typedef GLuint vox_program;

vox_program vox_create_program(const char* vert_path, const char* frag_path);
vox_shader vox_load_shader(GLenum type, const char* path);
void vox_activate_program(vox_program program);
void vox_free_program(vox_program program);

// I may never even use some of these but they are here
void vox_uniform_int(vox_program program, const char* name, int32_t value);
void vox_uniform_uint(vox_program program, const char* name, uint32_t value);
void vox_uniform_float(vox_program program, const char* name, float value);
void vox_uniform_bool(vox_program program, const char* name, bool value);
void vox_uniform_double(vox_program program, const char* name, double value);

void vox_uniform_vec2(vox_program program, const char* name, vox_fvec2* value);
void vox_uniform_vec3(vox_program program, const char* name, vox_fvec3* value);
void vox_uniform_vec4(vox_program program, const char* name, vox_fvec4* value);

void vox_uniform_mat2(vox_program program, const char* name, vox_mat2* value);
void vox_uniform_mat3(vox_program program, const char* name, vox_mat3* value);
void vox_uniform_mat4(vox_program program, const char* name, vox_mat4* value);

#endif // VOXINE_SHADER_H
