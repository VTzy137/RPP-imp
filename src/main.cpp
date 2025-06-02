#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/opencv.hpp"
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
 * initializing populations, running optimization algorithms, and visualizing results using OpenCV.
 */
int main(int argc, char* argv[])
{
    std::cout << "=== OpenCV Visualization Demo ===" << std::endl;

    runApp();

    srand(time(0));
    clock_t startt = clock();

    // OpenCV::example();

    // Input::initialize(2);
    Input::readMap(2);
    OpenCV::calcResize();


    solution1();

    std::cout << "Demo complete! Press any key to exit..." << std::endl;
    OpenCV::waitForKey();
    OpenCV::closeWindow();

    clock_t endd = clock();
    std::cout << "Total execution time: " << (endd - startt) << " ms" << std::endl;

    return 0;
}
