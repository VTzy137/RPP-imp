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
#include "strategy/rpp_imp.hpp"
#include "utils/input.hpp"


void rppImp()
{
    std::cout << "start rppImp" << std::endl;

    Map::markMapGradient();
    std::cout << "marked map gradient" << std::endl;

    OpenCV::saveMapGradient();
    std::cout << "saved map gradient" << std::endl;

    OpenCV::showImage();

    std::cout << "start init population" << std::endl;
    for (int individualIndex = 0; individualIndex < 30; individualIndex++)
    {
        Point* startPoint = new Point(Map::startPoint.y, Map::startPoint.x, nullptr);
        Point* finishPoint = new Point(Map::finishPoint.y, Map::finishPoint.x, nullptr);
        
        PSO::normalDirect[individualIndex] = init_population::initRandPath(startPoint, finishPoint);
        Path::population.push_back(new Path(startPoint));

        OpenCV::drawPath(Path::population[individualIndex], cv::Scalar(200, 200, 0));
    }

    // Path* astarRes = init_population::AStarSearch();
    // Path::gPath = astarRes;
    // Path::population.push_back(Path::gPath);
    std::cout << "finish init population" << std::endl;

    OpenCV::showImage();

    std::cout << "start sequencePSOES" << std::endl;
    sequencePSOES();
    std::cout << "finish sequencePSOES" << std::endl;


    std::cout << "Social::lastSocial() start" << std::endl;
    // Social::lastSocial();
    std::cout << "Social::lastSocial() done" << std::endl;

    OpenCV::showPopulation();

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
    // OpenCV::drawPath(Path::gPath);
    // OpenCV::showImage();

    OpenCV::showPopulation();

    // Path::gPath->calculatePathTargetScore();
    // std::cout << -2 << std::endl;
    // std::cout << std::endl
    //           << "MOPSOES angle: " << Path::gPath->angle << " \t,distance: " << Path::gPath->distance << std::endl;
}