#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <thirdparty/include/GLAD/glad.h>
#include <thirdparty/include/GLFW/glfw3.h>
#include <thirdparty/include/cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include <thirdparty/include/STB/stb_image.h>

#define VOXINE_IMPLEMENTATION
#include "shader.h"
#include "texture.h"
#include "startup.h"

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void) {
    window_t* window = init_window(800, 600, "testing");
    create_context(window);

    shader_program shader_program = create_shader_program("assets/shaders/vertshader.glsl", "assets/shaders/fragshader.glsl");

    float vertices[] = {
        // positions         // uv coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left    
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    unsigned int VAO, VBO, EBO;

    // generate the buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribue
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // uv attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    texture texture1 = create_texture("assets/textures/wall.jpg", false);
    stbi_set_flip_vertically_on_load(true);
    texture texture2 = create_texture("assets/textures/awesomeface.png", true);

    activate_shader_program(shader_program);
    uniform_set_int(shader_program, "texture1", 0);
    uniform_set_int(shader_program, "texture2", 1);
    mat4 trans = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1},
    };
    glm_translate(trans, (vec3){0.0f, 0.0f, 0.0f});
    glm_rotate(trans, glm_rad(90.0f), (vec3){0.0f, 0.0f, 1.0f});

    // vox_activate_program(shader_program);
    uniform_set_mat4(shader_program, "transform", (float*)trans);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.texture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free_shader_program(shader_program);
    glfwTerminate();
    return 0;
}
