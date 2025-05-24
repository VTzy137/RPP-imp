#pragma once
#include "geometry/vector.hpp"
#include <limits>
#include <memory>

class Path
{
  public:
    inline static constexpr float MAX_VALUE = 1e7f;

    float distance;
    float angle;
    float safety;
    std::shared_ptr<Point> begin;

    Path() : distance(MAX_VALUE), angle(MAX_VALUE), safety(0.0f), begin(nullptr)
    {
    }

    explicit Path(std::shared_ptr<Point> startPoint)
        : distance(MAX_VALUE), angle(MAX_VALUE), safety(0.0f), begin(startPoint)
    {
    }

    Path(float pathDistance, float pathAngle, float pathSafety, std::shared_ptr<Point> startPoint)
        : distance(pathDistance), angle(pathAngle), safety(pathSafety), begin(startPoint)
    {
    }

    bool isBetterThan(const Path& other) const;
    bool isBetterThan(const Path& other, float weight) const;
    static bool betterPath(const Path& a, const Path& b);
    static bool betterPath(const Path& a, const Path& b, float weight);

    static int compareSamePath(const Path& a, const Path& b);
    static int compareBadPath(const Path& a, const Path& b);
    static int dominantPath(const Path& a, const Path& b);
    static int tightlyDominantPath(const Path& a, const Path& b);
    static std::pair<float, float> gradientPoint(float x, float y);
    static std::pair<float, float> gradientPointTightly(float x, float y);
    static int pathLength(const Path& p);
    static void pathFunc(Path& path);
};
