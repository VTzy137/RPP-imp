#include "evolution/es.hpp"
#include "evolution/operator/combination.hpp"
#include "evolution/operator/mutation.hpp"
#include "geometry/path.hpp"

void ES::ES1(double toiu)
{
    for (int i = 0; i < Path::population.size(); ++i)
    {
        int pathLen = Path::population[i].numPoints();
        Path* tmp = Mutation::mutation(&Path::population[i], toiu);
        if (Path::betterPath(*tmp, Path::population[i]))
        {
            Path::population[i] = *combination1(tmp, &Path::pPath[i]);
        }
    }
}