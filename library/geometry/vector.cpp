#include "geometry/vector.hpp"
#include <cmath>

const Point Vector::originPoint{0.0f, 0.0f};

float Vector::euclideanLength(float beginY, float beginX, float endY, float endX) {
    float deltaY = endY - beginY;
    float deltaX = endX - beginX;
    return std::sqrt(deltaY * deltaY + deltaX * deltaX);
}

float Vector::euclideanLength(const Point& begin, const Point& end) {
    return euclideanLength(begin.y, begin.x, end.y, end.x);
}

float Vector::polarAngle(const Point& begin, const Point& end) {
    float deltaY = end.y - begin.y;
    float deltaX = end.x - begin.x;
    return atan2(deltaY, deltaX);
}

float Vector::turnAngle(const Point& begin, const Point& middle, const Point& end) {
    float BAy = begin.y - middle.y;
    float BAx = begin.x - middle.x;
    float BCy = end.y - middle.y;
    float BCx = end.x - middle.x;
    float dot = BAx * BCx + BAy * BCy;
    float cross = std::fabs(BAx * BCy - BAy * BCx);
    return atan2(cross, dot);
}

float Vector::smallAngleRatio = 0.1f;
bool Vector::isSmallAngle(const Point& begin, const Point& middle, const Point& end) {
    float ABy = begin.y - middle.y;
    float ABx = begin.x - middle.x;
    float BCy = end.y - middle.y;
    float BCx = end.x - middle.x;
    float normAB = fabs(ABy) + fabs(ABx);
    float normBC = fabs(BCy) + fabs(BCx);
    float cross = fabs(ABx * BCy - ABy * BCx);
    return cross < smallAngleRatio * normAB * normBC;
}

float Vector::moveLength = 2.5f;
void Vector::offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end) {
    float normalVector_y = (end.x - begin.x);
    float normalVector_x = -(end.y - begin.y);
    middle.x += Vector::moveLength * normalVector_x;
    middle.y += Vector::moveLength * normalVector_y;
}

void Vector::offsetMiddleOnePixelToReduceBend(const Point& begin, Point& middle, const Point& end) {
    float normalVector_y = (end.x - begin.x);
    float normalVector_x = -(end.y - begin.y);
    float length = euclideanLength(begin, end);
    middle.x += Vector::moveLength * normalVector_x / length;
    middle.y += Vector::moveLength * normalVector_y / length;
}

bool Vector::isValidVector(const Point& begin, const Point& end) {
    float xBegin = begin.x;
    float yBegin = begin.y;
    float length = euclideanLength(begin, end);
    float cos = (end.x - xBegin) / length;
    float sin = (end.y - yBegin) / length;
    for (float step = 0; step <= length; ++step) {
        if (!Point::isValidPosition(yBegin + step * sin, xBegin + step * cos)) {
            return false;
        }
    }
    return true;
}