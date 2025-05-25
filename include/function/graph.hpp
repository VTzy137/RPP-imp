#pragma once

#include "types.hpp"

namespace graph {
float euclideanDistance(vtzy_types::point* p1, vtzy_types::point* p2);
bool vectorThreePoint(vtzy_types::point* p1, vtzy_types::point* p2, vtzy_types::point* p3);
void changeToNewGraph();
void changeToInitGraph();
bool onMapSize(int i, int j);
void markPointNotCome(float x, float y);
void markPointNotCome2(float x, float y);
void markLineNotCome(vtzy_types::point* p, vtzy_types::point* q);
void smoothObstacle();
void obstacleGradient();
void markObstacle();
void resetGraphStatus();
} // namespace graph
