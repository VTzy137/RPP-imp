#include "function/init_population.hpp"
#include "geometry/map.hpp"
#include "geometry/path.hpp"
#include "global_type.hpp"
#include <cmath>
#include <set>

using namespace std;

typedef pair<double, pair<int, int>> pairDistance;
double gDistance[1000][1000] = {};
int visited[1000][1000] = {};
Path* astarRes;
Path* init_population::AStarSearch()
{
    set<pairDistance> aStar;
    int xStart = static_cast<int>(Map::startPoint.x), yStart = static_cast<int>(Map::startPoint.y);
    int xFinish = static_cast<int>(Map::finishPoint.x), yFinish = static_cast<int>(Map::finishPoint.y);
    aStar.insert(make_pair(0.0, make_pair(xStart, yStart)));
    while (aStar.empty() == false)
    {
        pairDistance newPoint = *aStar.begin();
        aStar.erase(aStar.begin());
        int x = newPoint.second.first, y = newPoint.second.second, past = x * 1000 + y;
        for (int i = 0; i < 8; ++i)
        {
            int x1 = x + GlobalType::neighbors[i].dx;
            int y1 = y + GlobalType::neighbors[i].dy;
            if (visited[y1][x1] == 0 && Point::isValidPosition(y1, x1))
            {
                visited[y1][x1] = past;
                gDistance[y1][x1] =
                    gDistance[y][x] + sqrt(abs(GlobalType::neighbors[i].dx) + abs(GlobalType::neighbors[i].dy));
                aStar.insert(make_pair(gDistance[y1][x1] + Vector::euclideanLength(y1, x1, yFinish, xFinish),
                                       make_pair(y1, x1)));
                if (x1 == xFinish && y1 == yFinish)
                    goto findSolution;
            }
            else if (Point::isValidPosition(y1, x1))
            {
                gDistance[y1][x1] =
                    min(gDistance[y1][x1], gDistance[y][x] + sqrt((double)(abs(GlobalType::neighbors[i].dx) +
                                                                           abs(GlobalType::neighbors[i].dy))));
            }
        }
    }
findSolution:
    Path* res = new Path(gDistance[yFinish][xFinish], 0, 0, nullptr);
    Point* p = new Point((double)xFinish, (double)yFinish, nullptr);
    int stop = 1000;
    while (--stop > 0)
    {
        int tmp = visited[xFinish][yFinish];
        xFinish = tmp / 1000;
        yFinish = tmp % 1000;
        p = new Point((double)xFinish, (double)yFinish, p);
        if (xFinish == xStart && yFinish == yStart)
            break;
    }

    res->begin = p;
    astarRes = res;
    return res;
}
