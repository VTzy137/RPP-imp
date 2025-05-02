#pragma once
#include <string>

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>


struct Config {
    double learning_rate;
    int population_size;
    double mutation_rate;
};

Config load_config(const std::string& filepath);

void update_config(const std::string& filepath, const std::string& key, const nlohmann::json& new_value);

