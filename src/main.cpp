#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/openGl.hpp"
#include "app.hpp"
#include "strategy/solution.hpp"
#include "utils/hyperparameter.hpp"
#include "utils/input.hpp"

/**
 * @file main.cpp
 * @brief Main entry point for the RPP-imp application. Initializes the application, reads input, runs
 * algorithms, and manages visualization.
 *
 * This file demonstrates the main workflow of the RPP-imp project, including reading map data,
 * initializing populations, running optimization algorithms, and visualizing results using OpenGL.
 */
int main(int argc, char* argv[])
{

    runApp();

    srand(time(0));
    clock_t startt = clock();

    Input::readMap();

    solution1();

    // changeToInitGraph();
    clock_t endd = clock();
    std::cout << std::endl << endd - startt;

    // std::string configPath = std::string(ASSET_PATH) + "/config.json";
    // std::ifstream file(std::string(ASSET_PATH) + "/config.json");
    // Config cfg = load_config(configPath);
    // std::cout << "Original mutation rate: " << cfg.mutation_rate << "\n";
    // update_config(configPath, "mutation_rate", cfg.mutation_rate * 1.1);


    return 0;
}
