#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"

namespace init_population
{

inline int rangeCurveLimit = 40;
inline int normalize = 25;
inline float minCurve = 3.0f;
bool initRandPath(Point* p, Point* q);
std::pair<Path*, bool> curvePathInit();
void addCurvePopulation(int numIndividual);

Path* AStarSearch();
void addAStarPopulation(int numIndividual);
} // namespace init_population
