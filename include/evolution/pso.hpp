#pragma once

#include "geometry/map.hpp"
#include "geometry/path.hpp"

class PSO
{
  public:
    static inline float w0PSO = 0.3f, w1PSO = 0.2f, w2PSO = 0.2f, w3PSO = 0.1f, velocity[1000][200][2] = {};
    static inline bool normalDirect[100];
    static Path *currPath, *gPath;
    static std::vector<Path*> pPath;
    static void updateVelocity(int i);

    static inline float wVPSO = 0.1f;
    static void moveMent();
    static void updateBestPath();
    static void PSOmigrate();
};
