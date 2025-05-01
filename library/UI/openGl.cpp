#include "UI/openGl.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace OpenGLUI {

void drawLineStrip(const std::vector<std::pair<int, int>>& points, int width, int height) {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "Line Strip Viewer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed\n";
        return;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, 0, height, -1, 1); // pixel coordinate system

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : points) {
            glVertex2f(p.first, p.second);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
} // namespace OpenGLUI
