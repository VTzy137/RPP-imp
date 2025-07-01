#include "evolution/social.hpp"
#include "UI/opencv.hpp"
#include "evolution/pso.hpp"
#include "function/init_population.hpp"
#include "geometry/path.hpp"
#include <iostream>

void Social::lastSocial()
{
    std::cout << "lastSocial" << std::endl;
    int numPopulations = Path::population.size();
    for (int ref = 0; ref < numPopulations; ++ref)
    {
        Path::population[ref]->calculatePathTargetScore();
        for (int comp = 0; comp < numPopulations; ++comp)
        {
            if (Path::population[ref]->alive == false || Path::population[comp]->alive == false)
                continue;
            int isDominant = Path::dominantPath(*Path::population[ref], *Path::population[comp]);
            if (isDominant)
                Path::population[comp]->alive = false;
        }
    }

    Path::gPath = Path::population[0];
    int numSurvived = 0;
    for (int ref = 0; ref < numPopulations; ref++)
    {
        if (Path::population[ref]->alive == false)
        {
            continue;
        }
        Path::population[numSurvived] = Path::population[ref];
        if (Path::betterPath(*Path::population[numSurvived], *Path::gPath))
        {
            Path::gPath = Path::population[numSurvived];
        }
        numSurvived++;
    }

    for (int individual = numSurvived; individual < numPopulations; ++individual)
    {
        delete Path::population[individual];
    }
    Path::population.erase(Path::population.begin() + numSurvived, Path::population.end());
}

void Social::decreaseDimension()
{
    for (int individual = 0; individual < Path::population.size(); ++individual)
    {
        Path::population[individual]->simplifyPath();
    }
}

void Social::saveExe()
{
    decreaseDimension();
    for (int ref = 0; ref < Path::population.size(); ++ref)
    {
        Path::population[ref]->calculatePathTargetScore();
        for (int comp = 0; comp < ref; ++comp)
        {
            if (Path::population[ref]->alive == false || Path::population[comp]->alive == false)
            {
                continue;
            }
            int numTargetBetter = Path::numTargetBetterPath(*Path::population[ref], *Path::population[comp]);
            if (numTargetBetter >= 2)
            {
                Path::population[comp]->alive = false;
            }
        }
    }

    int numSurvived = 0;
    for (int ref = 0; ref < Path::population.size(); ref++)
    {
        if (Path::population[ref]->alive == false)
        {
            continue;
        }
        Path::population[numSurvived] = Path::population[ref];
        numSurvived++;
    }

    for (int individual = numSurvived; individual < Path::population.size(); ++individual)
    {
        delete Path::population[individual];
    }
    Path::population.erase(Path::population.begin() + numSurvived, Path::population.end());

    OpenCV::clearCanvasWithMap();
    OpenCV::waitForKey();
}

void Social::pureSocial()
{
    for (int individual = 0; individual < Path::population.size(); ++individual)
    {
        int numPoints = Path::population[individual]->numPoints();
        if (numPoints > 150)
        {
            delete Path::population[individual];
            std::pair<Path*, bool> curvePath = init_population::curvePathInit();
            Path::population[individual] = curvePath.first;
            PSO::normalDirect[individual] = curvePath.second;
        }
    }
}