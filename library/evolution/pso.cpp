#include "evolution/pso.hpp"
#include "geometry/path.hpp"
#include "global_type.hpp"
#include <cmath>
#include <iostream>

Path* PSO::currPath = nullptr;
Path* PSO::gPath = nullptr;
std::vector<Path*> PSO::pPath;

void PSO::updateVelocity(int invidual)
{
    int pointIndex = 1;
    Point *p = Path::population[invidual]->begin->nextPoint, *pp = PSO::pPath[invidual]->begin->nextPoint;
    while (p != nullptr && pp != nullptr)
    {
        PSO::velocity[invidual][pointIndex][0] =
            PSO::w0PSO * PSO::velocity[invidual][pointIndex][0] + PSO::w1PSO * (pp->x - p->x);
        PSO::velocity[invidual][pointIndex][1] =
            PSO::w0PSO * PSO::velocity[invidual][pointIndex][1] + PSO::w1PSO * (pp->y - p->y);
        ++pointIndex;
        p = p->nextPoint;
        pp = pp->nextPoint;
    }
}

void PSO::moveMent()
{
    for (int individual = 0; individual < Path::population.size(); individual++)
    {
        updateVelocity(individual);
        std::cout << "updateVelocity" << std::endl;
        Point* p = Path::population[individual]->begin->nextPoint;
        int pathLen = Path::population[individual]->numPoints();
        for (int j = 1; j < pathLen - 1; ++j)
        {
            p->x += PSO::velocity[individual][j][0] * PSO::wVPSO;
            p->y += PSO::velocity[individual][j][1] * PSO::wVPSO;
            p = p->nextPoint;
        }
    }
}

void PSO::updateBestPath()
{
    for (int individual = 0; individual < Path::population.size(); individual++)
    {
        if (Path::betterPath(*Path::population[individual], *PSO::pPath[individual]))
            PSO::pPath[individual]->changePathTo(*Path::population[individual]);
        if (Path::betterPath(*Path::population[individual], *PSO::gPath))
        {
            PSO::gPath->changePathTo(*Path::population[individual]);
        }
    }
}

void PSO::moveFollowGradient(Point* begin, Point* middle, Point* end)
{
    int y = static_cast<int>(middle->y), x = static_cast<int>(middle->x);
    middle->y = middle->y * 0.8f + (end->y + begin->y) * 0.1f;
    middle->x = middle->x * 0.8f + (end->x + begin->x) * 0.1f;
    std::pair<float, float> q = Vector::vectorGradient(middle->y, middle->x);
    middle->y = middle->y * 0.7 + q.first * 0.3;
    middle->x = middle->x * 0.7 + q.second * 0.3;
}

void PSO::planePath(Point* begin, Point* middle, int position)
{
    if (!Point::isValidPosition(middle->y, middle->x))
    {
        if (PSO::normalDirect[position] > 0)
        {
            Vector::offsetMiddleToReduceBend(*begin, *middle, *middle->nextPoint);
        }
        else
        {
            Vector::offsetMiddleToReduceBend(*middle->nextPoint, *middle, *begin);
        }
    }
}

void PSO::PSOmigrate()
{
    for (int individual = 0; individual < Path::population.size(); individual++)
    {
        Point *pointPast = Path::population[individual]->begin, *point_i = pointPast->nextPoint;
        std::pair<float, float> q;
        bool changeDirection = false;
        while (point_i != nullptr && point_i->nextPoint != nullptr)
        {

            moveFollowGradient(pointPast, point_i, point_i->nextPoint);

            if (Point::reachBoundary(static_cast<int>(point_i->y), static_cast<int>(point_i->x)))
            {
                changeDirection = true;
            }

            planePath(pointPast, point_i, individual);

            if (point_i->euclideanDistanceTo(*pointPast) > 7)
            {
                pointPast->nextPoint =
                    new Point((point_i->y + pointPast->y) / 2, (point_i->x + pointPast->x) / 2, pointPast->nextPoint);
                pointPast = pointPast->nextPoint;
            }
            else if (point_i->euclideanDistanceTo(*pointPast) < 3 &&
                     std::fabs(Vector::turnAngle(*pointPast, *point_i, *point_i->nextPoint)) < 0.08)
            {
                pointPast->nextPoint = point_i->nextPoint;
                point_i = pointPast->nextPoint;
            }
            else
            {
                point_i = point_i->nextPoint;
                pointPast = pointPast->nextPoint;
            }
        }
        if (changeDirection)
        {
            // PSO::normalDirect[individual] = !PSO::normalDirect[individual];
            std::cout << "normalDirect: " << PSO::normalDirect[individual] << std::endl;
            if (abs(PSO::normalDirect[individual]) == 1)
            {
                PSO::normalDirect[individual] = - PSO::normalDirect[individual] * 10;
            }
            else if (PSO::normalDirect[individual] > 0)
            {
                --PSO::normalDirect[individual];
            }
            else
            {
                ++PSO::normalDirect[individual];
            }
            std::cout << "normalDirect: " << PSO::normalDirect[individual] << std::endl;
        }
    }
    // std::cout << "PSOmigrate done" << std::endl;
}
