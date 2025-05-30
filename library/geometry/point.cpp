#include "geometry/point.hpp"
#include "geometry/map.hpp"
#include "geometry/vector.hpp"
#include "global_type.hpp"
#include <cmath>

float Point::chebyshevDistanceTo(float y, float x) const
{
    float dy = std::abs(this->y - y);
    float dx = std::abs(this->x - x);
    return std::max(dy, dx);
}

float Point::chebyshevDistanceTo(const Point& target) const
{
    float dy = std::abs(this->y - target.y);
    float dx = std::abs(this->x - target.x);
    return std::max(dy, dx);
}

float Point::manhattanDistanceTo(float y, float x) const
{
    float dy = std::abs(this->y - y);
    float dx = std::abs(this->x - x);
    return dy + dx;
}

float Point::manhattanDistanceTo(const Point& target) const
{
    float dy = std::abs(this->y - target.y);
    float dx = std::abs(this->x - target.x);
    return dy + dx;
}

float Point::euclideanDistanceTo(float y, float x) const
{
    float dy = this->y - y;
    float dx = this->x - x;
    return std::sqrt(dy * dy + dx * dx);
}

float Point::euclideanDistanceTo(const Point& target) const
{
    float dy = this->y - target.y;
    float dx = this->x - target.x;
    return std::sqrt(dy * dy + dx * dx);
}


bool Point::stillOnMap(int y, int x)
{
    if (y < 0 || y >= Map::mapHeight)
        return false;
    if (x < 0 || x >= Map::mapWidth)
        return false;
    return true;
}

bool Point::stillOnMap(float y, float x)
{
    if (y < 0 || y >= Map::mapHeight)
        return false;
    if (x < 0 || x >= Map::mapWidth)
        return false;
    return true;
}

bool Point::stillOnMap()
{
    return stillOnMap(this->y, this->x);
}


bool Point::canMoveTo(int yIndex, int xIndex)
{
    return Map::mapGradient[yIndex][xIndex] <= 1000000 && Map::mapGradient[yIndex + 1][xIndex + 1] <= 1000000 &&
           Map::mapGradient[yIndex + 1][xIndex] <= 1000000 && Map::mapGradient[yIndex][xIndex + 1] <= 1000000;
}

bool Point::canMoveTo(float targetY, float targetX)
{
    int yIndex = static_cast<int>(targetY);
    int xIndex = static_cast<int>(targetX);
    return canMoveTo(yIndex, xIndex);
}

bool Point::canMoveTo(const Point& targetPoint)
{
    return canMoveTo(targetPoint.y, targetPoint.x);
}


int Point::gradientRisk(int y, int x)
{
    return Map::mapGradient[y][x];
}

int Point::gradientRisk(float y, float x)
{
    return Map::mapGradient[static_cast<int>(y)][static_cast<int>(x)];
}

int Point::gradientRisk() const
{
    return Map::mapGradient[static_cast<int>(this->y)][static_cast<int>(this->x)];
}


bool Point::isValidPosition(float y, float x)
{
    return stillOnMap(y, x) && canMoveTo(y, x);
}


bool Point::isValidPosition()
{
    return stillOnMap() && canMoveTo(*this);
}


float Point::moveSpeedRatio = 0.7f;
void Point::moveToLowerGradient()
{
    std::pair<float, float> vectorGradient = Vector::vectorGradient(this->y, this->x);
    this->y = vectorGradient.first * moveSpeedRatio + this->y * (1.0f - moveSpeedRatio);
    this->x = vectorGradient.second * moveSpeedRatio + this->x * (1.0f - moveSpeedRatio);
}

void Point::moveToLowerGradientTightly()
{
    std::pair<float, float> vectorGradient = Vector::vectorGradientTightly(this->y, this->x);
    this->y = vectorGradient.first * moveSpeedRatio + this->y * (1.0f - moveSpeedRatio);
    this->x = vectorGradient.second * moveSpeedRatio + this->x * (1.0f - moveSpeedRatio);
}