#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include "global_state.hpp"
#include <cmath>

namespace path {

bool checkValidLine(const Point& from, const Point& to) {
    float fromX = from.x, fromY = from.y, euclideanDistance = Vector::euclideanLength(from, to);
    float cos = (to.x - fromX) / euclideanDistance, sin = (to.y - fromY) / euclideanDistance;
    for (float step = 0; step <= euclideanDistance; step += 1)
        if (Point::canMoveTo((int)(fromX + step * cos), (int)(fromY + step * sin)) == false)
            return false;
    return true;
}

bool isLineClear(const Point& fromPoint, const Point& toPoint) {
    float fromX = fromPoint.x;
    float fromY = fromPoint.y;
    float distance = Vector::euclideanLength(fromPoint, toPoint);

    float directionX = (toPoint.x - fromX) / distance;
    float directionY = (toPoint.y - fromY) / distance;

    for (float step = 0; step <= distance; step += 1.0f) {
        int checkX = static_cast<int>(fromX + step * directionX);
        int checkY = static_cast<int>(fromY + step * directionY);

        if (!Point::canMoveTo(checkX, checkY)) {
            return false;
        }
    }

    return true;
}

void smallerAngle(const Point& from, Point& middle, const Point& to) {
    float y = to.x - from.x;
    float x = -(to.y - from.y);
    float z = Vector::euclideanLength(from, to);
    middle.x += x * 2.5 / z;
    middle.y += y * 2.5 / z;
}

float Path::compareTwoPath(const Path& a, const Path& b) {
    return (b.angle - a.angle) / b.angle + 2.5 * (b.distance - a.distance) / b.distance;
}

float Path::compareTwoPath(const Path& a, const Path& b, float weight) {
    return weight * (b.angle - a.angle) / b.angle + 2.5 * (b.distance - a.distance) / b.distance;
}

int compareSamePath(Path& a, Path& b) {
    float res = abs(a->angle - b->angle) / (a->angle + b->angle) +
                1.5 * abs(a->distance - b->distance) / (a->distance + b->distance);
    if (res > 0.5) {
        if (compareTwoPath(a, b) > 0) return 1;
        return -1;
    }
    return 0;
}

int compareBadPath(vtzy_types::path* a, vtzy_types::path* b) {
    float res = abs(a->angle - b->angle) / (a->angle + b->angle) +
                1.5 * abs(a->distance - b->distance) / (a->distance + b->distance);
    // cout << "Compare two paths: " << res << endl;
    if (res < 0.08) {
        if (compareTwoPath(a, b) > 0) return 1;
        return -1;
    }
    return 0;
}

int dominantPath(vtzy_types::path* a, vtzy_types::path* b) {
    if (a->angle * 1.02 < b->angle && a->distance * 1.05 < b->distance &&
        a->safety * 1.05 < b->safety)
        return -1;
    else if (a->angle > b->angle * 1.05 && a->distance > b->distance * 1.05 &&
             a->safety > b->safety * 1.05)
        return 1;
    return 0;
}

int tightlyDominantPath(vtzy_types::path* a, vtzy_types::path* b) {
    if (a->angle < b->angle && a->distance < b->distance)
        return -1;
    else if (a->angle > b->angle && a->distance > b->distance)
        return 1;
    return 0;
}

std::pair<float, float> gradientPoint(float x, float y) {
    int x1 = (int)x, y1 = (int)y, cur = vtzy_types::mapGradient[x1][y1], ne = -1;
    if (cur < 800000) return std::make_pair(x, y);
    for (int i = 0; i < 8; ++i) {
        if (vtzy_types::mapGradient[x1 + vtzy_types::nearPoint[i][0] * 2]
                                   [y1 + vtzy_types::nearPoint[i][1] * 2] < cur) {
            cur = vtzy_types::mapGradient[x1 + vtzy_types::nearPoint[i][0] * 2]
                                         [y1 + vtzy_types::nearPoint[i][1] * 2];
            ne = i;
        }
    }
    if (ne != -1) {
        x += vtzy_types::nearPoint[ne][0] * 2;
        y += vtzy_types::nearPoint[ne][1] * 2;
    }
    return std::make_pair(x, y);
}

std::pair<float, float> gradientPointTightly(float x, float y) {
    int x1 = (int)x, y1 = (int)y, cur = vtzy_types::mapGradient[x1][y1], ne = -1;
    // if(cur < 200000) return make_pair(0, 0);
    for (int i = 0; i < 8; ++i) {
        if (vtzy_types::mapGradient[x1 + vtzy_types::nearPoint[i][0] * 2]
                                   [y1 + vtzy_types::nearPoint[i][1] * 2] < cur) {
            cur = vtzy_types::mapGradient[x1 + vtzy_types::nearPoint[i][0] * 2]
                                         [y1 + vtzy_types::nearPoint[i][1] * 2];
            ne = i;
        }
    }
    if (ne == -1) return std::make_pair(0, 0);
    return std::make_pair(vtzy_types::nearPoint[ne][0], vtzy_types::nearPoint[ne][1]);
}

int pathLength(vtzy_types::path* p) {
    vtzy_types::point* p1 = p->begin;
    int len = 0;
    while (p1 != nullptr) {
        p1 = p1->next;
        ++len;
    }
    return len;
}

void pathFunc(vtzy_types::path* path) {
    // cout << "cc";
    vtzy_types::point *p = path->begin, *p1 = p->next;
    float x = p1->x - p->x, y = p1->y - p->y;
    float z = sqrt(x * x + y * y);
    float distance = z, angle = 0, pastAngle = acos(x / z) * (y >= 0 ? 1 : -1), currAngle;
    int i = 0;
    while (p->next != nullptr) {
        p1 = p->next;
        x = p1->x - p->x;
        y = p1->y - p->y;
        z = sqrt(x * x + y * y);
        distance += z;
        currAngle = 100 * acos(x / z) * (y >= 0 ? 1 : -1);
        if (i++ != 0) angle += pow(currAngle - pastAngle, 2);
        pastAngle = currAngle;
        p = p1;
        // cout << angle << " ";
    }
    path->distance = distance;
    path->angle = std::max(1.0f, angle);
}

void pathFunc1(vtzy_types::path* path) {
    // cout << endl;
    vtzy_types::point *p = path->begin, *p1 = p->next;
    float x = p1->x - p->x, y = p1->y - p->y;
    float z = sqrt(x * x + y * y);
    float distance = z, angle = 0, pastAngle = acos(x / z) * (y >= 0 ? 1 : -1), currAngle;
    path->safety = 0;
    while (p->next != nullptr) {
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

} // namespace path