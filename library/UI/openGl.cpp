#include "UI/openGl.h"
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace OpenGLUI {
void drawLineStrip(std::vector<std::pair<int, int>>& line, int width, int height) {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "Line Viewer", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : line) {
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
