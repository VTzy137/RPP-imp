#include <iostream>
#include <vector>

struct Point2D {
    float x, y;
};

#ifndef OPENGL_H
#define OPENGL_H

namespace OpenGL {
    std::vector<Point2D> generatePath();
    void renderPath(const std::vector<Point2D>& path);
    void testOpenGL();
}

#endif