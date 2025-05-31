#include "geometry/map.hpp"
#include <cmath>
#include <iostream>
#include <random>


namespace init_population
{

bool initRandPath(Point* p, Point* q)
{
    float yBegin = p->y, xBegin = p->x, dis = Vector::euclideanLength(*p, *q);
    float sin = (q->y - yBegin) / dis, cos = (q->x - xBegin) / dis;

    int rrr = std::rand() % 40 - 25;

    for (float j = 0; j < dis; j += 20)
    {
        p->nextPoint =
            new Point(std::max(3.0f, yBegin + j * sin + rrr * cos * (1 - powf((j - dis / 2) / dis, 2))),
                      std::max(3.0f, xBegin + j * cos - rrr * sin * (1 - powf((j - dis / 2) / dis, 2))), nullptr);
        p = p->nextPoint;
        std::cout << p->y << "-" << p->x << "  ";
    }
    std::cout << std::endl;
    p->nextPoint = q;
    return (rrr < 0);
}

} // namespace init_population
