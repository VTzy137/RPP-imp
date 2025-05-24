#pragma once
#include "geometry/path.hpp"

class Map
{
  public:
    inline static int mapHeight = 0, mapWidth = 0, numObstacle = 0;
    inline static int mapGradient[1000][1000] = {};
    static float distanceToFinish(float fromX, float fromY);

    static bool mapContainPoint(int targetX, int targetY);
    static bool mapContainPoint(float targetX, float targetY);
    static bool mapContainPoint(const Point& targetPoint);
};