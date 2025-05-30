#pragma once
#include "geometry/path.hpp"

class Mutation
{
    public:
        static Path* mutation(Path* p, float toiu);
        static float est;
};
