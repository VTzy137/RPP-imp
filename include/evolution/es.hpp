#pragma once

#include "geometry/path.hpp"
#include "global_type.hpp"

class ES
{
  public:
    static Path* mutateGroup(Point* begin, float Gauss, int centerPoint);

    inline static int expandCenter = 6;
    inline static int offsetCenterPoint = 3;
    static Path* mutation(Path* parent);
    static float est;

    inline static float initRangeMutation = 60.0f;
    inline static float rangeMutation = initRangeMutation / 10;
    static void pathEvolutionStrategy();
};