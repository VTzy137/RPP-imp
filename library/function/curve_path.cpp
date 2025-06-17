#include "geometry/map.hpp"
#include <cmath>
#include <function/init_population.hpp>
#include <iostream>
#include <random>


namespace init_population
{
bool initRandPath(Point* beginPoint, Point* endPoint)
{
    float yBegin = beginPoint->y, xBegin = beginPoint->x;
    float distance = Vector::euclideanLength(*beginPoint, *endPoint);
    float sin = (endPoint->y - yBegin) / distance;
    float cos = (endPoint->x - xBegin) / distance;

    int rangePathCurve = std::rand() % rangeCurveLimit - normalize;

    for (float lineDistance = 0; lineDistance < distance; lineDistance += 20)
    {
        float lineIndex = (lineDistance - (distance / 2)) / distance;
        float curveRadius = rangePathCurve * (1 - lineIndex * lineIndex);
        float y = std::max(minCurve, yBegin + sin * lineDistance + cos * curveRadius);
        float x = std::max(minCurve, xBegin + cos * lineDistance - sin * curveRadius);
        beginPoint->nextPoint = new Point(y, x, nullptr);
        beginPoint = beginPoint->nextPoint;
    }
    beginPoint->nextPoint = endPoint;
    return (rangePathCurve < 0);
}

Path* curvePathInit()
{

    Point* beginPath = new Point(Map::startPoint.y, Map::startPoint.x, nullptr);
    Point* endPath = new Point(Map::finishPoint.y, Map::finishPoint.x, nullptr);

    // PSO::normalDirect[i] = init_population::initRandPath(tmp, tmp1);

    Path* curvePath = new Path(beginPath);
    // OpenCV::drawPath(Path::population[i], cv::Scalar(200, 200, 0));
    return curvePath;
}

} // namespace init_population
