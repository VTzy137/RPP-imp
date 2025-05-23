#include "geometry/point.hpp"
#include "geometry/map.hpp"
#include "global_state.hpp"
#include <cmath>

float Point::chebyshevDistanceTo(float y, float x) const {
    float dy = std::abs(this->y - y);
    float dx = std::abs(this->x - x);
    return std::max(dy, dx);
}

float Point::chebyshevDistanceTo(const Point& target) const {
    float dy = std::abs(this->y - target.y);
    float dx = std::abs(this->x - target.x);
    return std::max(dy, dx);
}

float Point::manhattanDistanceTo(float y, float x) const {
    float dy = std::abs(this->y - y);
    float dx = std::abs(this->x - x);
    return dy + dx;
}

float Point::manhattanDistanceTo(const Point& target) const {
    float dy = std::abs(this->y - target.y);
    float dx = std::abs(this->x - target.x);
    return dy + dx;
}

float Point::euclideanDistanceTo(float y, float x) const {
    float deltaY = this->y - y;
    float deltaX = this->x - x;
    return std::sqrt(deltaY * deltaY + deltaX * deltaX);
}

float Point::euclideanDistanceTo(const Point& target) const {
    float deltaY = this->y - target.y;
    float deltaX = this->x - target.x;
    return std::sqrt(deltaY * deltaY + deltaX * deltaX);
}

bool Point::stillOnMap(float y, float x) {
    if (y < 0 || y >= GlobalState::mapHeight) return false;
    if (x < 0 || x >= GlobalState::mapWidth) return false;
    return true;
}

bool Point::stillOnMap() {
    return stillOnMap(this->y, this->x);
}

bool Point::canMoveTo(int yIndex, int xIndex) {
    return GlobalState::mapGradient[yIndex][xIndex] <= 1000000 &&
           GlobalState::mapGradient[yIndex + 1][xIndex + 1] <= 1000000 &&
           GlobalState::mapGradient[yIndex + 1][xIndex] <= 1000000 &&
           GlobalState::mapGradient[yIndex][xIndex + 1] <= 1000000;
}

bool Point::canMoveTo(float targetY, float targetX) {
    int yIndex = static_cast<int>(targetY);
    int xIndex = static_cast<int>(targetX);
    return canMoveTo(yIndex, xIndex);
}

bool Point::canMoveTo(const Point& targetPoint) {
    return canMoveTo(targetPoint.y, targetPoint.x);
}

bool Point::isValidPosition() {
    return stillOnMap() && canMoveTo(*this);
}