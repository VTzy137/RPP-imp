#include "UI/opencv.hpp"
#include "function/init_population.hpp"
#include "geometry/map.hpp"
#include "geometry/path.hpp"
#include "global_type.hpp"
#include <cmath>
#include <iostream>
#include <set>

typedef std::pair<float, std::pair<int, int>> pairDistance;
float gDistance[1000][1000] = {};
int pastPoint[1000][1000] = {};
Path* init_population::AStarSearch()
{
    std::set<pairDistance> aStar;
    int xFinish = static_cast<int>(Map::finishPoint.x);
    int yFinish = static_cast<int>(Map::finishPoint.y);
    int xStart = static_cast<int>(Map::startPoint.x);
    int yStart = static_cast<int>(Map::startPoint.y);

    aStar.insert(std::make_pair(0.0f, std::make_pair(yStart, xStart)));

    while (aStar.empty() == false)
    {
        pairDistance newPoint = *aStar.begin();
        aStar.erase(aStar.begin());

        int y = newPoint.second.first;
        int x = newPoint.second.second;
        int pointIndex = y * 1000 + x;
        for (int i = 0; i < 8; ++i)
        {
            int y1 = y + GlobalType::neighbors[i].dy;
            int x1 = x + GlobalType::neighbors[i].dx;

            if (pastPoint[y1][x1] == 0 && Point::isValidPosition(y1, x1))
            {
                pastPoint[y1][x1] = pointIndex;
                gDistance[y1][x1] =
                    gDistance[y][x] +
                    sqrt(static_cast<float>(abs(GlobalType::neighbors[i].dy) + abs(GlobalType::neighbors[i].dx)));

                aStar.insert(std::make_pair(gDistance[y1][x1] + Vector::euclideanLength(y1, x1, yFinish, xFinish),
                                            std::make_pair(y1, x1)));
                if (y1 == yFinish && x1 == xFinish)
                {
                    goto findSolution;
                }
            }
            else if (Point::isValidPosition(y1, x1))
            {
                float distance =
                    gDistance[y][x] +
                    sqrt(static_cast<float>(abs(GlobalType::neighbors[i].dy) + abs(GlobalType::neighbors[i].dx)));

                gDistance[y1][x1] = std::min(gDistance[y1][x1], distance);
            }
        }
    }

findSolution:

    std::cout << "findSolution" << std::endl;
    Path* res = new Path(gDistance[yFinish][xFinish], 0, 0, nullptr);
    Point* point = new Point(static_cast<float>(yFinish), static_cast<float>(xFinish), nullptr);
    int stop = 1000;
    while (--stop > 0)
    {
        int pastPointIndex = pastPoint[yFinish][xFinish];
        yFinish = pastPointIndex / 1000;
        xFinish = pastPointIndex % 1000;
        point = new Point(static_cast<float>(yFinish), static_cast<float>(xFinish), point);
        if (yFinish == yStart && xFinish == xStart)
        {
            break;
        }
    }

    res->begin = point;
    return res;
}

void init_population::addAStarPopulation(int numIndividual)
{
    for (int individualIndex = 0; individualIndex < numIndividual; individualIndex++)
    {
        Path::population.push_back(init_population::AStarSearch());
        OpenCV::drawPath(Path::population.back(), cv::Scalar(200, 200, 0));
    }
}