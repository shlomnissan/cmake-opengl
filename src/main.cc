// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <memory>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaders/vertex.h>
#include <shaders/fragment.h>

struct glfw_window_deleter {
    void operator()(GLFWwindow* window) const {
        glfwDestroyWindow(window);
    }
};
using GLFWwindow_ptr = std::unique_ptr<GLFWwindow, glfw_window_deleter>;

auto error_callback(int error, const char* message) -> void;
auto resize_callback(GLFWwindow *window, int width, int height) -> void;
auto key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void;

auto main() -> int {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // configure window

    constexpr int width = 800;
    constexpr int height = 600;
    GLFWwindow_ptr window {
        glfwCreateWindow(width, height, "OpenGL window", nullptr, nullptr)
    };
    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window.get());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window.get(), key_callback);
    glfwSetFramebufferSizeCallback(window.get(), resize_callback);

    glViewport(0, 0, width, height);

    // build and compile a shader program

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &_SHADER_vertex, nullptr);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &_SHADER_fragment, nullptr);
    glCompileShader(fragment_shader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set up vertex data and attributes

    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::array<GLfloat, 9> vertices {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top
    };
    
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while(!glfwWindowShouldClose(window.get())) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window.get());
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

auto error_callback(int error, const char* message) -> void {
    std::cerr << "Error (" << error << "): " << message << '\n';
}

auto resize_callback(GLFWwindow *window, int width, int height) -> void {
    glViewport(0, 0, width, height);
}

auto key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}