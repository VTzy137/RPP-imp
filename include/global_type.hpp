#pragma once

#include "geometry/path.hpp"
#include "geometry/point.hpp"

struct GlobalType
{
  private:
    struct Offset
    {
        int dx, dy;
    };

  public:
    inline static constexpr Offset neighbors[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                                   {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
    inline static Point relative;
};