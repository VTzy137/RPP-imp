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
#include "utils/log.hpp"


void rppImp()
{
    std::cout << "start rppImp" << std::endl;

    Map::markMapGradient();
    std::cout << "marked map gradient" << std::endl;

    OpenCV::saveMapGradient();
    OpenCV::showImage();
    std::cout << "saved map gradient" << std::endl;

    init_population::addCurvePopulation(30);
    OpenCV::showImage();
    std::cout << "inited curve population" << std::endl;

    init_population::addAStarPopulation(1);
    OpenCV::showImage();
    std::cout << "inited astar population" << std::endl;


    std::cout << "start sequencePSOES" << std::endl;
    sequencePSOES();
    OpenCV::showPopulation();
    std::cout << "finish sequencePSOES" << std::endl;


    Social::lastSocial();
    std::cout << "lastSocial done" << std::endl;

    OpenCV::showPopulation();
    // OpenCV::drawPath(Path::gPath);

    // Log::initialize(1);
    // Log::logPopulation("population");
    // Log::close();

    // Path::gPath->calculatePathTargetScore();
    // std::cout << -2 << std::endl;
    // std::cout << std::endl
    //           << "MOPSOES angle: " << Path::gPath->angle << " \t,distance: " << Path::gPath->distance << std::endl;
}