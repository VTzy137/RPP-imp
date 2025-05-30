#include "evolution/pso.hpp"
#include "geometry/path.hpp"
#include "global_type.hpp"

// Define static members
Path* PSO::currPath = nullptr;
Path* PSO::gPath = nullptr;
std::vector<Path> PSO::pPath;
std::vector<Path> PSO::population;

void PSO::updateV(int i)
{
    int j = 1;
    Point *p = population[i].begin->nextPoint, *pp = pPath[i].begin->nextPoint;
    while (p->nextPoint != nullptr)
    {
        v[i][j][0] = PSO::w0PSO * v[i][j][0] + PSO::w1PSO * (pp->x - p->x);
        v[i][j][1] = PSO::w0PSO * v[i][j][1] + PSO::w1PSO * (pp->y - p->y);
        ++j;
        p = p->nextPoint;
        pp = pp->nextPoint;
    }
}

void PSO::moveMent()
{
    for (int i = 0; i < Path::population.size(); i++)
    {
        updateV(i);
        Point* p = population[i].begin->nextPoint;
        int pathLen = population[i].numPoints();
        for (int j = 1; j < pathLen - 1; ++j)
        {
            p->x += v[i][j][0] * PSO::wVPSO;
            p->y += v[i][j][1] * PSO::wVPSO;
            p = p->nextPoint;
        }
    }
}

void PSO::updateBestPath()
{
    for (int i = 0; i < Path::population.size(); i++)
    {
        if (Path::betterPath(Path::population[i], PSO::pPath[i]))
            PSO::pPath[i] = Path(Path::population[i]);
        if (Path::betterPath(Path::population[i], *PSO::gPath))
        {
            PSO::gPath = &Path::population[i];
        }
    }
}


void PSO::PSOmigrate()
{
    for (int i = 0; i < Path::population.size(); i++)
    {
        Point *p1 = Path::population[i].begin, *p = p1->nextPoint;
        std::pair<float, float> q;
        while (p != nullptr && p->nextPoint != nullptr)
        {
            int x = (int)p->x, y = (int)p->y;
            p->x = p->x * 0.8 + (p->nextPoint->x + p1->x) * 10 / 100;
            p->y = p->y * 0.8 + (p->nextPoint->y + p1->y) * 10 / 100;
            q = Vector::vectorGradient(p->y, p->x);
            p->x = p->x * 0.7 + q.first * 0.3;
            p->y = p->y * 0.7 + q.second * 0.3;
            if (!Point::isValidPosition(p->y, p->x))
            {
                PSO::normalDirect[i] = !PSO::normalDirect[i];
            };
            if (!Point::isValidPosition(p->y, p->x))
                if (PSO::normalDirect[i])
                    Vector::offsetMiddleToReduceBend(*p1, *p, *p->nextPoint);
                else
                    Vector::offsetMiddleToReduceBend(*p->nextPoint, *p, *p1);

            if (p->euclideanDistanceTo(*p1) > 7)
            {
                p1->nextPoint = new Point((p->x + p1->x) / 2, (p->y + p1->y) / 2);
                p1 = p1->nextPoint;
            }
            else if (p->euclideanDistanceTo(*p1) < 3 && Vector::turnAngle(*p1, *p, *p->nextPoint) < 0.2)
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
}
