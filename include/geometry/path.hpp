#pragma once

#include "geometry/point.hpp"
#include "geometry/vector.hpp"
#include <limits>
#include <memory>
#include <vector>

class Path
{
  private:
    static bool eligibleToRemoveNextPoint(Point& begin, Point& middle);

  public:
    inline static int populationMax = 100;
    inline static Path *currPath, *gPath;
    inline static std::vector<Path*> population;
    inline static constexpr float MAX_VALUE = 1e7f;

    bool alive = true;

    float distance;
    float angle;
    float risk;
    Point* begin;

    Path(const Path& other) : distance(other.distance), angle(other.angle), risk(other.risk)
    {
        if (!other.begin)
        {
            this->begin = nullptr;
            return;
        }

        this->begin = new Point(other.begin->y, other.begin->x, nullptr);
        auto currentCopy = this->begin;
        auto currentOrig = other.begin->nextPoint;

        while (currentOrig)
        {
            currentCopy->nextPoint = new Point(currentOrig->y, currentOrig->x, nullptr);
            currentCopy = currentCopy->nextPoint;
            currentOrig = currentOrig->nextPoint;
        }
    }

    Path() : distance(MAX_VALUE), angle(MAX_VALUE), risk(0.0f), begin(nullptr)
    {
    }

    explicit Path(Point* startPoint) : distance(MAX_VALUE), angle(MAX_VALUE), risk(0.0f), begin(startPoint)
    {
    }

    Path(float pathDistance, float pathAngle, float pathRisk, Point* startPoint)
        : distance(pathDistance), angle(pathAngle), risk(pathRisk), begin(startPoint)
    {
    }

    ~Path()
    {
        Point* current = begin;
        while (current != nullptr)
        {
            Point* next = current->nextPoint;
            delete current;
            current = next;
        }
        begin = nullptr;
    }


    int numPoints() const;

    static float angleThreshold;
    void simplifyPath();

    static float weightBetterAngle, weightBetterDistance, weightBetterRisk;
    bool isBetterThan(const Path& other) const;
    static bool betterPath(const Path& reference, const Path& other);
    int numTargetBetterThan(const Path& other) const;
    static int numTargetBetterPath(const Path& reference, const Path& other);

    static float weightSameAngle, weightSameDistance, weightSameRisk;
    bool isSamePath(const Path& other) const;
    static bool areTwoPathSame(const Path& reference, const Path& other);

    float isSuperiorThan(const Path& other) const;
    static bool dominantPath(const Path& reference, const Path& other);

    void calculatePathTargetScore();

    void changePathTo(const Path& other);
};
