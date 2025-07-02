#include "geometry/map.hpp"
#include "global_type.hpp"
#include <cmath>
#include <iostream>
#include <queue>

void Map::markObstaclePoint(int y, int x)
{
    mapGradient[y][x] = 1000000;
    for (auto& neighbor : GlobalType::neighbors)
    {
        int ny = y + neighbor.dy;
        int nx = x + neighbor.dx;
        if (!Point::stillOnMap(ny, nx))
        {
            continue;
        }
        mapGradient[ny][nx] = 1000000;
    }
}

void Map::markObstaclePoint(float y, float x)
{
    Map::markObstaclePoint(static_cast<int>(y), static_cast<int>(x));
}

void Map::markObstacleLine(float y1, float x1, float y2, float x2)
{
    float length = Vector::euclideanLength(y1, x1, y2, x2);
    float sin = (y2 - y1) / length;
    float cos = (x2 - x1) / length;
    const float step = 1.0f;
    for (float positionStep = 0.0f; positionStep <= length; positionStep += step)
    {
        float y = y1 + positionStep * sin;
        float x = x1 + positionStep * cos;
        Map::markObstaclePoint(y, x);
    }
}

void Map::markObstacleLine(const Point& begin, const Point& end)
{
    Map::markObstacleLine(begin.y, begin.x, end.y, end.x);
}


void Map::markObstacleOutline(Point* beginPoint)
{
    Point* point = beginPoint;
    Point* nextPoint = point->nextPoint;
    while (nextPoint != nullptr)
    {
        Map::markObstacleLine(*point, *nextPoint);
        point = nextPoint;
        nextPoint = point->nextPoint;
    }
    Map::markObstacleLine(*point, *beginPoint);
}

void Map::markAllObstaclesOutline()
{
    for (auto obstacle : Map::obstacles)
    {
        Map::markObstacleOutline(obstacle);
    }

    mapGradient[static_cast<int>(startPoint.y)][static_cast<int>(startPoint.x)] = 0;
    mapGradient[static_cast<int>(finishPoint.y)][static_cast<int>(finishPoint.x)] = 0;
}

void Map::markMapBoundary()
{
    for (int y = 0; y < Map::mapHeight; y++)
    {
        mapGradient[y][0] = 2500000;
        mapGradient[y][Map::mapWidth - 1] = 2500000;
    }
    for (int x = 0; x < Map::mapWidth; x++)
    {
        mapGradient[0][x] = 2500000;
        mapGradient[Map::mapHeight - 1][x] = 2500000;
    }
}


void Map::markAllPointCanCome()
{
    std::queue<std::pair<int, int>> listPointCanCome;
    std::pair<int, int> start =
        std::make_pair(static_cast<int>(Map::startPoint.y), static_cast<int>(Map::startPoint.x));
    listPointCanCome.push(start);
    while (listPointCanCome.empty() == false)
    {
        int y = listPointCanCome.front().first;
        int x = listPointCanCome.front().second;
        listPointCanCome.pop();
        for (auto& neighbor : GlobalType::neighbors)
        {
            int ny = y + neighbor.dy;
            int nx = x + neighbor.dx;
            if (Point::stillOnMap(ny, nx) && Map::mapGradient[ny][nx] == 0)
            {
                listPointCanCome.push(std::make_pair(ny, nx));
                Map::mapGradient[ny][nx] = 1;
            }
        }
    }
}


void Map::markGradientByDistanceFromOutline()
{
    std::queue<std::pair<int, int>> pointQueue;
    for (int y = 0; y <= Map::mapHeight; y++)
    {
        for (int x = 0; x <= Map::mapWidth; x++)
        {
            if (Map::mapGradient[y][x] == 1000000)
            {
                pointQueue.push(std::make_pair(y, x));
                Map::mapGradient[y][x] = 1100100;
            }
        }
    }
    while (pointQueue.empty() == false)
    {
        int y = pointQueue.front().first, x = pointQueue.front().second;
        pointQueue.pop();
        for (auto& neighbor : GlobalType::neighbors)
        {
            int y1 = y + neighbor.dy;
            int x1 = x + neighbor.dx;
            if (!Point::stillOnMap(y1, x1))
            {
                continue;
            }

            if (Map::mapGradient[y1][x1] == 0)
            {
                Map::mapGradient[y1][x1] = Map::mapGradient[y][x] + 100000;
            }
            else if (Map::mapGradient[y1][x1] == 1)
            {
                Map::mapGradient[y1][x1] = std::max(Map::mapGradient[y][x] - 100000, 10);
            }
            else
            {
                continue;
            }
            pointQueue.push(std::make_pair(y1, x1));
        }
    }
}

void Map::smoothMapGradient()
{
    std::vector<int> lastRow(Map::mapWidth + 1, 0);
    for (int yAxis = 0; yAxis < Map::mapHeight; yAxis++)
    {
        for (int xAxis = 0; xAxis < Map::mapWidth; xAxis++)
        {
            int sumHeight = 0;
            for (auto& neighbor : GlobalType::neighbors)
            {
                int ny = yAxis + neighbor.dy;
                int nx = xAxis + neighbor.dx;
                sumHeight += Map::mapGradient[ny][nx];
            }
            Map::mapGradient[yAxis][xAxis] = (Map::mapGradient[yAxis][xAxis] * 2 + sumHeight) / 10;
        }
    }
}

void Map::markMapGradient()
{
    Map::markAllObstaclesOutline();
    std::cout << "markAllObstaclesOutline done" << std::endl;

    markMapBoundary();
    std::cout << "markMapBoundary done" << std::endl;

    Map::markAllPointCanCome();
    std::cout << "markAllPointCanCome done" << std::endl;

    Map::markGradientByDistanceFromOutline();
    std::cout << "markGradientByDistanceFromOutline done" << std::endl;

    Map::smoothMapGradient();
}
