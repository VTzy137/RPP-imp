#include "geometry/path.hpp"
#include "geometry/map.hpp"
#include "geometry/point.hpp"
#include "global_type.hpp"
#include <cmath>
#include <iostream>


int Path::numPoints() const
{
    const Point* point = this->begin;
    int numPoints = 0;
    while (point != nullptr)
    {
        point = point->nextPoint;
        ++numPoints;
    }
    return numPoints;
}

float Path::angleThreshold = 0.003f;
bool Path::eligibleToRemoveNextPoint(Point& begin, Point& nextPoint)
{
    if (nextPoint.nextPoint == nullptr)
    {
        return false;
    }

    float euclideanDistance = begin.euclideanDistanceTo(nextPoint);
    float angle = Vector::turnAngle(begin, nextPoint, *(nextPoint.nextPoint));
    // std::cout << "angle: " << angle << std::endl;
    if (euclideanDistance > 5 && euclideanDistance < 13 && fabs(angle) < angleThreshold)
    {
        return true;
    }
    return false;
}

void Path::simplifyPath()
{
    Point* point = this->begin;
    while (point->nextPoint != nullptr)
    {
        Point* nextPoint = point->nextPoint;
        if (eligibleToRemoveNextPoint(*point, *nextPoint))
        {
            point->nextPoint = nextPoint->nextPoint;
        }
        point = point->nextPoint;
    }
}


float Path::weightBetterAngle = 1.0f;
float Path::weightBetterDistance = 2.5f;
float Path::weightBetterRisk = 0.0f;

bool Path::isBetterThan(const Path& other) const
{
    float diffAngle = this->angle - other.angle;
    float diffDistance = this->distance - other.distance;
    float diffRisk = this->risk - other.risk;
    return weightBetterAngle * diffAngle + weightBetterDistance * diffDistance + weightBetterRisk * diffRisk < 0.0f;
}


bool Path::betterPath(const Path& reference, const Path& other)
{
    return reference.isBetterThan(other);
}


int Path::numTargetBetterThan(const Path& other) const
{
    int numBetter = 0;
    if (this->angle < other.angle)
    {
        numBetter++;
    }
    if (this->distance < other.distance)
    {
        numBetter++;
    }
    if (this->risk > other.risk)
        numBetter++;
    return numBetter;
}


int Path::numTargetBetterPath(const Path& reference, const Path& other)
{
    return reference.numTargetBetterThan(other);
}


float Path::weightSameAngle = 1.0f;
float Path::weightSameDistance = 1.5f;
float Path::weightSameRisk = 0.0f;

bool Path::isSamePath(const Path& other) const
{
    float diffAngle = this->angle - other.angle;
    float diffDistance = this->distance - other.distance;
    float diffRisk = this->risk - other.risk;

    float res = weightSameAngle * fabs(diffAngle) / (this->angle + other.angle) +
                weightSameDistance * fabs(diffDistance) / (this->distance + other.distance) +
                weightSameRisk * fabs(diffRisk) / (this->risk + other.risk);
    return res < 0.08f;
}


bool Path::areTwoPathSame(const Path& reference, const Path& other)
{
    return reference.isSamePath(other);
}


float Path::isSuperiorThan(const Path& other) const
{
    return this->isSamePath(other) && this->isBetterThan(other);
}


bool Path::dominantPath(const Path& a, const Path& b)
{
    if (a.angle <= b.angle && a.distance <= b.distance && a.risk <= b.risk)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Path::calculatePathTargetScore()
{
    Point* point = this->begin;
    Point* nextPoint = point->nextPoint;
    float distance = point->euclideanDistanceTo(*nextPoint);
    float angle = 0.0f;
    float risk = 0.0f;
    while (nextPoint->nextPoint != nullptr)
    {
        distance += nextPoint->euclideanDistanceTo(*nextPoint->nextPoint);
        float turnAngle = Vector::turnAngle(*point, *nextPoint, *nextPoint->nextPoint);
        angle += turnAngle * turnAngle;

        risk += std::max(0, nextPoint->gradientRisk() - 400000);
        point = nextPoint;
        nextPoint = point->nextPoint;
    }
    this->risk = risk / this->numPoints() / 2000;
    this->distance = distance;
    this->angle = std::max(0.0f, angle) * 10;
}

void Path::changePathTo(const Path& other)
{
    this->distance = other.distance;
    this->angle = other.angle;
    this->risk = other.risk;
    Point* point = this->begin;
    Point* nextPoint = point->nextPoint;
    
    point->nextPoint = nullptr;
    while (nextPoint != nullptr)
    {
        Point* tmp = nextPoint;
        nextPoint = point->nextPoint;
        delete tmp;
    }

    Point* otherPoint = other.begin;
    while (otherPoint != nullptr)
    {
        point->y = otherPoint->y;
        point->x = otherPoint->x;
        if (otherPoint->nextPoint != nullptr)
        {
            point->nextPoint = new Point();
        }
        otherPoint = otherPoint->nextPoint;
        point = point->nextPoint;
    }
}