#include "evolution/es.hpp"
#include "geometry/path.hpp"
#include <iostream>

Path* ES::combination(Path* dadPath, Path* momPath)
{
    if (momPath == nullptr)
    {
        return nullptr;
    }

    Point* dadPoint = dadPath->begin;
    Point* momPoint = momPath->begin->nextPoint;
    Point* offPoint = new Point(dadPoint->x, dadPoint->y, nullptr);

    dadPoint = dadPoint->nextPoint;
    Path* offPath = new Path(offPoint);

    while (dadPoint->nextPoint != nullptr)
    {
        offPoint->nextPoint = new Point((dadPoint->x + momPoint->x) / 2, (dadPoint->y + momPoint->y) / 2, nullptr);
        offPoint = offPoint->nextPoint;
        dadPoint = dadPoint->nextPoint;
        momPoint = momPoint->nextPoint;
    }

    offPoint->nextPoint = new Point(dadPoint->x, dadPoint->y, nullptr);
    offPath->calculatePathTargetScore();
    return offPath;
}

Path* ES::mutateGroupPoint(Point* refPoint, float length, int centerPoint)
{
    float y1 = (static_cast<float>(rand() % 200 - 100)) / ES::rangeMutation;
    float x1 = (static_cast<float>(rand() % 200 - 100)) / ES::rangeMutation;

    int pointIndex = 0;
    Point* offPoint = new Point(refPoint->y, refPoint->x, nullptr);
    Path* offspring = new Path(offPoint);
    refPoint = refPoint->nextPoint;
    while (refPoint->nextPoint != nullptr)
    {
        float wei = 1 - std::min(1.0f, std::abs(pointIndex++ - centerPoint) / length);
        offPoint->nextPoint = new Point(refPoint->y + y1 * wei, refPoint->x + x1 * wei, nullptr);
        if (!Vector::isValidVector(*offPoint, *offPoint->nextPoint))
            return nullptr;
        offPoint = offPoint->nextPoint;
        refPoint = refPoint->nextPoint;
    }

    offPoint->nextPoint = new Point(refPoint->y, refPoint->x, nullptr);
    return offspring;
}

float ES::est = 1.5f;
inline static int expandCenter = 6;
inline static int offsetCenterPoint = 3;
Path* ES::mutation(Path* parent)
{
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
    for (int individual = 0; individual < Path::population.size(); ++individual)
    {
        // int pathLen = Path::population[i].numPoints();
        std::cout << "pathEvolutionStrategy: mutation" << std::endl;
        Path* mutatedPath = ES::mutation(Path::population[individual]);
        std::cout << "pathEvolutionStrategy: mutation done" << std::endl;

        if (Path::betterPath(*mutatedPath, *Path::population[individual]))
        {
            std::cout << "pathEvolutionStrategy: betterPath" << std::endl;
            Path::population[individual] = mutatedPath;
            // Path::population[i].changePathTo(*combination1(tmp, &Path::pPath[i]));
        }
    }
}