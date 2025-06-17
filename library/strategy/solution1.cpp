#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/opencv.hpp"
#include "app.hpp"
#include "evolution/pso.hpp"
#include "evolution/social.hpp"
#include "function/init_population.hpp"
#include "geometry/map.hpp"
#include "strategy/psoes.hpp"
#include "strategy/solution.hpp"
#include "utils/input.hpp"


/**
 * @brief Initializes the application, reads the map, sets up populations, runs algorithms (A*,
 * PSOES), and visualizes results.
 */
void solution1()
{
    std::cout << "start solution1" << std::endl;

    Map::markMapGradient();

    std::cout << "marked map gradient" << std::endl;

    OpenCV::saveMapGradient();
    std::cout << "saved map gradient" << std::endl;
    OpenCV::clearCanvasWithMap();
    OpenCV::showImage();
    OpenCV::waitForKey();
    OpenCV::clearCanvasWithMap();

    std::cout << "start init population" << std::endl;
    for (int i = 0; i < 30; i++)
    {
        Point* tmp = new Point(Map::startPoint.y, Map::startPoint.x, nullptr);
        Point* tmp1 = new Point(Map::finishPoint.y, Map::finishPoint.x, nullptr);

        PSO::normalDirect[i] = init_population::initRandPath(tmp, tmp1);

        Path::population.push_back(new Path(tmp));
        Point* tmp2 = Path::population[i]->begin;
        while (tmp2 != nullptr)
        {
            std::cout << tmp2->y << " " << tmp2->x << std::endl;
            tmp2 = tmp2->nextPoint;
        }
        std::cout << "population[i]->numPoints(): " << Path::population[i]->numPoints() << std::endl;
        OpenCV::drawPath(Path::population[i], cv::Scalar(200, 200, 0));
    }

    OpenCV::showImage();
    OpenCV::waitForKey();
    OpenCV::clearCanvasWithMap();

    std::cout << "finish init population" << std::endl;

    // Path* astarRes = init_population::AStarSearch();
    // Path::gPath = astarRes;
    // Path::population.push_back(Path::gPath);

    std::cout << "start PSOES" << std::endl;

    OpenCV::clearCanvasWithMap();

    PSOES();
    std::cout << "finish PSOES" << std::endl;

    Social::lastSocial();

    OpenCV::clearCanvasWithMap();
    for (int i = 0; i < Path::population.size(); i++)
    {
        if (i != 0)
            std::cout << -1 << std::endl;
        Point* tmp = Path::population[i]->begin;
        while (tmp != nullptr)
        {
            std::cout << tmp->x / 2 << " " << tmp->y / 2 << std::endl;
            tmp = tmp->nextPoint;
        }
    }
    OpenCV::drawPath(Path::gPath);
    OpenCV::showImage();
    OpenCV::waitForKey();

    Path::gPath->calculatePathTargetScore();
    std::cout << -2 << std::endl;
    std::cout << std::endl
              << "MOPSOES angle: " << Path::gPath->angle << " \t,distance: " << Path::gPath->distance << std::endl;
}