#pragma once
#include "point.hpp"

struct Vector {
    static const Point originPoint;

    static float euclideanLength(float beginY, float beginX, float endY, float endX);
    static float euclideanLength(const Point& begin, const Point& end);

    static float polarAngle(const Point& begin, const Point& end);
    static float turnAngle(const Point& begin, const Point& middle, const Point& end);

    static float smallAngleRatio;
    static bool isSmallAngle(const Point& begin, const Point& middle, const Point& end);

    static float moveLength;
    static void offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end);
    static void offsetMiddleOnePixelToReduceBend(const Point& begin, Point& middle, const Point& end);

    static bool isValidVector(const Point& begin, const Point& end);
};