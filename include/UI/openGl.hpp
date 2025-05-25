#pragma once
#include <atomic>
#include <iostream>
#include <utility>
#include <vector>

#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "types.hpp"

namespace OpenGLUI {
GLFWwindow* initOpenGL();
void drawPoint(vtzy_types::point* point);
void drawLine(vtzy_types::point* point1, vtzy_types::point* point2);
void drawPath(vtzy_types::path* path);
} // namespace OpenGLUI
