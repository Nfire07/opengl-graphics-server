#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

#include "glmath.h"    // Point struct, toNDCx, toNDCy
#include "triangles.h" // TriangleBuffers and related functions

int screenWidth = 600;
int screenHeight = 600;

TriangleBuffers triangleBuffers;

void render(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void error_callback(int error,const char* description);
void processInput(GLFWwindow *window);

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL - Triangle Example", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // Define triangle vertices in pixel coordinates
    Point p1 = {100, 100};
    Point p2 = {500, 100};
    Point p3 = {300, 500};

    // Create OpenGL buffers for the triangle
    triangleBuffers = createTriangleBuffers(p1, p2, p3, screenWidth, screenHeight);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        render(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    deleteTriangleBuffers(triangleBuffers);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void render(GLFWwindow* window) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawTriangleBuffers(triangleBuffers);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}
