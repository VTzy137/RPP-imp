#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <vector>

struct Point2D {
    float x, y;
};

namespace OpenGL {
    std::vector<Point2D> generatePath() {
        std::vector<Point2D> path;
        for (float t = 0.0f; t < 10.0f; t += 0.1f) {
            path.push_back(Point2D{t / 10.0f, 0.5f + 0.4f * static_cast<float>(sin(t))});
        }
        return path;
    }

    void renderPath(const std::vector<Point2D>& path) {
        glBegin(GL_LINE_STRIP);
        for (const auto& p : path) {
            glVertex2f(p.x, p.y); // normalized coordinates [-1, 1]
        }
        glEnd();
    }

    void testOpenGL() {
        if (!glfwInit()) {
            std::cerr << "GLFW init failed\n";
            return;
        }

        GLFWwindow* window = glfwCreateWindow(800, 600, "Path Viewer", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glewInit();

        std::vector<Point2D> path = generatePath();

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // coordinate system [0,1]

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glColor3f(1.0f, 0.0f, 0.0f);
            renderPath(path);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}