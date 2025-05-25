#include "function/init_population.hpp"
#include "function/graph.hpp"
#include <cmath>
#include <iostream>

namespace init_population {
bool initRandPath(vtzy_types::point* startPoint, vtzy_types::point* endPoint) {
    constexpr float MIN_COORDINATE = 3.0f;
    constexpr float STEP_SIZE = 20.0f;
    constexpr int CURVE_AMPLITUDE_RANGE = 40;
    constexpr int CURVE_AMPLITUDE_OFFSET = 25;

    float distance = graph::euclideanDistance(startPoint, endPoint);
    float startX = startPoint->x;
    float startY = startPoint->y;

    float directionX = (endPoint->x - startX) / distance;
    float directionY = (endPoint->y - startY) / distance;

    int curveIntensity = rand() % CURVE_AMPLITUDE_RANGE - CURVE_AMPLITUDE_OFFSET;

    // std::cout << std::endl;
    // std::cout << "Population " << " path: " << std::endl;
    vtzy_types::point* currentPoint = startPoint;
    for (float step = 0; step < distance; step += STEP_SIZE) {
        float distanceRatio = (step - distance / 2) / distance;
        float curveFactor = 1 - pow(distanceRatio, 2);

        float newX = startX + step * directionX - curveIntensity * directionY * curveFactor;
        float newY = startY + step * directionY + curveIntensity * directionX * curveFactor;

        newX = std::max(MIN_COORDINATE, newX);
        newY = std::max(MIN_COORDINATE, newY);

        // std::cout << newX << " " << newY << std::endl;
        currentPoint->next = new vtzy_types::point(newX, newY, nullptr);
        currentPoint = currentPoint->next;
    }

    // std::cout << std::endl;
    currentPoint->next = endPoint;

    return (curveIntensity < 0);
}
} // namespace init_population