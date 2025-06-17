#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"

namespace init_population
{

inline int rangeCurveLimit = 40;
inline int normalize = 25;
inline float minCurve = 3.0f;
bool initRandPath(Point* p, Point* q);


Path* AStarSearch();
} // namespace init_population
