#include "geometry/vector.hpp"
#include <cmath>

const Point Vector::originPoint{0.0f, 0.0f};


float squaredEuclideanDistance(const Point& begin, const Point& end)
{
    float dy = end.y - begin.y;
    float dx = end.x - begin.x;
    return dy * dy + dx * dx;
}


float Vector::euclideanLength(float beginY, float beginX, float endY, float endX)
{
    float dy = endY - beginY;
    float dx = endX - beginX;
    return std::sqrt(dy * dy + dx * dx);
}


float Vector::euclideanLength(const Point& begin, const Point& end)
{
    return euclideanLength(begin.y, begin.x, end.y, end.x);
}


float Vector::polarAngle(const Point& begin, const Point& end)
{
    float dy = end.y - begin.y;
    float dx = end.x - begin.x;
    return atan2(dy, dx);
}


float Vector::turnAngle(const Point& A, const Point& B, const Point& C)
{
    float BA_y = A.y - B.y;
    float BA_x = A.x - B.x;
    float BC_y = C.y - B.y;
    float BC_x = C.x - B.x;
    float dot = BA_x * BC_x + BA_y * BC_y;
    float cross = std::fabs(BA_x * BC_y - BA_y * BC_x);
    return atan2(cross, dot);
}


float Vector::moveLength = 2.5f;
void Vector::offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end)
{
    float normalVector_y = (end.x - begin.x);
    float normalVector_x = -(end.y - begin.y);
    middle.x += Vector::moveLength * normalVector_x;
    middle.y += Vector::moveLength * normalVector_y;
}


void Vector::offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end,
                                      float divide)
{
    float normalVector_y = (end.x - begin.x);
    float normalVector_x = -(end.y - begin.y);
    middle.x += Vector::moveLength * normalVector_x / divide;
    middle.y += Vector::moveLength * normalVector_y / divide;
}


float Vector::shortThreshold = 1.0f;
bool Vector::isTooShort(const Point& begin, const Point& end)
{
    return euclideanLength(begin, end) < Vector::shortThreshold;
}


bool Vector::isTooShort(float length)
{
    return length < Vector::shortThreshold;
}


bool Vector::isTooShort()
{
    return this->length < Vector::shortThreshold;
}


float Vector::angleRatioThreshold = 0.1f;
bool Vector::isSmallAngle(const Point& A, const Point& B, const Point& C)
{
    float AB_y = B.y - A.y;
    float AB_x = B.x - A.x;
    float BC_y = C.y - B.y;
    float BC_x = C.x - B.x;
    float normAB = fabs(AB_y) + fabs(AB_x);
    float normBC = fabs(BC_y) + fabs(BC_x);
    float cross = fabs(AB_x * BC_y - AB_y * BC_x);
    return cross < angleRatioThreshold * normAB * normBC;
}


float Vector::distanceStep = 1.0f;
bool Vector::isValidVector(const Point& begin, const Point& end)
{
    float begin_y = begin.y;
    float begin_x = begin.x;

    float length = euclideanLength(begin, end);

    float cos = (end.x - begin_x) / length;
    float sin = (end.y - begin_y) / length;

    for (float alongDistance = 0.0f; alongDistance <= length; alongDistance += distanceStep)
    {
        float y = begin_y + alongDistance * sin;
        float x = begin_x + alongDistance * cos;
        if (!Point::isValidPosition(y, x))
            return false;
    }
    return true;
}