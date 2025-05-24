#include "geometry/map.hpp"
#include <cmath>

float Map::distanceToFinish(float fromX, float fromY) {
    float deltaX = GlobalState::finishPoint.x - fromX;
    float deltaY = GlobalState::finishPoint.y - fromY;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

bool Map::mapContainPoint(int targetX, int targetY) {
    if (targetX < 0 || targetY < 0 || targetX > GlobalState::mapHeight ||
        targetY > GlobalState::mapWidth)
        return false;
    if (GlobalState::mapGradient[targetX][targetY] > 1000000) return false;
    return true;
}

bool Map::mapContainPoint(float targetX, float targetY) {
    return mapContainPoint(static_cast<int>(targetX), static_cast<int>(targetY));
}

bool Map::mapContainPoint(const Point& point) {
    return mapContainPoint(point.x, point.y);
}