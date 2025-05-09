#pragma once

#include "types.hpp"
#include <utility>

namespace algorithm {
vtzy_types::path* aStar();
void decreaseDimension();
vtzy_types::path* makeCopyPath(vtzy_types::path* p);
void setPathFromAstar();
void updateBestPath();
void updateV(int i);
void PSOmigrate();
void PSO();
vtzy_types::path* mutation(vtzy_types::path* p, float toiu);
vtzy_types::path* combination1(vtzy_types::path* p, vtzy_types::path* q);
vtzy_types::path* combination2(vtzy_types::path* p, vtzy_types::path* q);
void ES(float toiu);
void lastSocial();
void saveExe();
void PSOES(float toiu, int loop);
} // namespace algorithm