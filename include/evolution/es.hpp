#pragma once

#include "geometry/path.hpp"
#include "global_type.hpp"

class ES
{
  public:
    static Path* mutateGroupPoint(Point* begin, float Gauss, int centerPoint);

    static Path* combination(Path* p, Path* q);
    inline static int expandCenter = 6;
    inline static int offsetCenterPoint = 3;
    static Path* mutation(Path* parent);
    static float est;

    inline static float initRangeMutation = 60.0f;
    inline static float rangeMutation = initRangeMutation / 10;
    static void pathEvolutionStrategy();
};