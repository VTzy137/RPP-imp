#include <bits/stdc++.h>
using namespace std;
struct point
{
    double x, y;
    point* next;
    point() : x(0), y(0), next(nullptr){};
    point(double x1, double y1, point* next1) : x(x1), y(y1), next(next1)
    {
    }
};

struct path
{
    double distance, angle, safety;
    point* begin;
    path() : distance(1000000), angle(1000000), begin(nullptr)
    {
    }
    path(point* beginPoint) : distance(1000000), angle(1000000), begin(beginPoint)
    {
    }
    path(double distance1, double angle1, point* beginPoint) : distance(distance1), angle(angle1), begin(beginPoint)
    {
    }
};

path* paths[50];
point *start, *finish, *obstacles[1000], *population[100];
int mapHeight, mapWidth, numObstacle, numPath = 0;

bool checkValidLine(point* m, point* n, point* p, point* q)
{
    double b = n->x - m->x;
    double a = m->y - n->y;
    double c = a * m->x + b * m->y;

    double d = (p->x * a + p->y * b - c);
    double e = (q->x * a + q->y * b - c);
    return d * e <= 0;
}

double distancePointToLine(point* prePoint, point* midPoint, point* nextPoint)
{
    double a = sqrt(pow(midPoint->x - prePoint->x, 2) + pow(midPoint->y - prePoint->y, 2));
    double b = sqrt(pow(nextPoint->x - prePoint->x, 2) + pow(nextPoint->y - prePoint->y, 2));
    double c = sqrt(pow(midPoint->x - nextPoint->x, 2) + pow(midPoint->y - nextPoint->y, 2));

    double q = (a + b + c) / 2;
    double s = sqrt(q * (q - a) * (q - b) * (q - c));
    double h = s * 2.0 / c;

    if (abs(sqrt(a * a - h * h) + sqrt(b * b - h * h) - c) > 0.01)
    {
        return min(a, b);
    }
    return h;
}

double distanceToObstacle(point* p, point* p1)
{
    double tmp = 1e9;
    for (int i = 0; i < numObstacle; ++i)
    {
        point* obstacle = obstacles[i];
        while (obstacle->next != nullptr)
        {
            tmp = min(tmp, distancePointToLine(p, obstacle, obstacle->next));
            tmp = min(tmp, distancePointToLine(p1, obstacle, obstacle->next));
            tmp = min(tmp, distancePointToLine(obstacle, p, p1));
            tmp = min(tmp, distancePointToLine(obstacle->next, p, p1));
            obstacle = obstacle->next;
        }
        double tmp = 1e9;
        tmp = min(tmp, distancePointToLine(p, obstacle, obstacles[i]));
        tmp = min(tmp, distancePointToLine(p1, obstacle, obstacles[i]));
        tmp = min(tmp, distancePointToLine(obstacle, p, p1));
        tmp = min(tmp, distancePointToLine(obstacles[i], p, p1));
    }
    return tmp;
}

void pathFunc(path* path1)
{
    point* currentPoint = path1->begin;
    point* nextPoint = currentPoint->next;
    double y = nextPoint->y - currentPoint->y;
    double x = nextPoint->x - currentPoint->x;
    double length = sqrt(x * x + y * y);
    double distance = length, angle = 0;
    double pastAngle = acos(x / length) * (y >= 0 ? 1 : -1);
    double currAngle, safety = 0;
    int index = 0;
    while (currentPoint->next != nullptr)
    {
        nextPoint = currentPoint->next;
        y = nextPoint->y - currentPoint->y;
        x = nextPoint->x - currentPoint->x;
        length = sqrt(x * x + y * y);
        distance += length;
        double safe = 100.0 / pow(distanceToObstacle(currentPoint, nextPoint), 2);
        safety += safe;
        currAngle = 100 * acos(x / length) * (y >= 0 ? 1 : -1);
        if (index++ != 0)
        {
            angle += abs(currAngle - pastAngle);
        }
        pastAngle = currAngle;
        currentPoint = nextPoint;
    }
    path1->safety = safety / index;
    path1->distance = distance;
    path1->angle = max(1.0, angle) / sqrt(index);
}

double limitHV = 300;
bool checkValidPath(path* currentPath)
{
    point* currentPoint = currentPath->begin;
    if (abs(currentPoint->x - start->x) > 0.1 || abs(currentPoint->y - start->y) > 0.1)
    {
        currentPoint = new point(start->x, start->y, currentPoint);
    }
    while (true)
    {
        if (currentPoint->next == nullptr)
        {
            if (abs(currentPoint->x - finish->x) < 0.1 && abs(currentPoint->y - finish->y) < 0.1)
                break;
            currentPoint->next = new point(finish->x, finish->y, nullptr);
        }
        for (int i = 0; i < numObstacle; ++i)
        {
            point* obstacle = obstacles[i];
            while (obstacle->next != nullptr)
            {
                if (checkValidLine(currentPoint, currentPoint->next, obstacle, obstacle->next) &&
                    checkValidLine(obstacle, obstacle->next, currentPoint, currentPoint->next))
                {
                    return false;
                }
                obstacle = obstacle->next;
            }
            if (checkValidLine(currentPoint, currentPoint->next, obstacle, obstacles[i]) &&
                checkValidLine(obstacle, obstacles[i], currentPoint, currentPoint->next))
            {
                return false;
            }
        }
        currentPoint = currentPoint->next;
    }
    pathFunc(currentPath);
    if (currentPath->safety > limitHV || currentPath->angle > limitHV)
        return false;
    return true;
}

int main()
{
    int numIO = 2;
    string assetsPath = "../../assets/";
    ifstream file1(assetsPath + "output/out" + to_string(numIO) + ".txt");
    // ifstream file1(assetsPath + "HaiNSGAII/nsgaii_test" + to_string(numIO) + ".txt");
    // ifstream file1(assetsPath + "HaiPSOES/psoes_test" + to_string(numIO) + ".txt");
    // ifstream file1(assetsPath + "HaiPSO/pso_test" + to_string(numIO) + ".txt");
    ifstream file2(assetsPath + "input/map" + to_string(numIO) + ".txt");

    start = new point();
    finish = new point();

    cout << "map " << numIO << endl;
    file2 >> mapHeight >> mapWidth;
    cout << "mapHeight: " << mapHeight << " mapWidth: " << mapWidth << endl;
    file2 >> start->x >> start->y >> finish->x >> finish->y;
    file2 >> numObstacle;

    string s;
    for (int obstacleIndex = 0; obstacleIndex < numObstacle; ++obstacleIndex)
    {
        file2.ignore();
        getline(file2, s);
        stringstream ss(s);
        double x1, y1;

        while (ss >> x1)
        {
            ss >> y1;
            obstacles[obstacleIndex] = new point(x1, y1, obstacles[obstacleIndex]);
        }
    }
    for (int obstacleIndex = 0; obstacleIndex < numObstacle; ++obstacleIndex)
    {
        cout << "--- obs " << obstacleIndex << endl;
        point *p = obstacles[obstacleIndex], *q = p->next;
        while (q != NULL)
        {
            cout << p->x << " " << p->y << " " << q->x << " " << q->y << endl;
            p = p->next;
            q = q->next;
        }
    }

    file2.close();
    double x = 1, y;
    file1 >> x;
    int loop = 1000;
    while (loop-- > 0)
    {
        if (abs(x + 2.0) < 0.01 || abs(x + 1.0) < 0.01)
        {
            path* tmp = new path();
            point* currentPoint = population[numPath];
            point* nextPoint = currentPoint->next;
            point* nextNextPoint = nextPoint->next;
            currentPoint->next = nullptr;
            while (nextNextPoint != nullptr)
            {
                nextPoint->next = currentPoint;
                currentPoint = nextPoint;
                nextPoint = nextNextPoint;
                nextNextPoint = nextNextPoint->next;
            }
            nextPoint->next = currentPoint;
            population[numPath] = nextPoint;
            tmp->begin = population[numPath];
            if (checkValidPath(tmp))
            {
                // pathFunc(tmp);
                paths[numPath] = tmp;
                ++numPath;
            }
            else
            {
                population[numPath] = nullptr;
            }
            if (abs(x + 2.0) < 0.01)
            {
                break;
            }
            file1 >> x;
            continue;
        }
        file1 >> y;
        // cout << x << " " << y << endl;
        population[numPath] = new point(x, y, population[numPath]);
        file1 >> x;
    }
    file1.close();
    // cout << numPath << endl;
    sort(paths, paths + numPath, [](path* path1, path* path2) -> bool { return path1->distance < path2->distance; });

    map<double, double> safetyValueByAngle;
    safetyValueByAngle[0] = limitHV;
    safetyValueByAngle[limitHV] = 0;

    double past = 0;
    double hyperVolume = 0;
    double sqrPareto = 0;
    for (int individual = 0; individual < numPath; ++individual)
    {
        safetyValueByAngle[paths[individual]->angle] = paths[individual]->safety;
        cout << "path " << individual << ": " << paths[individual]->distance << " " << paths[individual]->angle << " "
             << paths[individual]->safety << endl;

        hyperVolume += sqrPareto * (paths[individual]->distance - past);
        double currentAngle = 0, currentSafety = limitHV;
        sqrPareto = 0;
        for (auto& pairAngleSafety : safetyValueByAngle)
        {
            if (pairAngleSafety.second > currentSafety)
                continue;
            sqrPareto += (limitHV - currentSafety) * (pairAngleSafety.first - currentAngle);
            currentAngle = pairAngleSafety.first;
            currentSafety = pairAngleSafety.second;
        }
        past = paths[individual]->distance;
    }
    hyperVolume += sqrPareto * (limitHV - past);

    cout << endl << "Hyper volume: " << hyperVolume << endl;

    // int hv = (int)hyperVolume;
    // cout << endl << "Hyper volume: " << hv << endl;
}