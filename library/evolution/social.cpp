#include "evolution/social.hpp"
#include "UI/opencv.hpp"
#include "geometry/path.hpp"
#include <algorithm>
#include <iostream>

namespace
{
// Helper function to check dominance for all population pairs
void markDominatedPaths()
{
    const int populationSize = Path::population.size();
    for (int i = 0; i < populationSize; ++i)
    {
        Path::population[i]->calculatePathTargetScore();
        for (int j = 0; j < populationSize; ++j)
        {
            if (!Path::population[i]->alive || !Path::population[j]->alive)
            {
                continue;
            }

            const int isDominant = Path::dominantPath(*Path::population[i], *Path::population[j]);
            if (isDominant)
            {
                Path::population[j]->alive = false;
            }
        }
    }
}

// Helper function to compact population by removing dead paths
void compactPopulation()
{
    const int populationSize = Path::population.size();
    int aliveCount = 0;

    for (int i = 0; i < populationSize; ++i)
    {
        if (!Path::population[i]->alive)
        {
            continue;
        }
        Path::population[aliveCount] = Path::population[i];
        ++aliveCount;
    }

    Path::population.erase(Path::population.begin() + aliveCount, Path::population.end());
}

// Helper function to find the best path among alive population
void updateGlobalBestPath()
{
    Path::gPath = Path::population[0];
    const int populationSize = Path::population.size();

    for (int i = 0; i < populationSize; ++i)
    {
        if (Path::betterPath(*Path::population[i], *Path::gPath))
        {
            Path::gPath = Path::population[i];
        }
    }
}

// Helper function to mark paths based on target comparison
void markInferiorPathsByTargets()
{
    const int populationSize = Path::population.size();
    for (int i = 0; i < populationSize; ++i)
    {
        Path::population[i]->calculatePathTargetScore();
        for (int j = 0; j < i; ++j)
        {
            if (!Path::population[i]->alive || !Path::population[j]->alive)
            {
                continue;
            }

            const int targetComparison = Path::numTargetBetterPath(*Path::population[i], *Path::population[j]);
            if (targetComparison >= 2)
            {
                Path::population[j]->alive = false;
            }
        }
    }
}
} // namespace

void Social::lastSocial()
{
    std::cout << "lastSocial" << std::endl;

    markDominatedPaths();
    updateGlobalBestPath();
    compactPopulation();
}

void Social::decreaseDimension()
{
    const int populationSize = Path::population.size();
    for (int i = 0; i < populationSize; ++i)
    {
        Path::population[i]->simplifyPath();
    }
}

void Social::saveExe()
{
    decreaseDimension();
    markInferiorPathsByTargets();
    compactPopulation();

    OpenCV::clearCanvasWithMap();
    OpenCV::waitForKey();
}