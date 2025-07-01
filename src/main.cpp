#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/opencv.hpp"
#include "app.hpp"
#include "strategy/rpp_imp.hpp"
#include "utils/hyperparameter.hpp"
#include "utils/input.hpp"

int main(int argc, char* argv[])
{
    std::cout << "=== OpenCV Visualization Demo ===" << std::endl;
    runApp();

    srand(time(0));
    clock_t startTime = clock();

    Input::readMap(2);
    std::cout << "read map done" << std::endl;

    OpenCV::calcResize();
    std::cout << "calc resize done" << std::endl;

    rppImp();

    std::cout << "Demo complete! Press any key to exit..." << std::endl;
    OpenCV::waitForKey();
    OpenCV::closeWindow();

    clock_t endTime = clock();
    std::cout << "Total execution time: " << (endTime - startTime) << " ms" << std::endl;

    return 0;
}
