#pragma once
#include "point.hpp"

struct Vector
{
    float length;

    Vector(const Point& begin, const Point& end) : length(euclideanLength(begin, end))
    {
    }

    inline static const Point originPoint;

    static float euclideanLength(float beginY, float beginX, float endY, float endX);
    static float euclideanLength(const Point& begin, const Point& end);

    static float polarAngle(const Point& begin, const Point& end);
    static float turnAngle(const Point& begin, const Point& middle, const Point& end);

    static float moveLength;
    static void offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end);
    static void offsetMiddleToReduceBend(const Point& begin, Point& middle, const Point& end,
                                         float divide);

    static float shortThreshold;
    static bool isTooShort(const Point& begin, const Point& end);
    static bool isTooShort(float length);
    bool isTooShort();

    static float angleRatioThreshold;
    static bool isSmallAngle(const Point& begin, const Point& middle, const Point& end);

    static float distanceStep;
    static bool isValidVector(const Point& begin, const Point& end);
};