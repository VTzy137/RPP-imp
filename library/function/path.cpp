#include "function/path.hpp"
#include "function/graph.hpp"
#include "types.hpp"
#include <cmath>

namespace path {
float distanceToFinish(float x, float y) {
    vtzy_types::point* p = new vtzy_types::point(x, y, nullptr);
    return graph::euclideanDistance(p, vtzy_types::finish);
}

bool checkValidPosition(vtzy_types::point* p) {
    int x = (int)p->x, y = (int)p->y;
    // if(x < 0 || y < 0 || x > mapHeight || y > mapWidth) return false;
    if (vtzy_types::graphStatus[x][y] > 1000000 || vtzy_types::graphStatus[x + 1][y] > 1000000 ||
        vtzy_types::graphStatus[x][y + 1] > 1000000 ||
        vtzy_types::graphStatus[x + 1][y + 1] > 1000000)
        return false;
    return true;
}

bool checkValidPosition(float x1, float y1) {
    int x = (int)x1, y = (int)y1;
    // if(x < 0 || y < 0 || x > mapHeight || y > mapWidth) return false;
    if (vtzy_types::graphStatus[x][y] > 1000000 || vtzy_types::graphStatus[x + 1][y] > 1000000 ||
        vtzy_types::graphStatus[x][y + 1] > 1000000 ||
        vtzy_types::graphStatus[x + 1][y + 1] > 1000000)
        return false;
    return true;
}

bool checkValidPoint(vtzy_types::point* p) {
    int x = (int)p->x, y = (int)p->y;
    if (x < 0 || y < 0 || x > vtzy_types::mapHeight || y > vtzy_types::mapWidth) return false;
    if (vtzy_types::graphStatus[x][y] > 1000000) return false;
    return true;
}

bool checkValidPoint(int x, int y) {
    if (x < 0 || y < 0 || x > vtzy_types::mapHeight || y > vtzy_types::mapWidth) return false;
    if (vtzy_types::graphStatus[x][y] > 1000000) return false;
    return true;
}

bool checkValidLine(vtzy_types::point* p, vtzy_types::point* q) {
    float xBegin = p->x, yBegin = p->y, dis = graph::euclideanDistance(p, q);
    float cos = (q->x - xBegin) / dis, sin = (q->y - yBegin) / dis;
    for (float j = 0; j <= dis; ++j)
        if (checkValidPoint((int)(xBegin + j * cos), (int)(yBegin + j * sin)) == false)
            return false;
    return true;
}

float angleVector(vtzy_types::point* p1, vtzy_types::point* p2) {
    return atan(p2->y - p1->y / p2->x - p1->x);
}

float angleThreePoint(vtzy_types::point* p1, vtzy_types::point* p2, vtzy_types::point* p3) {
    return abs(angleVector(p3, p2) - angleVector(p2, p1));
}

void normalLine(vtzy_types::point* p1, vtzy_types::point* p2, vtzy_types::point* p3) {
    float y = p3->x - p1->x, x = -(p3->y - p1->y), z = graph::euclideanDistance(p1, p3);
    p2->x += x * 2.5 / z;
    p2->y += y * 2.5 / z;
}

std::pair<float, float> returnNormalLine(vtzy_types::point* p1, vtzy_types::point* p2,
                                         vtzy_types::point* p3) {
    float y = p3->x - p1->x, x = -(p3->y - p1->y), z = graph::euclideanDistance(p1, p3);
    return std::make_pair(x, y);
}

float compareTwoPath(vtzy_types::path* a, vtzy_types::path* b) {
    // return b->angle - a->angle + b->distance - a->distance;
    return (b->angle - a->angle) / b->angle + 2.5 * (b->distance - a->distance) / b->distance;
    // return (b->angle - a->angle) / b->angle + 2.5 * (b->distance - a->distance) / b->distance +
    // (b->safety - a->safety) * 10.5 / b->safety;
}

float compareTwoPath(vtzy_types::path* a, vtzy_types::path* b, float weight) {
    // return b->angle - a->angle + b->distance - a->distance;
    return weight * (b->angle - a->angle) / b->angle +
           2.5 * (b->distance - a->distance) / b->distance;
    // return (b->angle - a->angle) / b->angle + 2.5 * (b->distance - a->distance) / b->distance +
    // (b->safety - a->safety) * 10.5 / b->safety;
}

// int compareTwoPath(path *a, path *b) {
// return a->angle < b->angle + a->distance < b->distance;
// return a->distance < b->distance;
// return a->angle < b->angle;
// }

int compareSamePath(vtzy_types::path* a, vtzy_types::path* b) {
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
    int x1 = (int)x, y1 = (int)y, cur = vtzy_types::graphStatus[x1][y1], ne = -1;
    if (cur < 800000) return std::make_pair(x, y);
    for (int i = 0; i < 8; ++i) {
        if (vtzy_types::graphStatus[x1 + vtzy_types::nearPoint[i][0] * 2]
                                   [y1 + vtzy_types::nearPoint[i][1] * 2] < cur) {
            cur = vtzy_types::graphStatus[x1 + vtzy_types::nearPoint[i][0] * 2]
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
    int x1 = (int)x, y1 = (int)y, cur = vtzy_types::graphStatus[x1][y1], ne = -1;
    // if(cur < 200000) return make_pair(0, 0);
    for (int i = 0; i < 8; ++i) {
        if (vtzy_types::graphStatus[x1 + vtzy_types::nearPoint[i][0] * 2]
                                   [y1 + vtzy_types::nearPoint[i][1] * 2] < cur) {
            cur = vtzy_types::graphStatus[x1 + vtzy_types::nearPoint[i][0] * 2]
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
        path->safety += vtzy_types::graphStatus[(int)p->x][(int)p->y];
        p1 = p->next;
        x = p1->x - p->x;
        y = p1->y - p->y;
        z = sqrt(x * x + y * y);
        distance += z;
        distance += std::max(0, vtzy_types::graphStatus[(int)p1->x][(int)p1->y] - 500000);
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