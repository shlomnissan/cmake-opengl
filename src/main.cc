// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    while(!glfwWindowShouldClose(window.get())) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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