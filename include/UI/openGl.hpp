#pragma once
#include <atomic>
#include <iostream>
#include <utility>
#include <vector>

#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "geometry/path.hpp"
#include "geometry/point.hpp"

namespace OpenGLUI
{
GLFWwindow* initOpenGL();
void drawPoint(Point* point);
void drawLine(Point* point1, Point* point2);
void drawPath(Path* path);
} // namespace OpenGLUI
