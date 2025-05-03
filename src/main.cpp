#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/openGl.h"
#include "app.h"
#include "meta/hyperparameter.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    runApp();

    std::string configPath = "../config.json";

    // Load original config
    Config cfg = load_config(configPath);
    std::cout << "Original mutation rate: " << cfg.mutation_rate << "\n";

    // Update the mutation rate
    update_config(configPath, "mutation_rate", cfg.mutation_rate * 1.1);

    // Load again to verify
    cfg = load_config(configPath);
    std::cout << "Updated mutation rate: " << cfg.mutation_rate << "\n";

    std::vector<std::pair<int, int>> line = {
        {50, 50}, {100, 150}, {200, 100}, {300, 300}, {400, 250}};

    std::thread viewer([&line]() { OpenGLUI::drawLineStrip(line, 640, 480); });

    // Example update after 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));
    line = {{10, 10}, {50, 100}, {150, 50}, {250, 300}, {350, 200}};

    viewer.join();

    return 0;
}
