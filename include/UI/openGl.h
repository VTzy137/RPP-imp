#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <atomic>

#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGLUI {
    void drawLineStrip(std::vector<std::pair<int, int>>& line, int width, int height, std::atomic<bool>& running);
}
