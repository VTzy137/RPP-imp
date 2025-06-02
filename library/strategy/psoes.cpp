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

inline float toiu = 60.0f;
inline int loop = 10000;
void PSOES()
{
    int showloop = 5;
    for (int i = 0; i < loop; ++i)
    {
        if (i % showloop == 0)
        {
            OpenCV::clearCanvasWithMap();
            for (int j = 0; j < Path::population.size(); ++j)
            {
                OpenCV::drawPath(Path::population[j]);
            }
            OpenCV::showImage(30);
            showloop += 2;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        Mutation::est += 0.7 / loop;
        toiu += 30.0f / loop;
        // if(i < loop/10) ES(toiu/10);
        if (i < loop / 4)
            PSO::PSOmigrate();
        else if (i == loop / 4)
        {
            std::cout << "start Social::saveExe()" << std::endl;
            Social::saveExe();
        }
        else
        {
            std::cout << "ES::ES1(toiu)" << std::endl;
            ES::ES1(toiu);
            // PSO::moveMent();
            // PSO::updateBestPath();
        }
    }
}