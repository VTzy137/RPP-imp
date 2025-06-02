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
        mapGradient[ny][nx] = 1000000;
    }
}

void Map::markObstaclePoint(float y, float x)
{
    markObstaclePoint(static_cast<int>(y), static_cast<int>(x));
}

void Map::markObstacleLine(float y1, float x1, float y2, float x2)
{
    float length = Vector::euclideanLength(y1, x1, y2, x2);
    float sin = (y2 - y1) / length;
    float cos = (x2 - x1) / length;
    const float step = 1.0f;
    for (float t = 0.0f; t <= length; t += step)
    {
        float y = y1 + t * sin;
        float x = x1 + t * cos;
        markObstaclePoint(y, x);
    }
}

void Map::markObstacleLine(const Point& begin, const Point& end)
{
    markObstacleLine(begin.y, begin.x, end.y, end.x);
}


void Map::markObstacleOutline(Point* beginPoint)
{
    Point* point = beginPoint;
    Point* nextPoint = point->nextPoint;
    while (nextPoint != nullptr)
    {
        markObstacleLine(*point, *nextPoint);
        point = nextPoint;
        nextPoint = point->nextPoint;
    }
    markObstacleLine(*point, *beginPoint);
}

void Map::markAllObstaclesOutline()
{
    for (auto obstacle : Map::obstacles)
    {
        markObstacleOutline(obstacle);
    }

    mapGradient[static_cast<int>(startPoint.y)][static_cast<int>(startPoint.x)] = 0;
    mapGradient[static_cast<int>(finishPoint.y)][static_cast<int>(finishPoint.x)] = 0;
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
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i <= Map::mapHeight; i++)
    {
        for (int j = 0; j <= Map::mapWidth; j++)
        {
            if (Map::mapGradient[i][j] == 1000000)
            {
                q.push(std::make_pair(i, j));
                Map::mapGradient[i][j] = 1100100;
            }
        }
    }
    while (q.empty() == false)
    {
        int i = q.front().first, j = q.front().second;
        q.pop();
        for (auto& neighbor : GlobalType::neighbors)
        {
            int i1 = i + neighbor.dy, j1 = j + neighbor.dx, t = 1;
            if (!Point::stillOnMap(i1, j1))
                continue;
            if (Map::mapGradient[i1][j1] == 0)
            {
                Map::mapGradient[i1][j1] = Map::mapGradient[i][j] + 100000;
            }
            else if (Map::mapGradient[i1][j1] == 1)
                Map::mapGradient[i1][j1] = std::max(Map::mapGradient[i][j] - 100000, 10);
            else
                t = 0;
            if (t)
                q.push(std::make_pair(i1, j1));
        }
    }
}

void Map::markMapGradient()
{
    markAllObstaclesOutline();

    markAllPointCanCome();
    std::cout << "markAllPointCanCome" << std::endl;
    // for (int i = 0; i <= Map::mapHeight; i++)
    // {
    //     for (int j = 0; j <= Map::mapWidth; j++)
    //     {
    //         if (abs(i - Map::startPoint.x) <= 3 && abs(j - Map::startPoint.y) <= 3)
    //             Input::logBoth("2");
    //         else if (abs(i - Map::finishPoint.x) <= 3 && abs(j - Map::finishPoint.y) <= 3)
    //             Input::logBoth("3");
    //         else if (Map::mapGradient[i][j] == 1000000)
    //             Input::logBoth("1");
    //         else
    //             Input::logBoth("0");
    //     }
    //     Input::logBothLine("");
    // }

    markGradientByDistanceFromOutline();
    std::cout << "markGradientByDistanceFromOutline" << std::endl;
    // for (int i = 0; i <= Map::mapHeight; i++)
    // {
    //     for (int j = 0; j <= Map::mapWidth; j++)
    //     {
    //         if (Map::mapGradient[i][j] > 1000000)
    //             Input::logBoth("1");
    //         else
    //             Input::logBoth("0");
    //     }
    //     Input::logBothLine("");
    // }
}

void Map::smoothMapGradient()
{
    std::vector<int> lastRow(Map::mapWidth + 1, 0);
    for (int i = 0; i < Map::mapHeight; i++)
    {
        for (int j = 0; j < Map::mapWidth; j++)
        {
            int sum = 0;
            for (auto& neighbor : GlobalType::neighbors)
            {
                int ny = i + neighbor.dy;
                int nx = j + neighbor.dx;
                sum += Map::mapGradient[ny][nx];
            }
            lastRow[j] = Map::mapGradient[i][j];
            Map::mapGradient[i][j] = (Map::mapGradient[i][j] * 2 + sum) / 10;
        }
    }
    for (int j = 0; j < Map::mapWidth; j++)
    {
        Map::mapGradient[Map::mapHeight][j] = lastRow[j];
    }
}