#include "function/genetic.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

namespace function {

    // Parameters for the genetic algorithm
    const int POPULATION_SIZE = 100;
    const int CHROMOSOME_LENGTH = 20;
    const int MAX_GENERATIONS = 100;
    const double MUTATION_RATE = 0.01;
    const double CROSSOVER_RATE = 0.7;
    
    // Define the chromosome structure
    using Chromosome = std::vector<bool>;
    
    // Generate a random chromosome
    Chromosome generateRandomChromosome(std::mt19937& rng) {
        std::uniform_int_distribution<int> dist(0, 1);
        Chromosome chromosome(CHROMOSOME_LENGTH);
        
        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            chromosome[i] = dist(rng) == 1;
        }
        
        return chromosome;
    }
    
    // Calculate fitness (example: count number of 1's)
    double calculateFitness(const Chromosome& chromosome) {
        return std::count(chromosome.begin(), chromosome.end(), true);
    }
    
    // Perform crossover between two parents
    std::pair<Chromosome, Chromosome> crossover(const Chromosome& parent1, 
                                               const Chromosome& parent2,
                                               std::mt19937& rng) {
        std::uniform_int_distribution<int> dist(1, CHROMOSOME_LENGTH - 1);
        int crossoverPoint = dist(rng);
        
        Chromosome child1 = parent1;
        Chromosome child2 = parent2;
        
        for (int i = crossoverPoint; i < CHROMOSOME_LENGTH; i++) {
            child1[i] = parent2[i];
            child2[i] = parent1[i];
        }
        
        return {child1, child2};
    }
    
    // Perform mutation
    void mutate(Chromosome& chromosome, std::mt19937& rng) {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            if (dist(rng) < MUTATION_RATE) {
                chromosome[i] = !chromosome[i];
            }
        }
    }
    
    // Select a parent using tournament selection
    Chromosome selectParent(const std::vector<Chromosome>& population, std::mt19937& rng) {
        std::uniform_int_distribution<int> dist(0, POPULATION_SIZE - 1);
        
        Chromosome contestant1 = population[dist(rng)];
        Chromosome contestant2 = population[dist(rng)];
        
        if (calculateFitness(contestant1) > calculateFitness(contestant2)) {
            return contestant1;
        } else {
            return contestant2;
        }
    }
    
    void runGeneticAlgorithm() {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 rng(rd());
        
        // Generate initial population
        std::vector<Chromosome> population(POPULATION_SIZE);
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = generateRandomChromosome(rng);
        }
        
        // Run the evolution for MAX_GENERATIONS
        for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
            // Create new population
            std::vector<Chromosome> newPopulation;
            
            // Elitism: keep the best chromosome
            auto bestIt = std::max_element(population.begin(), population.end(),
                [](const Chromosome& a, const Chromosome& b) {
                    return calculateFitness(a) < calculateFitness(b);
                });
            newPopulation.push_back(*bestIt);
            
            // Fill the rest of the population
            while (newPopulation.size() < POPULATION_SIZE) {
                // Select parents
                Chromosome parent1 = selectParent(population, rng);
                Chromosome parent2 = selectParent(population, rng);
                
                // Perform crossover with probability CROSSOVER_RATE
                std::uniform_real_distribution<double> dist(0.0, 1.0);
                std::pair<Chromosome, Chromosome> children;
                
                if (dist(rng) < CROSSOVER_RATE) {
                    children = crossover(parent1, parent2, rng);
                } else {
                    children = {parent1, parent2};
                }
                
                // Perform mutation
                mutate(children.first, rng);
                mutate(children.second, rng);
                
                // Add children to new population
                newPopulation.push_back(children.first);
                if (newPopulation.size() < POPULATION_SIZE) {
                    newPopulation.push_back(children.second);
                }
            }
            
            // Replace old population with new population
            population = newPopulation;
            
            // Print progress
            if (generation % 10 == 0) {
                auto bestIt = std::max_element(population.begin(), population.end(),
                    [](const Chromosome& a, const Chromosome& b) {
                        return calculateFitness(a) < calculateFitness(b);
                    });
                std::cout << "Generation " << generation << ": Best fitness = " 
                          << calculateFitness(*bestIt) << std::endl;
            }
        }
        
        // Print final result
        auto bestIt = std::max_element(population.begin(), population.end(),
            [](const Chromosome& a, const Chromosome& b) {
                return calculateFitness(a) < calculateFitness(b);
            });
        
        std::cout << "Final best chromosome: ";
        for (bool gene : *bestIt) {
            std::cout << (gene ? "1" : "0");
        }
        std::cout << "\nFitness: " << calculateFitness(*bestIt) << std::endl;
    }
}