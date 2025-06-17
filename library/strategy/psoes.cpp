#include "strategy/psoes.hpp"
#include "UI/opencv.hpp"
#include "evolution/es.hpp"
#include "evolution/operator/mutation.hpp"
#include "evolution/pso.hpp"
#include "evolution/social.hpp"
#include <chrono>
#include <iostream>
#include <thread>
// #include "evolution/operator/combination.hpp"

inline int loop = 10000;
void PSOES()
{
    int showloop = 50;
    for (int i = 0; i < loop / 4; ++i)
    {
        // if (i % showloop == 0)
        // {
        //     OpenCV::clearCanvasWithMap();
        //     for (int j = 0; j < Path::population.size(); ++j)
        //     {
        //         OpenCV::drawPath(Path::population[j]);
        //     }
        //     OpenCV::showImage(30);
        //     showloop += 2;
        // }
        // std::this_thread::sleep_for(std::chrono::milliseconds(3));

        // ES::est += 0.7 / loop;
        // if (i % 100 == 0)
        // {
        //     ES::pathEvolutionStrategy();
        // }
        PSO::PSOmigrate();
    }

    std::cout << "start Social::saveExe()" << std::endl;
    Social::saveExe();

    std::cout << "ES::pathEvolutionStrategy(toiu)" << std::endl;
    for (int i = 0; i < loop / 4; ++i)
    {
        ES::rangeMutation += 30.0f / loop;
        ES::pathEvolutionStrategy();
        // PSO::moveMent();
        // PSO::updateBestPath();
    }
}