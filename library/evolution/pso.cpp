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
    int j = 1;
    Point *p = Path::population[invidual]->begin->nextPoint, *pp = PSO::pPath[invidual]->begin->nextPoint;
    while (p != nullptr && pp != nullptr)
    {
        PSO::velocity[invidual][j][0] = PSO::w0PSO * PSO::velocity[invidual][j][0] + PSO::w1PSO * (pp->x - p->x);
        PSO::velocity[invidual][j][1] = PSO::w0PSO * PSO::velocity[invidual][j][1] + PSO::w1PSO * (pp->y - p->y);
        ++j;
        p = p->nextPoint;
        pp = pp->nextPoint;
    }
}

void PSO::moveMent()
{
    for (int i = 0; i < Path::population.size(); i++)
    {
        updateVelocity(i);
        std::cout << "updateVelocity" << std::endl;
        Point* p = Path::population[i]->begin->nextPoint;
        int pathLen = Path::population[i]->numPoints();
        for (int j = 1; j < pathLen - 1; ++j)
        {
            p->x += velocity[i][j][0] * PSO::wVPSO;
            p->y += velocity[i][j][1] * PSO::wVPSO;
            p = p->nextPoint;
        }
    }
}

void PSO::updateBestPath()
{
    for (int i = 0; i < Path::population.size(); i++)
    {
        // if (Path::betterPath(Path::population[i], PSO::pPath[i]))
        //     PSO::pPath[i].changePathTo(Path::population[i]);
        if (Path::betterPath(*Path::population[i], *PSO::gPath))
        {
            PSO::gPath->changePathTo(*Path::population[i]);
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
    if (Point::reachBoundary(static_cast<int>(middle->y), static_cast<int>(middle->x)))
    {
        PSO::normalDirect[position] = !PSO::normalDirect[position];
    };
    if (!Point::isValidPosition(middle->y, middle->x))
    {
        if (PSO::normalDirect[position])
            Vector::offsetMiddleToReduceBend(*begin, *middle, *middle->nextPoint);
        else
            Vector::offsetMiddleToReduceBend(*middle->nextPoint, *middle, *begin);
    }
}

void PSO::PSOmigrate()
{
    for (int i = 0; i < Path::population.size(); i++)
    {
        Point *pointPast = Path::population[i]->begin, *point_i = pointPast->nextPoint;
        std::pair<float, float> q;
        while (point_i != nullptr && point_i->nextPoint != nullptr)
        {

            moveFollowGradient(pointPast, point_i, point_i->nextPoint);

            planePath(pointPast, point_i, i);

            if (point_i->euclideanDistanceTo(*pointPast) > 7)
            {
                pointPast->nextPoint =
                    new Point((point_i->y + pointPast->y) / 2, (point_i->x + pointPast->x) / 2, pointPast->nextPoint);
                pointPast = pointPast->nextPoint;
            }
            else if (point_i->euclideanDistanceTo(*pointPast) < 3 &&
                     std::fabs(Vector::turnAngle(*pointPast, *point_i, *point_i->nextPoint)) < 0.2)
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
    }
    // std::cout << "PSOmigrate done" << std::endl;
}
