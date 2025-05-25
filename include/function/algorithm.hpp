#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include "types.hpp"
#include <utility>

namespace algorithm {
path* aStar();
void decreaseDimension();
path* makeCopyPath(path* p);
void setPathFromAstar();
void updateBestPath();
void updateV(int i);
void PSOmigrate();
void PSO();
vtzy_types::path* mutation(path* p, float toiu);
path* combination1(path* p, path* q);
path* combination2(path* p, path* q);
void ES(float toiu);
void lastSocial();
void saveExe();
} // namespace algorithm