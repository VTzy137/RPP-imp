#pragma once
#include <memory>

class Point
{
  public:
    float y, x;
    Point* nextPoint;

    Point() : y(0), x(0), nextPoint(nullptr)
    {
    }
    Point(float yPosition, float xPosition, Point* nextPointPtr = nullptr)
        : y(yPosition), x(xPosition), nextPoint(nextPointPtr)
    {
    }

    float chebyshevDistanceTo(float y, float x) const;
    float chebyshevDistanceTo(const Point& target) const;
    float manhattanDistanceTo(float y, float x) const;
    float manhattanDistanceTo(const Point& target) const;
    float euclideanDistanceTo(float y, float x) const;
    float euclideanDistanceTo(const Point& target) const;

    static bool stillOnMap(int y, int x);
    static bool stillOnMap(float y, float x);
    static bool reachBoundary(int y, int x);
    bool stillOnMap();

    static bool canMoveTo(int targetY, int targetX);
    static bool canMoveTo(float targetY, float targetX);
    static bool canMoveTo(const Point& targetPoint);

    static int gradientRisk(int y, int x);
    static int gradientRisk(float y, float x);
    int gradientRisk() const;

    static bool isValidPosition(float y, float x);
    bool isValidPosition();

    static float moveSpeedRatio;
    void moveToLowerGradient();
    void moveToLowerGradientTightly();
};