#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/openGl.hpp"
#include "app.hpp"
#include "function/algorithm.hpp"
#include "function/graph.hpp"
#include "function/path.hpp"
#include "types.hpp"
#include "utils/hyperparameter.hpp"
#include "utils/input.hpp"
#include <function/initPopulation.hpp>

int main(int argc, char* argv[]) {
    runApp();

    Input::readMap();
    for (int i = 0; i < 10; i++) {
        vtzy_types::point* tmp = vtzy_types::obstacles[i];
        while (tmp != nullptr) {
            std::cout << tmp->x << " " << tmp->y << std::endl;
            tmp = tmp->next;
        }
    }

    // std::string configPath = std::string(ASSET_PATH) + "/config.json";
    // std::ifstream file(std::string(ASSET_PATH) + "/config.json");
    // Config cfg = load_config(configPath);
    // std::cout << "Original mutation rate: " << cfg.mutation_rate << "\n";
    // update_config(configPath, "mutation_rate", cfg.mutation_rate * 1.1);

    std::vector<std::pair<int, int>> line = {
        {50, 50}, {100, 150}, {200, 100}, {300, 300}, {400, 250}};

    std::atomic<bool> running(true);

    std::thread viewer([&]() { OpenGLUI::drawLineStrip(line, 640, 480, running); });

    // Example update after 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(1));
    line = {{10, 10}, {50, 100}, {150, 50}, {250, 300}, {350, 200}};
    std::this_thread::sleep_for(std::chrono::seconds(1));

    graph::markObstacle();

    for (int i = 0; i < 30; i++) {
        // findByES(start, finish);
        vtzy_types::point *tmp = new vtzy_types::point(vtzy_types::start->x, vtzy_types::start->y, nullptr),
                          *tmp1 = new vtzy_types::point(vtzy_types::finish->x, vtzy_types::finish->y, nullptr);
        vtzy_types::normalDirect[i] = init_population::initRandPath(tmp, tmp1);
        vtzy_types::population[i] = new vtzy_types::path(tmp);
        // normalDirect[i] = (rand() % 100) & 1;
        vtzy_types::numPopulations = i + 1;
    }

    // probabilisticMap();
    algorithm::aStar();
    vtzy_types::gPath = vtzy_types::astarRes;
    // setPathFromAstar();
    // resetGraphStatus();
    // cout << -1 << endl;

    algorithm::PSOES(60.0, 10000);
    algorithm::lastSocial();
    // cout << pathLen <<endl;
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        if (i != 0) std::cout << -1 << std::endl;
        vtzy_types::point* tmp = vtzy_types::population[i]->begin;
        while (tmp != nullptr) {
            std::cout << tmp->x / 2 << " " << tmp->y / 2 << std::endl;
            tmp = tmp->next;
        }
    }
    std::cout << -2 << std::endl;
    std::cout << std::endl
              << "MOPSOES angle: " << vtzy_types::gPath->angle
              << " \t,distance: " << vtzy_types::gPath->distance << std::endl;
    path::pathFunc(vtzy_types::astarRes);

    line = {};
    vtzy_types::point *tmp = vtzy_types::gPath->begin;
    while (tmp != nullptr) {
        line.push_back({(int)tmp->x, (int)tmp->y});
        tmp = tmp->next;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));

    running = false;
    viewer.join();

    return 0;
}
