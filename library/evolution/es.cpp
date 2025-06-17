#include "evolution/es.hpp"
#include "evolution/operator/combination.hpp"
#include "evolution/operator/mutation.hpp"
#include "geometry/path.hpp"
#include <iostream>

Path* ES::mutateGroup(Point* tmp, float Gauss, int centerPoint)
{
    float y1 = (static_cast<float>(rand() % 200 - 100)) / ES::rangeMutation;
    float x1 = (static_cast<float>(rand() % 200 - 100)) / ES::rangeMutation;

    int pointIndex = 0;
    Point* offPoint = new Point(tmp->y, tmp->x, nullptr);
    Path* offspring = new Path(offPoint);
    tmp = tmp->nextPoint;
    while (tmp->nextPoint != nullptr)
    {
        float wei = 1 - std::min(1.0f, std::abs(pointIndex++ - centerPoint) / Gauss);
        offPoint->nextPoint = new Point(tmp->y + y1 * wei, tmp->x + x1 * wei, nullptr);
        if (!Vector::isValidVector(*offPoint, *offPoint->nextPoint))
            return nullptr;
        offPoint = offPoint->nextPoint;
        tmp = tmp->nextPoint;
    }

    offPoint->nextPoint = new Point(tmp->y, tmp->x, nullptr);
}

float ES::est = 1.5f;
inline static int expandCenter = 6;
inline static int offsetCenterPoint = 3;
Path* ES::mutation(Path* parent)
{
    // std::cout << "parent->begin->y: " << parent->begin->y << std::endl;
    // std::cout << "numPoints: " << parent->numPoints() << " est: " << est << " rangeMutation: " << rangeMutation
    //           << std::endl;
    int maxKeke = static_cast<int>(parent->numPoints() * est / 4);
    float keke = static_cast<float>(rand() % maxKeke);


    int centerPoint = static_cast<float>(rand() % (parent->numPoints() + expandCenter) - offsetCenterPoint);

    Path* offspring = ES::mutateGroup(parent->begin, keke, centerPoint);
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