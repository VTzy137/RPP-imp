#include "UI/opencv.hpp"
#include "evolution/pso.hpp"
#include "function/init_population.hpp"
#include "geometry/map.hpp"
#include <cmath>
#include <iostream>
#include <random>


bool init_population::initRandPath(Point* beginPoint, Point* endPoint)
{
    float yBegin = beginPoint->y, xBegin = beginPoint->x;
    float distance = Vector::euclideanLength(*beginPoint, *endPoint);
    float sin = (endPoint->y - yBegin) / distance;
    float cos = (endPoint->x - xBegin) / distance;

    int rangePathCurve = std::rand() % init_population::rangeCurveLimit - init_population::normalize;

    for (float lineDistance = 0; lineDistance < distance; lineDistance += 20)
    {
        float lineIndex = (lineDistance - (distance / 2)) / distance;
        float curveRadius = rangePathCurve * (1 - lineIndex * lineIndex);
        float y = std::max(init_population::minCurve, yBegin + sin * lineDistance + cos * curveRadius);
        float x = std::max(init_population::minCurve, xBegin + cos * lineDistance - sin * curveRadius);
        beginPoint->nextPoint = new Point(y, x, nullptr);
        beginPoint = beginPoint->nextPoint;
    }
    beginPoint->nextPoint = endPoint;
    return (rangePathCurve < 0);
}

std::pair<Path*, bool> init_population::curvePathInit()
{
    Point* startPoint = new Point(Map::startPoint.y, Map::startPoint.x, nullptr);
    Point* finishPoint = new Point(Map::finishPoint.y, Map::finishPoint.x, nullptr);

    Path* curvePath = new Path(startPoint);
    bool normalDirect = init_population::initRandPath(startPoint, finishPoint);

    return std::make_pair(curvePath, normalDirect);
}

void init_population::addCurvePopulation(int numIndividual)
{
    for (int individualIndex = 0; individualIndex < numIndividual; individualIndex++)
    {
        std::pair<Path*, bool> curvePath = init_population::curvePathInit();
        Path::population.push_back(curvePath.first);
        PSO::normalDirect[individualIndex] = curvePath.second;

        OpenCV::drawPath(Path::population[individualIndex], cv::Scalar(200, 200, 0));
    }
}
