#pragma once
#include <memory>

class Point {
  public:
    float x, y;
    std::shared_ptr<Point> nextPoint;

    Point() : x(0), y(0), nextPoint(nullptr) {}
    Point(float xPosition, float yPosition, std::shared_ptr<Point> nextPointPtr = nullptr)
        : x(xPosition), y(yPosition), nextPoint(nextPointPtr) {}

    float chebyshevDistanceTo(float y, float x) const;
    float chebyshevDistanceTo(const Point& target) const;
    float manhattanDistanceTo(float y, float x) const;
    float manhattanDistanceTo(const Point& target) const;
    float euclideanDistanceTo(float y, float x) const;
    float euclideanDistanceTo(const Point& target) const;

    static bool stillOnMap(float y, float x);
    bool stillOnMap();

    static bool canMoveTo(int targetY, int targetX);
    static bool canMoveTo(float targetY, float targetX);
    static bool canMoveTo(const Point& targetPoint);

    static bool isValidPosition(float y, float x);
    bool isValidPosition();
};