#include "evolution/mutation.hpp"
#include "function/path.hpp"
#include <cmath>
#include <random>

float Mutation::est = 1.5f;

vtzy_types::path* Mutation::mutation(vtzy_types::path* originalPath, float mutationStrength) {
    // Create starting point for offspring
    vtzy_types::point* currentOriginal = originalPath->begin;
    vtzy_types::point* currentOffspring =
        new vtzy_types::point(currentOriginal->x, currentOriginal->y, nullptr);
    vtzy_types::path* offspring = new vtzy_types::path(currentOffspring);

    // Move to next point
    currentOriginal = currentOriginal->next;

    // Mutation parameters
    const float mutationRadius =
        static_cast<float>(rand() % static_cast<int>(vtzy_types::pathLen * est / 4));
    const float xOffset = (rand() % 200 - 100) / mutationStrength;
    const float yOffset = (rand() % 200 - 100) / mutationStrength;
    const float centerPosition = rand() % (vtzy_types::pathLen + 6) - 3;

    float currentPosition = 0;

    // Process each point in the path
    while (currentOriginal->next != nullptr) {
        float weight =
            1.0f - std::min(1.0f, std::abs(currentPosition - centerPosition) / mutationRadius);

        // Create mutated point
        currentOffspring->next = new vtzy_types::point(
            currentOriginal->x + xOffset * weight, currentOriginal->y + yOffset * weight, nullptr);

        // Check if the new line segment is valid
        if (!path::checkValidLine(currentOffspring, currentOffspring->next)) {
            // If invalid, clean up and return original path
            delete offspring;
            return originalPath;
        }

        // Move to next point
        currentOffspring = currentOffspring->next;
        currentOriginal = currentOriginal->next;
        currentPosition++;
    }

    // Add final point
    currentOffspring->next = new vtzy_types::point(currentOriginal->x, currentOriginal->y, nullptr);

    // Calculate path metrics
    path::pathFunc(offspring);

    return offspring;
}
