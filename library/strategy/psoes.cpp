#include "strategy/psoes.hpp"
#include "evolution/es.hpp"
#include "evolution/operator/mutation.hpp"
#include "evolution/pso.hpp"
#include "evolution/social.hpp"
// #include "evolution/operator/combination.hpp"

void PSOES(double toiu, int loop)
{
    int showloop = 20;
    for (int i = 0; i < loop; ++i)
    {
        Mutation::est += 0.7 / loop;
        toiu += 30.0 / loop;
        // if(i < loop/10) ES(toiu/10);
        if (i < loop / 4)
            PSO::PSOmigrate();
        else if (i == loop / 4)
        {
            Social::saveExe();
        }
        else
        {
            ES::ES1(toiu);
            PSO::moveMent();
            PSO::updateBestPath();
        }
    }
}