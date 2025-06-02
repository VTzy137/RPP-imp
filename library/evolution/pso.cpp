#include "evolution/pso.hpp"
#include "geometry/path.hpp"
#include "global_type.hpp"
#include <cmath>
#include <iostream>

// Define static members
Path* PSO::currPath = nullptr;
Path* PSO::gPath = nullptr;
std::vector<Path*> PSO::pPath;

void PSO::updateVelocity(int i)
{
    int j = 1;
    Point *p = Path::population[i]->begin->nextPoint, *pp = PSO::pPath[i]->begin->nextPoint;
    while (p != nullptr && pp != nullptr)
    {
        PSO::velocity[i][j][0] = PSO::w0PSO * PSO::velocity[i][j][0] + PSO::w1PSO * (pp->x - p->x);
        PSO::velocity[i][j][1] = PSO::w0PSO * PSO::velocity[i][j][1] + PSO::w1PSO * (pp->y - p->y);
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


void PSO::PSOmigrate()
{
    std::cout << "PSOmigrate" << std::endl;
    for (int i = 0; i < Path::population.size(); i++)
    {
        std::cout << "p->y: " << Path::population[i]->begin << std::endl;
        Point *p1 = Path::population[i]->begin, *p = p1->nextPoint;
        std::pair<float, float> q;
        std::cout << "p->y: " << p->y << " p->x: " << p->x << std::endl;
        while (p != nullptr && p->nextPoint != nullptr)
        {
            int y = static_cast<int>(p->y), x = static_cast<int>(p->x);
            p->y = p->y * 0.8f + (p->nextPoint->y + p1->y) * 0.1f;
            p->x = p->x * 0.8f + (p->nextPoint->x + p1->x) * 0.1f;
            q = Vector::vectorGradient(p->y, p->x);
            p->y = p->y * 0.7 + q.first * 0.3;
            p->x = p->x * 0.7 + q.second * 0.3;
            if (!Point::stillOnMap(p->y, p->x))
            {
                PSO::normalDirect[i] = !PSO::normalDirect[i];
            };
            if (!Point::isValidPosition(p->y, p->x))
            {
                if (PSO::normalDirect[i])
                    Vector::offsetMiddleToReduceBend(*p1, *p, *p->nextPoint);
                else
                    Vector::offsetMiddleToReduceBend(*p->nextPoint, *p, *p1);
            }

            if (p->euclideanDistanceTo(*p1) > 7)
            {
                p1->nextPoint = new Point((p->y + p1->y) / 2, (p->x + p1->x) / 2, p1->nextPoint);
                p1 = p1->nextPoint;
            }
            else if (p->euclideanDistanceTo(*p1) < 3 && std::fabs(Vector::turnAngle(*p1, *p, *p->nextPoint)) < 0.2)
            {
                p1->nextPoint = p->nextPoint;
                p = p1->nextPoint;
            }
            else
            {
                p = p->nextPoint;
                p1 = p1->nextPoint;
            }
        }
    }
    std::cout << "PSOmigrate done" << std::endl;
}
