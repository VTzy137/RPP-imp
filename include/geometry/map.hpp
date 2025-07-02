#pragma once
#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include <vector>

class Map
{
  private:
    static void markObstaclePoint(int x, int y);
    static void markObstaclePoint(float x, float y);
    static void markObstacleLine(float y1, float x1, float y2, float x2);
    static void markObstacleLine(const Point& begin, const Point& end);
    static void markObstacleOutline(Point* beginPoint);

    static void markAllObstaclesOutline();
    static void markMapBoundary();
    static void markAllPointCanCome();
    static void markGradientByDistanceFromOutline();

  public:
    inline static int mapHeight = 0, mapWidth = 0;
    inline static Point startPoint, finishPoint;
    inline static int numObstacle = 0;
    inline static std::vector<Point*> obstacles;
    inline static int mapGradient[1000][1000] = {};

    static void markMapGradient();
    static void smoothMapGradient();
};