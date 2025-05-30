#pragma once

#include "geometry/point.hpp"
#include "geometry/path.hpp"

namespace init_population
{
bool initRandPath(Point* p, Point* q);
Path* AStarSearch();
} // namespace init_population
