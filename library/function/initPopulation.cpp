#include "function/initPopulation.hpp"
#include "function/graph.hpp"
#include <cmath>
#include <iostream>

namespace init_population {
bool initRandPath(vtzy_types::point* p, vtzy_types::point* q) {
    float xBegin = p->x, yBegin = p->y, dis = graph::euclideanDistance(p, q);
    float cos = (q->x - xBegin) / dis, sin = (q->y - yBegin) / dis;
    int rrr = rand() % 40 - 25;
    for (float j = 0; j < dis; j += 20) {
        p->next = new vtzy_types::point(
            std::max(3.0f, static_cast<float>(xBegin + j * cos -
                                              rrr * sin * (1 - pow((j - dis / 2) / dis, 2)))),
            std::max(3.0f, static_cast<float>(yBegin + j * sin +
                                              rrr * cos * (1 - pow((j - dis / 2) / dis, 2)))),
            nullptr);
        p = p->next;
    }
    p->next = q;
    return (rrr < 0);
}
} // namespace init_population