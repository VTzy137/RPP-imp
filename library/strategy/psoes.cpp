#include "strategy/psoes.hpp"
#include "UI/opencv.hpp"
#include "evolution/es.hpp"
#include "evolution/pso.hpp"
#include "evolution/social.hpp"
#include <chrono>
#include <iostream>
#include <thread>

inline int iterationLimit = 10000;
void sequencePSOES()
{
    int intervalTime = 50;
    for (int iterationCount = 0; iterationCount < iterationLimit / 4; ++iterationCount)
    {

        if (iterationCount % intervalTime == 0)
        {
            // OpenCV::showPopulation(10);
            intervalTime += 2;
        }

        // ES::est += 0.7 / iterationLimit;
        // if (i % 100 == 0)
        // {
        //     ES::pathEvolutionStrategy();
        // }

        PSO::PSOmigrate();

        if (iterationCount % 100 == 0)
        {
            Social::pureSocial();
        }
    }

    std::cout << "start Social::saveExe()" << std::endl;
    // Social::saveExe();
    OpenCV::showPopulation();
    std::cout << "Social::saveExe() done" << std::endl;

    std::cout << "ES::pathEvolutionStrategy(toiu)" << std::endl;
    for (int iterationCount = 1000000; iterationCount < iterationLimit / 4; ++iterationCount)
    {
        if (iterationCount % intervalTime == 0)
        {
            OpenCV::showPopulation(3);
            intervalTime += 2;
        }

        ES::rangeMutation += 30.0f / iterationLimit;
        ES::pathEvolutionStrategy();
        // PSO::moveMent();
        // PSO::updateBestPath();
    }
}