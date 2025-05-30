#include "evolution/social.hpp"
#include "geometry/path.hpp"

void Social::lastSocial()
{
    int numPopulations = Path::population.size();
    for (int i = 0; i < numPopulations; ++i)
    {
        for (int j = 0; j < numPopulations; ++j)
        {
            if (Path::population[i].alive == false || Path::population[j].alive == false)
                continue;
            int tmp = Path::dominantPath(Path::population[i], Path::population[j]);
            if (tmp == 1)
                Path::population[i].alive = false;
            else if (tmp == -1)
                Path::population[j].alive = false;
        }
    }
    int numPopu = 0;
    for (int i = 0; i < numPopulations; i++)
    {
        if (Path::population[i].alive == false)
            continue;
        Path::pPath[numPopu] = Path(Path::population[i]);
        Path::population[numPopu] = Path(Path::population[i]);
        if (Path::betterPath(Path::pPath[numPopu], *Path::gPath))
            Path::gPath = &Path::pPath[numPopu];
        numPopu++;
    }
    Path::population.erase(Path::population.begin() + numPopu, Path::population.end());
}

void Social::decreaseDimension()
{
    for (int i = 0; i < Path::population.size(); ++i)
    {
        Path::population[i].simplifyPath();
    }
}

void Social::saveExe()
{
    decreaseDimension();
    Path::gPath = &Path::population[0];
    for (int i = 0; i < Path::population.size(); ++i)
    {
        Path::population[i].calculatePathTargetScore();
        for (int j = 0; j < i; ++j)
        {
            if (Path::population[i].alive == false || Path::population[j].alive == false)
                continue;
            int tmp = Path::numTargetBetterPath(Path::population[i], Path::population[j]);
            if (tmp == 1)
                Path::population[j].alive = false;
            else if (tmp == -1)
                Path::population[i].alive = false;
        }
    }
    int numPopu = 0;
    for (int i = 0; i < Path::population.size(); i++)
    {
        if (Path::population[i].alive == false)
            continue;
        Path::pPath[numPopu] = Path(Path::population[i]);
        Path::population[numPopu] = Path(Path::population[i]);
        if (Path::betterPath(Path::pPath[numPopu], *Path::gPath))
            Path::gPath = &Path::pPath[numPopu];
        numPopu++;
    }
    Path::population.erase(Path::population.begin() + numPopu, Path::population.end());
}