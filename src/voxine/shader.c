#include <voxine/shader.h>

static FILE* open_file(const char* path, const char* mode) {
    FILE* in = fopen(path, mode);
    if (in == NULL) {
        fprintf(stderr, "ERROR: could not open %s\n%s", path, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return in;
}

static void read_file(char* buffer, const char* path) {
    FILE* file = open_file(path, "r");
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';
}

vox_shader vox_load_shader(GLenum type, const char* path) {
    vox_shader shader = glCreateShader(type);
    char* source = 0;
    read_file(source, path);
    glShaderSource(shader, 1, (const GLchar* const*)&source, NULL);
    glCompileShader(shader);

    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        fprintf(stderr, "ERROR: shader compilation: %s\n%s", path, info_log);
    }

    return shader;
}

vox_program vox_shader_program(const char* vert_path, const char* frag_path) {
    vox_shader vert = vox_load_shader(GL_VERTEX_SHADER, vert_path);
    vox_shader frag = vox_load_shader(GL_FRAGMENT_SHADER, frag_path);

    vox_program program;
    program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

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
