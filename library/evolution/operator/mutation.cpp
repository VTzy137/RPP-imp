#include "evolution/operator/mutation.hpp"
#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include "global_type.hpp"
#include <cmath>


float Mutation::est = 1.5f;
Path* Mutation::mutation(Path* p, float toiu)
{
    Point *tmp = p->begin, *offPoint = new Point(tmp->x, tmp->y, nullptr);
    Path* offspring = new Path(offPoint);
    tmp = tmp->nextPoint;
    float keke = rand() % (int)(p->numPoints() * est / 4), x1 = (rand() % 200 - 100) / (toiu),
          y1 = (rand() % 200 - 100) / (toiu), stt = 0, posPoint = rand() % (p->numPoints() + 6) - 3;
    while (tmp->nextPoint != nullptr)
    {
        float wei = 1 - std::min(1.0f, std::abs(stt++ - posPoint) / keke);
        offPoint->nextPoint = new Point(tmp->x + x1 * wei, tmp->y + y1 * wei, nullptr);
        if (!Vector::isValidVector(*offPoint, *offPoint->nextPoint))
            return p;
        offPoint = offPoint->nextPoint;
        tmp = tmp->nextPoint;
    }
    offPoint->nextPoint = new Point(tmp->x, tmp->y, nullptr);
    offspring->calculatePathTargetScore();
    // offspring->simplifyPath();
    return offspring;
}
