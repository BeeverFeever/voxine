#ifndef VOXINE_STARTUP_H
#define VOXINE_STARTUP_H

#include <thirdparty/include/GLAD/glad.h>
#include <thirdparty/include/GLFW/glfw3.h>

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef GLFWwindow window_t;

window_t* init_window(int w, int h, const char* name);
void create_context(window_t* win);

#endif // VOXINE_STARTUP_H

#ifdef VOXINE_IMPLEMENTATION

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void create_context(window_t* win) {
    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialise GLEW\n");
        exit(1);
    }

    glViewport(0, 0, h, w);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
}

window_t* init_window(int w, int h, const char* name) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialise GLFW\n");
        exit(1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_t* window;
    window = glfwCreateWindow(w, h, name, NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open glfw window\n");
        glfwTerminate();
        exit(1);
    }
    return window;
}

#endif // VOXINE_IMPLEMENTATION
