#include "utils/hyperparameter.hpp"

using json = nlohmann::json;

Config load_config(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filepath);
    }

    json j;
    in >> j;

    Config cfg;
    cfg.learning_rate = j.value("learning_rate", 0.01);
    cfg.population_size = j.value("population_size", 100);
    cfg.mutation_rate = j.value("mutation_rate", 0.1);
    return cfg;
}

void update_config(const std::string& filepath, const std::string& key,
                   const nlohmann::json& new_value) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filepath);
    }

    nlohmann::json j;
    in >> j;
    in.close();

    j[key] = new_value;

    std::ofstream out(filepath);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to write config file: " + filepath);
    }

    out << j.dump(4); // pretty-print with indent=4
}
