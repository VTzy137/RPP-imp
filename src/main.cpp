#include <iostream>
#include <utility>
#include <vector>

#include "UI/openGl.h"
#include "meta/hyperparameter.h"
#include "app.h"
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

    return 0;
}