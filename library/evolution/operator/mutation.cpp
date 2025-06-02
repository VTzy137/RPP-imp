#include "evolution/operator/mutation.hpp"
#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include "global_type.hpp"
#include <cmath>
#include <iostream>

float Mutation::est = 1.5f;
Path* Mutation::mutation(Path* p, float toiu)
{
    std::cout << "p->begin->y: " << p->begin->y << std::endl;
    Point* tmp = p->begin;
    Point* offPoint = new Point(tmp->y, tmp->x, nullptr);
    Path* offspring = new Path(offPoint);
    tmp = tmp->nextPoint;
    std::cout << "numPoints: " << p->numPoints() << " est: " << est << " toiu: " << toiu << std::endl;
    int maxKeke = static_cast<int>(p->numPoints() * est / 4);
    float keke = static_cast<float>(rand() % maxKeke);

    // std::cout << "maxKeke: " << maxKeke << std::endl;
    // std::cout << "keke: " << keke << std::endl;
    float y1 = (static_cast<float>(rand() % 200 - 100)) / toiu;
    float x1 = (static_cast<float>(rand() % 200 - 100)) / toiu;

    // float keke = static_cast<float>(rand() % static_cast<int>(p->numPoints() * est / 4));
    // float y1 = static_cast<float>(rand() % 200 - 100) / (toiu);
    // float x1 = static_cast<float>(rand() % 200 - 100) / (toiu);
    std::cout << "y1: " << y1 << std::endl;
    float stt = 0;
    float posPoint = static_cast<float>(rand() % static_cast<int>(p->numPoints() + 6) - 3);

    std::cout << "keke: " << keke << std::endl;

    while (tmp->nextPoint != nullptr)
    {
        float wei = 1 - std::min(1.0f, std::abs(stt++ - posPoint) / keke);
        offPoint->nextPoint = new Point(tmp->y + y1 * wei, tmp->x + x1 * wei, nullptr);
        if (!Vector::isValidVector(*offPoint, *offPoint->nextPoint))
            return p;
        offPoint = offPoint->nextPoint;
        tmp = tmp->nextPoint;
    }
    std::cout << "tmp->y: " << tmp->y << std::endl;
    offPoint->nextPoint = new Point(tmp->y, tmp->x, nullptr);
    offspring->calculatePathTargetScore();
    // offspring->simplifyPath();
    return offspring;
}
