#ifndef VOXINE_SHADER_H
#define VOXINE_SHADER_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <thirdparty/include/GLAD/glad.h>

#include "voxmath.h"

typedef GLuint shader;
typedef GLuint shader_program;

shader_program create_shader_program(const char* vert_path, const char* frag_path);
void activate_shader_program(shader_program program);
void free_shader_program(shader_program program);

// I may never even use some of these but they are here
void uniform_set_int(shader_program program, const char* name, int32_t value);
void uniform_set_uint(shader_program program, const char* name, uint32_t value);
void uniform_set_float(shader_program program, const char* name, float value);
void uniform_set_bool(shader_program program, const char* name, bool value);
void uniform_set_double(shader_program program, const char* name, double value);

void uniform_set_vec2(shader_program program, const char* name, float* value);
void uniform_set_vec3(shader_program program, const char* name, float* value);
void uniform_set_vec4(shader_program program, const char* name, float* value);

void uniform_set_mat2(shader_program program, const char* name, float* value);
void uniform_set_mat3(shader_program program, const char* name, float* value);
void uniform_set_mat4(shader_program program, const char* name, float* value);

#endif // VOXINE_SHADER_H

#ifdef VOXINE_IMPLEMENTATION

static FILE* _open_file(const char* path, const char* mode) {
    FILE* in = fopen(path, mode);
    if (in == NULL) {
        fprintf(stderr, "ERROR: could not open %s\n%s", path, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return in; 
}

static char* _read_file(const char* path) {
    FILE* file = _open_file(path, "r");
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "ERROR: malloc error. %i:%s", __LINE__, __FILE__);
        exit(1);
    }
    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';
    return buffer;
}

static shader _load_shader(GLenum type, const char* path) {
    // read in and compile shader
    shader shader = glCreateShader(type);
    char* source = _read_file(path);
    glShaderSource(shader, 1, (const GLchar* const*)&source, NULL);
    glCompileShader(shader);

    // check for compilation errors
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        fprintf(stderr, "ERROR: shader compilation: %s\n%s", path, info_log);
    }

    free(source);
    return shader;
}

shader_program create_program(const char* vert_path, const char* frag_path) {
    // create both shaders
    shader vert = _load_shader(GL_VERTEX_SHADER, vert_path);
    shader frag = _load_shader(GL_FRAGMENT_SHADER, frag_path);

    // create and link program
    shader_program program;
    program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    // error check the program
    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        fprintf(stderr, "ERROR: shader program linking\n%s", info_log);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return program;
}

void activate_program(shader_program program) {
    glUseProgram(program);
}

void free_program(shader_program program) {
    glDeleteProgram(program);
}

// Uniforms
void uniform_set_int(shader_program program, const char* name, int32_t value) {
    glUniform1i(glGetUniformLocation(program, name), value);
}
void uniform_set_uint(shader_program program, const char* name, uint32_t value) {
    glUniform1ui(glGetUniformLocation(program, name), value);
}
void uniform_set_float(shader_program program, const char* name, float value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}
void uniform_set_bool(shader_program program, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(program, name), (int)value);
}
void uniform_set_double(shader_program program, const char* name, double value) {
    glUniform1d(glGetUniformLocation(program, name), value);
}

void uniform_set_vec2(shader_program program, const char* name, float* value) {
    glUniform2fv(glGetUniformLocation(program, name), 1, (GLfloat*)value);
}
void uniform_set_vec3(shader_program program, const char* name, float* value) {
    glUniform3fv(glGetUniformLocation(program, name), 1, (GLfloat*)value);
}
void uniform_set_vec4(shader_program program, const char* name, float* value) {
    glUniform3fv(glGetUniformLocation(program, name), 1, (GLfloat*)value);
}

void uniform_set_mat2(shader_program program, const char* name, float* value) {
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, (GLfloat*)value);
}
void uniform_set_mat3(shader_program program, const char* name, float* value) {
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, (GLfloat*)value);
}
void uniform_set_mat4(shader_program program, const char* name, float* value) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, (GLfloat*)value);
}

#endif
