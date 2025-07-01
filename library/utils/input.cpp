#include "utils/input.hpp"
#include "geometry/map.hpp"
#include "geometry/path.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Input::readMap(int numInput)
{
    const std::string configPath = std::string(ASSET_PATH) + "/";

    const std::string mapFilePath = configPath + "input/map" + std::to_string(numInput) + ".txt";
    // const std::string mapFilePath = configPath + "sampleMap/map" + std::to_string(numInput) + ".txt";
    std::ifstream mapFile(mapFilePath);

    if (!mapFile.is_open())
    {
        std::cerr << "Error: Could not open input file: " << mapFilePath << std::endl;
        return;
    }


    Map::startPoint = Point();
    Map::finishPoint = Point();

    mapFile >> Map::mapHeight >> Map::mapWidth;
    mapFile >> Map::startPoint.y >> Map::startPoint.x >> Map::finishPoint.y >> Map::finishPoint.x;
    mapFile >> Map::numObstacle;


    // int SCALE_FACTOR = 500 / std::max(Map::mapHeight, Map::mapWidth);
    int SCALE_FACTOR = 2;

    Map::startPoint.y *= SCALE_FACTOR;
    Map::startPoint.x *= SCALE_FACTOR;
    Map::finishPoint.y *= SCALE_FACTOR;
    Map::finishPoint.x *= SCALE_FACTOR;
    Map::mapHeight *= SCALE_FACTOR;
    Map::mapWidth *= SCALE_FACTOR;

    std::cout << "Map size: " << Map::mapHeight << " " << Map::mapWidth << std::endl;
    std::cout << "Start point: " << Map::startPoint.y << " " << Map::startPoint.x << std::endl;
    std::cout << "Finish point: " << Map::finishPoint.y << " " << Map::finishPoint.x << std::endl;
    std::cout << "Number of obstacles: " << Map::numObstacle << std::endl;
    std::string line;

    for (int obstacleIndex = 0; obstacleIndex < Map::numObstacle; ++obstacleIndex)
    {
        Map::obstacles.push_back(nullptr);
        mapFile.ignore();
        std::getline(mapFile, line);

        std::stringstream ss(line);
        float y, x;
        while (ss >> y)
        {
            ss >> x;
            y *= SCALE_FACTOR;
            x *= SCALE_FACTOR;
            Map::obstacles[obstacleIndex] = new Point(y, x, Map::obstacles[obstacleIndex]);
        }
    }

    for (int obstacleIndex = 0; obstacleIndex < Map::numObstacle; ++obstacleIndex)
    {
        std::cout << "Obstacle " << obstacleIndex << ": ";
        Point* current = Map::obstacles[obstacleIndex];
        while (current != nullptr)
        {
            std::cout << current->y << " " << current->x << " ";
            current = current->nextPoint;
        }
        std::cout << std::endl;
    }

    const float mapWidth = Map::mapWidth;
    const float mapHeight = Map::mapHeight;

    std::cout << "mapWidth: " << mapWidth << " mapHeight: " << mapHeight << std::endl;

    Map::obstacles.push_back(nullptr);
    Map::obstacles[Map::numObstacle] = new Point(0, 0, Map::obstacles[Map::numObstacle]);
    Map::obstacles[Map::numObstacle] = new Point(mapWidth, 0, Map::obstacles[Map::numObstacle]);
    Map::obstacles[Map::numObstacle] = new Point(mapWidth, mapHeight, Map::obstacles[Map::numObstacle]);
    Map::obstacles[Map::numObstacle] = new Point(0, mapHeight, Map::obstacles[Map::numObstacle]);

    std::cout << "Obstacle " << Map::numObstacle << ": ";
    Point* current = Map::obstacles[Map::numObstacle];
    while (current != nullptr)
    {
        std::cout << current->y << " " << current->x << " ";
        current = current->nextPoint;
    }
    std::cout << std::endl;
    std::cout << "obstacles: " << Map::obstacles.size() << std::endl;

    ++Map::numObstacle;
}
