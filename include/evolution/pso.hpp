#pragma once

#include "geometry/map.hpp"
#include "geometry/path.hpp"

class PSO
{
  public:
    static inline float w0PSO = 0.3f, w1PSO = 0.2f, w2PSO = 0.2f, w3PSO = 0.1f, velocity[1000][200][2] = {};
    static inline int normalDirect[100];
    static Path *currPath, *gPath;
    static std::vector<Path*> pPath;
    static void updateVelocity(int i);

    static inline float wVPSO = 0.1f;
    static void moveMent();
    static void updateBestPath();

    static void moveFollowGradient(Point* begin, Point* middle, Point* end);
    static void planePath(Point* begin, Point* middle, int position);
    static void PSOmigrate();
};
