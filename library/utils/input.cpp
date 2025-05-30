#include "utils/input.hpp"
#include "geometry/map.hpp"
#include "geometry/path.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Input::readMap()
{
    constexpr int SCALE_FACTOR = 2;
    const std::string configPath = std::string(ASSET_PATH) + "/";
    const int numInput = 1;

    const std::string mapFilePath = configPath + "input/map" + std::to_string(numInput) + ".txt";
    std::ifstream mapFile(mapFilePath);

    if (!mapFile.is_open())
    {
        std::cerr << "Error: Could not open input file: " << mapFilePath << std::endl;
        return;
    }

    const std::string outputFilePath = configPath + "output/out" + std::to_string(numInput) + ".txt";
    std::cout << mapFilePath << std::endl << outputFilePath << std::endl;

    Map::startPoint = Point();
    Map::finishPoint = Point();

    mapFile >> Map::mapHeight >> Map::mapWidth;
    mapFile >> Map::startPoint.x >> Map::startPoint.y >> Map::finishPoint.x >> Map::finishPoint.y;
    mapFile >> Map::numObstacle;

    std::cout << Map::mapHeight << " " << Map::mapWidth << std::endl;
    std::cout << Map::startPoint.x << " " << Map::startPoint.y << " " << Map::finishPoint.x << " " << Map::finishPoint.y
              << std::endl;
    std::cout << Map::numObstacle << std::endl;

    Map::startPoint.x *= SCALE_FACTOR;
    Map::startPoint.y *= SCALE_FACTOR;
    Map::finishPoint.x *= SCALE_FACTOR;
    Map::finishPoint.y *= SCALE_FACTOR;
    Map::mapHeight *= SCALE_FACTOR;
    Map::mapWidth *= SCALE_FACTOR;

    std::string line;
    for (int i = 0; i < Map::numObstacle; ++i)
    {
        mapFile.ignore();
        std::getline(mapFile, line);
        std::cout << line << std::endl;

        std::stringstream ss(line);
        float x, y;
        while (ss >> x)
        {
            ss >> y;
            std::cout << x << " " << y << std::endl;
            std::cout << ss.str() << std::endl;
            x *= SCALE_FACTOR;
            y *= SCALE_FACTOR;
            Map::obstacles[i] = new Point(x, y, Map::obstacles[i]);
        }
    }

    const float mapWidth = Map::mapWidth;
    const float mapHeight = Map::mapHeight;


    Map::obstacles[Map::numObstacle] = new Point(0, 0, Map::obstacles[Map::numObstacle]);
    Map::obstacles[Map::numObstacle] = new Point(mapWidth, 0, Map::obstacles[Map::numObstacle]);
    Map::obstacles[Map::numObstacle] = new Point(mapWidth, mapHeight, Map::obstacles[Map::numObstacle]);
    Map::obstacles[Map::numObstacle] = new Point(0, mapHeight, Map::obstacles[Map::numObstacle]);
    std::cout << "read map" << std::endl;

    ++Map::numObstacle;
}
