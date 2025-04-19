#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

// Using the popular nlohmann/json library
using json = nlohmann::json;

// Save hyperparameters
void saveHyperparameters(const json& hyperparams, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << hyperparams.dump(4); // Pretty print with 4-space indent
        outFile.close();
    } else {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
    }
}

// Load hyperparameters
json loadHyperparameters(const std::string& filename) {
    json hyperparams;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        try {
            inFile >> hyperparams;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        }
        inFile.close();
    } else {
        std::cerr << "Could not open file for reading: " << filename << std::endl;
    }
    return hyperparams;
}

void exampleUseJson() {
    std::cout << "Hello, World!" << std::endl;
    json hyperparams = {
        {"learning_rate", 0.001},
        {"batch_size", 64},
        {"epochs", 10},
        {"dropout", 0.2}
    };
    
    saveHyperparameters(hyperparams, "hyperparams.json");
    
    hyperparams["temperature"] = 0.8;
    hyperparams["decay_rate"] = 0.95;
    
    saveHyperparameters(hyperparams, "hyperparams_updated.json");
    
    json loaded = loadHyperparameters("hyperparams.json");
    std::cout << "Loaded parameters: " << loaded.dump(4) << std::endl;
}