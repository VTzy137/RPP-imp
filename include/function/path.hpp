#pragma once

#include "types.hpp"
#include <utility>

namespace path {
float distanceToFinish(float x, float y);
bool checkValidPosition(vtzy_types::point* p);
bool checkValidPosition(float x1, float y1);
bool checkValidPoint(vtzy_types::point* p);
bool checkValidPoint(int x, int y);
bool checkValidLine(vtzy_types::point* p, vtzy_types::point* q);
float angleVector(vtzy_types::point* p1, vtzy_types::point* p2);
float angleThreePoint(vtzy_types::point* p1, vtzy_types::point* p2, vtzy_types::point* p3);
void normalLine(vtzy_types::point* p1, vtzy_types::point* p2, vtzy_types::point* p3);
std::pair<float, float> returnNormalLine(vtzy_types::point* p1, vtzy_types::point* p2,
                                         vtzy_types::point* p3);
float compareTwoPath(vtzy_types::path* a, vtzy_types::path* b);
float compareTwoPath(vtzy_types::path* a, vtzy_types::path* b, float weight);
int compareSamePath(vtzy_types::path* a, vtzy_types::path* b);
int compareBadPath(vtzy_types::path* a, vtzy_types::path* b);
int dominantPath(vtzy_types::path* a, vtzy_types::path* b);
int tightlyDominantPath(vtzy_types::path* a, vtzy_types::path* b);
std::pair<float, float> gradientPoint(float x, float y);
std::pair<float, float> gradientPointTightly(float x, float y);
int pathLength(vtzy_types::path* p);
void pathFunc(vtzy_types::path* path);
void pathFunc1(vtzy_types::path* path);
} // namespace path
