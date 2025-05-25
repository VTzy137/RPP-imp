#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"

struct GlobalType
{
  private:
    struct Offset
    {
        int dx, dy;
    };

  public:
    inline static constexpr Offset neighbor[8] = {{1, 0},  {0, 1},  {1, 1},  {-1, 1},
                                                  {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
    inline static Point startPoint, finishPoint;
    inline static Point *obstacles[1000], *initStartPoint, *initFinishPoint;
    inline static Point relative;
    inline static float gDistance[1000][1000] = {};
    inline static int visited[1000][1000] = {};
    inline static Path* astarRes;
    inline static Path *currPath, *gPath, *pPath[1000], *population[1000];
    inline static int numPopulations = 5, populationMax = 100, pathLen;
    inline static float w0PSO = 0.3, w1PSO = 0.2, w2PSO = 0.2, w3PSO = 0.1, v[1000][200][2] = {},
                        normalDirect[100];
};