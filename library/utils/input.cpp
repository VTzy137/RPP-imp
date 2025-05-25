#include "utils/input.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Input::readMap() {
    constexpr int SCALE_FACTOR = 2;
    const std::string configPath = std::string(ASSET_PATH) + "/";
    const int numInput = 1;

    const std::string mapFilePath = configPath + "input/map" + std::to_string(numInput) + ".txt";
    std::ifstream mapFile(mapFilePath);

    if (!mapFile.is_open()) {
        std::cerr << "Error: Could not open input file: " << mapFilePath << std::endl;
        return;
    }

    const std::string outputFilePath =
        configPath + "output/out" + std::to_string(numInput) + ".txt";
    std::cout << mapFilePath << std::endl << outputFilePath << std::endl;
    std::cout << "yes" << std::endl;

    vtzy_types::start = new vtzy_types::point();
    vtzy_types::finish = new vtzy_types::point();

    mapFile >> vtzy_types::mapHeight >> vtzy_types::mapWidth;
    mapFile >> vtzy_types::start->x >> vtzy_types::start->y >> vtzy_types::finish->x >>
        vtzy_types::finish->y;
    mapFile >> vtzy_types::numObstacle;

    vtzy_types::start->x *= SCALE_FACTOR;
    vtzy_types::start->y *= SCALE_FACTOR;
    vtzy_types::finish->x *= SCALE_FACTOR;
    vtzy_types::finish->y *= SCALE_FACTOR;
    vtzy_types::mapHeight *= SCALE_FACTOR;
    vtzy_types::mapWidth *= SCALE_FACTOR;

    std::string line;
    for (int i = 0; i < vtzy_types::numObstacle; ++i) {
        mapFile.ignore();
        std::getline(mapFile, line);

        std::stringstream ss(line);
        float x, y;
        while (ss >> x) {
            ss >> y;
            x *= SCALE_FACTOR;
            y *= SCALE_FACTOR;
            vtzy_types::obstacles[i] = new vtzy_types::point(x, y, vtzy_types::obstacles[i]);
        }
    }

    const float mapWidth = vtzy_types::mapWidth;
    const float mapHeight = vtzy_types::mapHeight;

    vtzy_types::obstacles[vtzy_types::numObstacle] =
        new vtzy_types::point(0, 0, vtzy_types::obstacles[vtzy_types::numObstacle]);
    vtzy_types::obstacles[vtzy_types::numObstacle] =
        new vtzy_types::point(mapWidth, 0, vtzy_types::obstacles[vtzy_types::numObstacle]);
    vtzy_types::obstacles[vtzy_types::numObstacle] =
        new vtzy_types::point(mapWidth, mapHeight, vtzy_types::obstacles[vtzy_types::numObstacle]);
    vtzy_types::obstacles[vtzy_types::numObstacle] =
        new vtzy_types::point(0, mapHeight, vtzy_types::obstacles[vtzy_types::numObstacle]);

    ++vtzy_types::numObstacle;
}
