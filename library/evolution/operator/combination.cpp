#include "evolution/operator/combination.hpp"
#include "geometry/path.hpp"

Path* combination1(Path* p, Path* q)
{
    if (q == nullptr)
        return nullptr;
    Point *p1 = p->begin, *q1 = q->begin->nextPoint, *tmp1 = new Point(p1->x, p1->y, nullptr);
    p1 = p1->nextPoint;
    Path* tmp = new Path(tmp1);
    while (p1->nextPoint != nullptr)
    {
        tmp1->nextPoint = new Point((p1->x + q1->x) / 2, (p1->y + q1->y) / 2, nullptr);
        tmp1 = tmp1->nextPoint;
        p1 = p1->nextPoint;
        q1 = q1->nextPoint;
    }
    tmp1->nextPoint = new Point(p1->x, p1->y, nullptr);
    tmp->calculatePathTargetScore();
    return tmp;
}