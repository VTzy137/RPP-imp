#include "evolution/social.hpp"
#include "UI/opencv.hpp"
#include "geometry/path.hpp"
#include <iostream>

void Social::lastSocial()
{
    std::cout << "lastSocial" << std::endl;
    int numPopulations = Path::population.size();
    for (int i = 0; i < numPopulations; ++i)
    {
        Path::population[i]->calculatePathTargetScore();
        for (int j = 0; j < numPopulations; ++j)
        {
            if (Path::population[i]->alive == false || Path::population[j]->alive == false)
                continue;
            int isDominant = Path::dominantPath(*Path::population[i], *Path::population[j]);
            if (isDominant)
                Path::population[j]->alive = false;
        }
    }

    Path::gPath = Path::population[0];
    int numPopu = 0;
    for (int i = 0; i < numPopulations; i++)
    {
        if (Path::population[i]->alive == false)
            continue;
        Path::population[numPopu] = Path::population[i];
        if (Path::betterPath(*Path::population[numPopu], *Path::gPath))
            Path::gPath = Path::population[numPopu];
        numPopu++;
    }

    Path::population.erase(Path::population.begin() + numPopu, Path::population.end());
}

void Social::decreaseDimension()
{
    for (int i = 0; i < Path::population.size(); ++i)
    {
        Path::population[i]->simplifyPath();
    }
}

void Social::saveExe()
{
    decreaseDimension();
    for (int i = 0; i < Path::population.size(); ++i)
    {
        Path::population[i]->calculatePathTargetScore();
        for (int j = 0; j < i; ++j)
        {
            if (Path::population[i]->alive == false || Path::population[j]->alive == false)
                continue;
            int tmp = Path::numTargetBetterPath(*Path::population[i], *Path::population[j]);
            if (tmp >= 2)
            {
                Path::population[j]->alive = false;
            }
        }
    }
    int numPopu = 0;
    for (int i = 0; i < Path::population.size(); i++)
    {
        if (Path::population[i]->alive == false)
            continue;
        Path::population[numPopu] = Path::population[i];
        numPopu++;
    }
    Path::population.erase(Path::population.begin() + numPopu, Path::population.end());

    OpenCV::clearCanvasWithMap();
    OpenCV::waitForKey();
}