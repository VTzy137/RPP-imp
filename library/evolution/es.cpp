#include "evolution/es.hpp"
#include "evolution/operator/combination.hpp"
#include "evolution/operator/mutation.hpp"
#include "geometry/path.hpp"
#include <iostream>

void ES::ES1(float toiu)
{
    for (int i = 0; i < Path::population.size(); ++i)
    {
        // int pathLen = Path::population[i].numPoints();
        std::cout << "ES1: mutation" << std::endl;
        Path* tmp = Mutation::mutation(Path::population[i], toiu);
        std::cout << "ES1: mutation done" << std::endl;

        if (Path::betterPath(*tmp, *Path::population[i]))
        {
            std::cout << "ES1: betterPath" << std::endl;
            Path::population[i] = tmp;
            // Path::population[i].changePathTo(*combination1(tmp, &Path::pPath[i]));
        }
    }
}