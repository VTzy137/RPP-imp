#include "utils/input.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Input::readMap() {

    int nearPoint[8][2] = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
    vtzy_types::point *start, *finish, *obstacles[1000], *initStart, *initFinish;
    int mapHeight = 0, mapWidth = 0, numObstacle = 0;
    int graphStatus[1000][1000] = {};

    vtzy_types::point relative;

    // yes
    std::string configPath = std::string(ASSET_PATH) + "/";
    std::ifstream file(std::string(ASSET_PATH) + "/input");
    int numInput = 1;

    std::string fp1 = configPath + "input/map" + std::to_string(numInput) + ".txt";
    FILE* input = freopen(fp1.c_str(), "r", stdin);
    if (!input) {
        std::cerr << "Error: Could not open input file: " << fp1 << std::endl;
        // exit(1);
    }
    std::string fp2 = configPath + "output/out" + std::to_string(numInput) + ".txt";
    std::cout << fp1 << std::endl << fp2 << std::endl;
    std::cout << "yes" << std::endl;
    // FILE* output = freopen(&fp2[0], "w", stdout);
    // if (!output) {
    //     std::cerr << "Error: Could not open output file: " << fp2 << std::endl;
    //     exit(1);
    // }
    vtzy_types::start = new vtzy_types::point();
    vtzy_types::finish = new vtzy_types::point();
    std::cin >> vtzy_types::mapHeight >> vtzy_types::mapWidth;
    std::cin >> vtzy_types::start->x >> vtzy_types::start->y >> vtzy_types::finish->x >>
        vtzy_types::finish->y;
    std::cin >> vtzy_types::numObstacle;
    vtzy_types::start->x *= 2;
    vtzy_types::start->y *= 2;
    vtzy_types::finish->x *= 2;
    vtzy_types::finish->y *= 2;
    vtzy_types::mapHeight *= 2;
    vtzy_types::mapWidth *= 2;

    std::string s;
    for (int i = 0; i < vtzy_types::numObstacle; ++i) {
        std::cin.ignore();
        std::getline(std::cin, s);
        // cout << s << endl;
        std::stringstream ss(s);
        float x1, y1;
        while (ss >> x1) {
            ss >> y1;
            x1 *= 2;
            y1 *= 2;
            vtzy_types::obstacles[i] = new vtzy_types::point(x1, y1, vtzy_types::obstacles[i]);
        }
    }
    vtzy_types::obstacles[vtzy_types::numObstacle] =
        new vtzy_types::point(-0, -0, vtzy_types::obstacles[vtzy_types::numObstacle]);
    vtzy_types::obstacles[vtzy_types::numObstacle] = new vtzy_types::point(
        vtzy_types::mapWidth - 0, -0, vtzy_types::obstacles[vtzy_types::numObstacle]);
    vtzy_types::obstacles[vtzy_types::numObstacle] =
        new vtzy_types::point(vtzy_types::mapWidth - 0, vtzy_types::mapHeight - 0,
                              vtzy_types::obstacles[vtzy_types::numObstacle]);
    vtzy_types::obstacles[vtzy_types::numObstacle] = new vtzy_types::point(
        -0, vtzy_types::mapHeight - 0, vtzy_types::obstacles[vtzy_types::numObstacle]);
    ++vtzy_types::numObstacle;
}
