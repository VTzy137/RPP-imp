#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/openGl.hpp"
#include "app.hpp"
#include "evolution/pso.hpp"
#include "evolution/social.hpp"
#include "function/init_population.hpp"
#include "geometry/map.hpp"
#include "strategy/psoes.hpp"
#include "strategy/solution.hpp"
#include "utils/input.hpp"
#include "UI/opencv.hpp"

/**
 * @brief Initializes the application, reads the map, sets up populations, runs algorithms (A*,
 * PSOES), and visualizes results.
 */
void solution1()
{
    std::cout << "start solution1" << std::endl;

    Map::markMapGradient();
    for(int i = 0; i < 300; i++)
    {
        OpenCV::drawPoint(new Point(Map::startPoint.y, Map::startPoint.x), cv::Scalar(255, 0, 0));
        OpenCV::showImage();
    }

    // std::cout << "start init population" << std::endl;
    // for (int i = 0; i < 30; i++)
    // {

    //     Point* tmp = new Point(Map::startPoint.y, Map::startPoint.x, nullptr);
    //     Point* tmp1 = new Point(Map::finishPoint.y, Map::finishPoint.x, nullptr);

    //     PSO::normalDirect[i] = init_population::initRandPath(tmp, tmp1);

    //     Path initRandPath = Path(tmp);
    //     Path::population.push_back(initRandPath);
    // }
    
    // std::cout << "finish init population" << std::endl;

    // Path* astarRes = init_population::AStarSearch();
    // Path::gPath = astarRes;

    // std::cout << "start PSOES" << std::endl;

    // PSOES(60.0, 10000);
    // std::cout << "finish PSOES" << std::endl;

    // Social::lastSocial();
    // // cout << pathLen <<endl;
    // for (int i = 0; i < Path::population.size(); i++)
    // {
    //     if (i != 0)
    //         std::cout << -1 << std::endl;
    //     Point* tmp = Path::population[i].begin;
    //     while (tmp != nullptr)
    //     {
    //         std::cout << tmp->x / 2 << " " << tmp->y / 2 << std::endl;
    //         tmp = tmp->nextPoint;
    //     }
    // }
    // Path::gPath->calculatePathTargetScore();
    // std::cout << -2 << std::endl;
    // std::cout << std::endl
    //           << "MOPSOES angle: " << Path::gPath->angle << " \t,distance: " << Path::gPath->distance << std::endl;
}