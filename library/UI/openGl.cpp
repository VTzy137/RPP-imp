#include "UI/openGl.hpp"
#include "geometry/path.hpp"
#include <thread>

namespace OpenGLUI
{
GLFWwindow* initOpenGL()
{
    if (!glfwInit())
        return nullptr;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Animated 2D Paths", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1); // Set 2D view
    return window;
}

void drawPoint(Point* point)
{
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(point->x, point->y);
    glEnd();
}

void drawLine(Point* point1, Point* point2)
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(point1->x, point1->y);
    glVertex2f(point2->x, point2->y);
    glEnd();
}

void drawPath(Path* path)
{
    Point* tmp = path->begin;

    while (tmp != nullptr && tmp->nextPoint != nullptr)
    {
        OpenGLUI::drawLine(tmp, tmp->nextPoint);

        OpenGLUI::drawPoint(tmp);
        OpenGLUI::drawPoint(tmp->nextPoint);

        glfwSwapBuffers(glfwGetCurrentContext());

        tmp = tmp->nextPoint;
    }

    // Draw final point if it exists
    if (tmp != nullptr)
    {
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(tmp->x, tmp->y);
        glEnd();
        glfwSwapBuffers(glfwGetCurrentContext());
    }
}

} // namespace OpenGLUI

void drawLineStrip(std::vector<std::pair<int, int>>& line, int width, int height, std::atomic<bool>& running)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to init GLFW\n";
        return;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "Line Viewer", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();

    while (!glfwWindowShouldClose(window) && running)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : line)
        {
            glVertex2f(p.first, p.second);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void drawPoint(Point* point)
{
    glPointSize(15.0f);
    glBegin(GL_POINTS);
    glVertex2f(point->x, point->y);
    glEnd();
} // namespace OpenGLUI
