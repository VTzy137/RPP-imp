#include "geometry/point.hpp"
#include "geometry/map.hpp"
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
    return Map::mapGradient[yIndex][xIndex] <= 1000000 &&
           Map::mapGradient[yIndex + 1][xIndex + 1] <= 1000000 &&
           Map::mapGradient[yIndex + 1][xIndex] <= 1000000 &&
           Map::mapGradient[yIndex][xIndex + 1] <= 1000000;
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


bool Point::isValidPosition(float y, float x)
{
    return stillOnMap(y, x) && canMoveTo(y, x);
}


bool Point::isValidPosition()
{
    return stillOnMap() && canMoveTo(*this);
}


std::pair<float, float> gradientPoint(float x, float y)
{
    int x1 = (int)x, y1 = (int)y, cur = Map::mapGradient[x1][y1], ne = -1;
    if (cur < 800000)
        return std::make_pair(x, y);
    for (int i = 0; i < 8; ++i)
    {
        if (Map::mapGradient[x1 + Map::nearPoint[i][0] * 2][y1 + Map::nearPoint[i][1] * 2] < cur)
        {
            cur = Map::mapGradient[x1 + Map::nearPoint[i][0] * 2]
                                  [y1 + vtzy_types::nearPoint[i][1] * 2];
            ne = i;
        }
    }
    if (ne != -1)
    {
        x += vtzy_types::nearPoint[ne][0] * 2;
        y += vtzy_types::nearPoint[ne][1] * 2;
    }
    return std::make_pair(x, y);
}

std::pair<float, float> gradientPointTightly(float x, float y)
{
    int x1 = (int)x, y1 = (int)y, cur = vtzy_types::mapGradient[x1][y1], ne = -1;
    // if(cur < 200000) return make_pair(0, 0);
    for (int i = 0; i < 8; ++i)
    {
        if (vtzy_types::mapGradient[x1 + vtzy_types::nearPoint[i][0] * 2]
                                   [y1 + vtzy_types::nearPoint[i][1] * 2] < cur)
        {
            cur = vtzy_types::mapGradient[x1 + vtzy_types::nearPoint[i][0] * 2]
                                         [y1 + vtzy_types::nearPoint[i][1] * 2];
            ne = i;
        }
    }
    if (ne == -1)
        return std::make_pair(0, 0);
    return std::make_pair(vtzy_types::nearPoint[ne][0], vtzy_types::nearPoint[ne][1]);
}