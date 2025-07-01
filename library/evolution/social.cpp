#include "evolution/social.hpp"
#include "UI/opencv.hpp"
#include "evolution/pso.hpp"
#include "function/init_population.hpp"
#include "geometry/path.hpp"
#include <iostream>

void Social::lastSocial()
{
    int numPopulations = Path::population.size();
    for (int ref = 0; ref < numPopulations; ++ref)
    {
        Path::population[ref]->calculatePathTargetScore();
        // std::cout << "ref: " << ref << std::endl;
        // std::cout << "alive: " << Path::population[ref]->alive << std::endl;
        // std::cout << "angle: " << Path::population[ref]->angle << std::endl;
        // std::cout << "distance: " << Path::population[ref]->distance << std::endl;
        // std::cout << "risk: " << Path::population[ref]->risk << std::endl;
        for (int comp = 0; comp < ref; ++comp)
        {
            if (Path::population[ref]->alive == false || Path::population[comp]->alive == false)
            {
                continue;
            }
            int isDominant = Path::dominantPath(*Path::population[ref], *Path::population[comp]);
            if (isDominant)
            {
                Path::population[comp]->alive = false;
            }
        }
    }

    // Path::gPath = Path::population[0];
    int numSurvived = 0;
    for (int individual = 0; individual < numPopulations; individual++)
    {
        if (Path::population[individual]->alive == false)
        {
            delete Path::population[individual];
            continue;
        }
        Path::population[numSurvived] = Path::population[individual];
        // if (Path::betterPath(*Path::population[numSurvived], *Path::gPath))
        // {
        //     Path::gPath = Path::population[numSurvived];
        // }
        numSurvived++;
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
        // std::cout << "ref: " << ref << std::endl;
        // std::cout << "angle: " << Path::population[ref]->angle << std::endl;
        // std::cout << "distance: " << Path::population[ref]->distance << std::endl;
        // std::cout << "risk: " << Path::population[ref]->risk << std::endl;
        for (int comp = 0; comp < ref; ++comp)
        {
            if (Path::population[ref]->alive == false || Path::population[comp]->alive == false)
            {
                continue;
            }
            int numTargetBetter = Path::numTargetBetterPath(*Path::population[ref], *Path::population[comp]);
            if (numTargetBetter >= 3)
            {
                Path::population[comp]->alive = false;
            }
        }
    }

    int numSurvived = 0;
    for (int individual = 0; individual < Path::population.size(); individual++)
    {
        if (Path::population[individual]->alive == false)
        {
            delete Path::population[individual];
            continue;
        }
        Path::population[numSurvived] = Path::population[individual];
        numSurvived++;
    }

    Path::population.erase(Path::population.begin() + numSurvived, Path::population.end());
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