#include "geometry/path.hpp"
#include "geometry/map.hpp"
#include "geometry/point.hpp"
#include "global_type.hpp"
#include <cmath>

bool Path::isBetterThan(const Path& other, float weight = 2.5f) const
{
    float diffAngle = this->angle - other.angle;
    float diffDistance = this->distance - other.distance;
    return diffAngle + weight * diffDistance < 0;
}

bool Path::betterPath(const Path& reference, const Path& other, float weight = 2.5f)
{
    float diffAngle = reference.angle - other.angle;
    float diffDistance = reference.distance - other.distance;
    return diffAngle + weight * diffDistance > 0;
}

int Path::numTargetBetterThan(const Path& other, float weight) const
{
    int numBetter = 0;
    if (this->angle < other.angle)
        numBetter++;
    if (this->distance < other.distance)
        numBetter++;
    if (this->risk < other.risk)
        numBetter++;
    return numBetter;
}

int Path::numTargetBetterPath(const Path& reference, const Path& other, float weight)
{
    float diffAngle = reference.angle - other.angle;
    float diffDistance = reference.distance - other.distance;
}

int compareSamePath(Path& a, Path& b)
{
    float res = abs(a->angle - b->angle) / (a->angle + b->angle) +
                1.5 * abs(a->distance - b->distance) / (a->distance + b->distance);
    if (res > 0.5)
    {
        if (compareTwoPath(a, b) > 0)
            return 1;
        return -1;
    }
    return 0;
}


int compareBadPath(vtzy_types::path* a, vtzy_types::path* b)
{
    float res = abs(a->angle - b->angle) / (a->angle + b->angle) +
                1.5 * abs(a->distance - b->distance) / (a->distance + b->distance);
    // cout << "Compare two paths: " << res << endl;
    if (res < 0.08)
    {
        if (compareTwoPath(a, b) > 0)
            return 1;
        return -1;
    }
    return 0;
}


int dominantPath(vtzy_types::path* a, vtzy_types::path* b)
{
    if (a->angle * 1.02 < b->angle && a->distance * 1.05 < b->distance &&
        a->safety * 1.05 < b->safety)
        return -1;
    else if (a->angle > b->angle * 1.05 && a->distance > b->distance * 1.05 &&
             a->safety > b->safety * 1.05)
        return 1;
    return 0;
}


int tightlyDominantPath(vtzy_types::path* a, vtzy_types::path* b)
{
    if (a->angle < b->angle && a->distance < b->distance)
        return -1;
    else if (a->angle > b->angle && a->distance > b->distance)
        return 1;
    return 0;
}


int pathLength(vtzy_types::path* p)
{
    vtzy_types::point* p1 = p->begin;
    int len = 0;
    while (p1 != nullptr)
    {
        p1 = p1->next;
        ++len;
    }
    return len;
}


void pathFunc(vtzy_types::path* path)
{
    // cout << "cc";
    vtzy_types::point *p = path->begin, *p1 = p->next;
    float x = p1->x - p->x, y = p1->y - p->y;
    float z = sqrt(x * x + y * y);
    float distance = z, angle = 0, pastAngle = acos(x / z) * (y >= 0 ? 1 : -1), currAngle;
    int i = 0;
    while (p->next != nullptr)
    {
        p1 = p->next;
        x = p1->x - p->x;
        y = p1->y - p->y;
        z = sqrt(x * x + y * y);
        distance += z;
        currAngle = 100 * acos(x / z) * (y >= 0 ? 1 : -1);
        if (i++ != 0)
            angle += pow(currAngle - pastAngle, 2);
        pastAngle = currAngle;
        p = p1;
        // cout << angle << " ";
    }
    path->distance = distance;
    path->angle = std::max(1.0f, angle);
}


void pathFunc1(vtzy_types::path* path)
{
    // cout << endl;
    vtzy_types::point *p = path->begin, *p1 = p->next;
    float x = p1->x - p->x, y = p1->y - p->y;
    float z = sqrt(x * x + y * y);
    float distance = z, angle = 0, pastAngle = acos(x / z) * (y >= 0 ? 1 : -1), currAngle;
    path->safety = 0;
    while (p->next != nullptr)
    {
        path->safety += vtzy_types::mapGradient[(int)p->x][(int)p->y];
        p1 = p->next;
        x = p1->x - p->x;
        y = p1->y - p->y;
        z = sqrt(x * x + y * y);
        distance += z;
        distance += std::max(0, vtzy_types::mapGradient[(int)p1->x][(int)p1->y] - 500000);
        currAngle = acos(x / z) * (y >= 0 ? 1 : -1);
        // cout << currAngle << " " << (x/z) << endl;
        angle += pow(currAngle - pastAngle, 1.9);
        pastAngle = currAngle;
        p = p1;
        // cout << angle << " ";
    }
    path->safety /= pathLength(path);
    path->distance = distance;
    path->angle = angle;
}
