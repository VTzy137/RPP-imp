#include "evolution/es.hpp"
#include "geometry/path.hpp"
#include <iostream>

Path* ES::combination(Path* p, Path* q)
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

Path* ES::mutateGroupPoint(Point* tmp, float length, int centerPoint)
{
    float y1 = (static_cast<float>(rand() % 200 - 100)) / ES::rangeMutation;
    float x1 = (static_cast<float>(rand() % 200 - 100)) / ES::rangeMutation;

    int pointIndex = 0;
    Point* offPoint = new Point(tmp->y, tmp->x, nullptr);
    Path* offspring = new Path(offPoint);
    tmp = tmp->nextPoint;
    while (tmp->nextPoint != nullptr)
    {
        float wei = 1 - std::min(1.0f, std::abs(pointIndex++ - centerPoint) / length);
        offPoint->nextPoint = new Point(tmp->y + y1 * wei, tmp->x + x1 * wei, nullptr);
        if (!Vector::isValidVector(*offPoint, *offPoint->nextPoint))
            return nullptr;
        offPoint = offPoint->nextPoint;
        tmp = tmp->nextPoint;
    }

    offPoint->nextPoint = new Point(tmp->y, tmp->x, nullptr);
    return offspring;
}

float ES::est = 1.5f;
inline static int expandCenter = 6;
inline static int offsetCenterPoint = 3;
Path* ES::mutation(Path* parent)
{
    // std::cout << "parent->begin->y: " << parent->begin->y << std::endl;
    // std::cout << "numPoints: " << parent->numPoints() << " est: " << est << " rangeMutation: " << rangeMutation
    //           << std::endl;
    int numPoints = parent->numPoints();
    int maxLength = static_cast<int>(numPoints * est / 4);
    float length = static_cast<float>(rand() % maxLength);

    int centerPoint = static_cast<float>(rand() % (numPoints + expandCenter) - offsetCenterPoint);

    Path* offspring = ES::mutateGroupPoint(parent->begin, length, centerPoint);
    if (offspring == nullptr)
    {
        return parent;
    }

    offspring->calculatePathTargetScore();
    // offspring->simplifyPath();
    return offspring;
}

void ES::pathEvolutionStrategy()
{
    for (int i = 0; i < Path::population.size(); ++i)
    {
        // int pathLen = Path::population[i].numPoints();
        std::cout << "pathEvolutionStrategy: mutation" << std::endl;
        Path* tmp = ES::mutation(Path::population[i]);
        std::cout << "pathEvolutionStrategy: mutation done" << std::endl;

        if (Path::betterPath(*tmp, *Path::population[i]))
        {
            std::cout << "pathEvolutionStrategy: betterPath" << std::endl;
            Path::population[i] = tmp;
            // Path::population[i].changePathTo(*combination1(tmp, &Path::pPath[i]));
        }
    }
}