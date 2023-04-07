#include "shader.h"

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
    char* buffer = malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "ERROR: malloc error. %i:%s", __LINE__, __FILE__);
        exit(1);
    }
    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';
    return buffer;
}

vox_shader vox_load_shader(GLenum type, const char* path) {
    // read in and compile shader
    vox_shader shader = glCreateShader(type);
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

vox_program vox_create_program(const char* vert_path, const char* frag_path) {
    // create both shaders
    vox_shader vert = vox_load_shader(GL_VERTEX_SHADER, vert_path);
    vox_shader frag = vox_load_shader(GL_FRAGMENT_SHADER, frag_path);

    // create and link program
    vox_program program;
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

void vox_activate_program(vox_program program) {
    glUseProgram(program);
}

void vox_free_program(vox_program program) {
    glDeleteProgram(program);
}

// Uniforms
void vox_uniform_int(vox_program program, const char* name, int32_t value) {
    glUniform1i(glGetUniformLocation(program, name), value);
}
void vox_uniform_uint(vox_program program, const char* name, uint32_t value) {
    glUniform1ui(glGetUniformLocation(program, name), value);
}
void vox_uniform_float(vox_program program, const char* name, float value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}
void vox_uniform_bool(vox_program program, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(program, name), (int)value);
}
void vox_uniform_double(vox_program program, const char* name, double value) {
    glUniform1d(glGetUniformLocation(program, name), value);
}

void vox_uniform_vec2(vox_program program, const char* name, vox_fvec2* value) {
    glUniform2fv(glGetUniformLocation(program, name), 1, (GLfloat*)value);
}
void vox_uniform_vec3(vox_program program, const char* name, vox_fvec3* value) {
    glUniform3fv(glGetUniformLocation(program, name), 1, (GLfloat*)value);
}
void vox_uniform_vec4(vox_program program, const char* name, vox_fvec4* value) {
    glUniform3fv(glGetUniformLocation(program, name), 1, (GLfloat*)value);
}

void vox_uniform_mat2(vox_program program, const char* name, vox_mat2* value) {
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, (GLfloat*)value);
}
void vox_uniform_mat3(vox_program program, const char* name, vox_mat3* value) {
    glUniformMatrix3fv(glGetUniformLocation(program, name), 1, GL_FALSE, (GLfloat*)value);
}
void vox_uniform_mat4(vox_program program, const char* name, vox_mat4* value) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, (GLfloat*)value);
}
