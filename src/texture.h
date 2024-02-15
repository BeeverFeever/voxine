#ifndef VOXINE_TEXTURE_H
#define VOXINE_TEXTURE_H

#include <stdio.h>

#include <thirdparty/include/GLAD/glad.h>
// #include <thirdparty/include/STB/stb_image.h>

typedef struct {
    GLuint texture;
    unsigned char* data;
    int width;
    int height;
    int channels;
} texture;

texture create_texture(const char* const path, bool alpha);

#endif // VOXINE_TEXTURE_H

#ifdef VOXINE_IMPLEMENTATION

texture create_texture(const char* const path, bool alpha) {
    texture tex;

    glGenTextures(1, &tex.texture);
    glBindTexture(GL_TEXTURE_2D, tex.texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data = stbi_load(path, &tex.width, &tex.height, &tex.channels, 0);
    if (data == NULL) {
        fprintf(stderr, "ERROR: failed to load texture\n");
    }

    if (alpha)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return tex;
}

#endif // VOXINE_IMPLEMENTATION
