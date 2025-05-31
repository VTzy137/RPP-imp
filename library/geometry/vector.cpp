#include "geometry/vector.hpp"
#include "geometry/map.hpp"
#include "global_type.hpp"

#include <cmath>
#include <iostream>

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
    float AB_y = B.y - A.y;
    float AB_x = B.x - A.x;
    float BC_y = C.y - B.y;
    float BC_x = C.x - B.x;
    float dot = AB_y * BC_y + AB_x * BC_x;
    float cross = AB_x * BC_y - AB_y * BC_x;
    return atan2(cross, dot);
}

float Vector::moveLength = 2.5f;
void Vector::offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end)
{
    float normalVector_y = (end.x - begin.x);
    float normalVector_x = -(end.y - begin.y);
    float length = Vector::euclideanLength(begin, end);
    middle.y += Vector::moveLength * normalVector_y / length;
    middle.x += Vector::moveLength * normalVector_x / length;
}


void Vector::offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end, float divide)
{
    float normalVector_y = (end.x - begin.x);
    float normalVector_x = -(end.y - begin.y);
    middle.y += Vector::moveLength * normalVector_y / divide;
    middle.x += Vector::moveLength * normalVector_x / divide;
}


float Vector::shortThreshold = 3.0f;
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


float Vector::angleRatioThreshold = 0.03f;
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

    float sin = (end.y - begin_y) / length;
    float cos = (end.x - begin_x) / length;

    for (float alongDistance = 0.0f; alongDistance <= length; alongDistance += distanceStep)
    {
        float y = begin_y + alongDistance * sin;
        float x = begin_x + alongDistance * cos;
        if (!Point::isValidPosition(y, x))
            return false;
    }
    return true;
}


int Vector::minGradientThreshold = 800000;
std::pair<float, float> Vector::vectorGradient(float y, float x, int threshold)
{
    int y_int = static_cast<int>(y);
    int x_int = static_cast<int>(x);
    int lowestGradient = Map::mapGradient[y_int][x_int];
    if (lowestGradient < threshold)
        return std::make_pair(y, x);
    int vector_y = y, vector_x = x;
    for (const auto& neighbor : GlobalType::neighbors)
    {
        int candidate_y = y_int + neighbor.dy;
        int candidate_x = x_int + neighbor.dx;
        if (Map::mapGradient[candidate_y][candidate_x] < lowestGradient)
        {
            vector_y = candidate_y;
            vector_x = candidate_x;
            lowestGradient = Map::mapGradient[candidate_y][candidate_x];
        }
    }

    return std::make_pair(vector_y, vector_x);
}


std::pair<float, float> Vector::vectorGradientTightly(float y, float x)
{
    return vectorGradient(static_cast<int>(y), static_cast<int>(x), 0);
}