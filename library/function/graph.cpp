
#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>
#include "function/graph.hpp"

namespace graph {
float euclideanDistance(vtzy_types::point* p1, vtzy_types::point* p2) {
    float x = p1->x - p2->x, y = p1->y - p2->y;
    return std::sqrt(x * x + y * y);
}

bool vectorThreePoint(vtzy_types::point* p1, vtzy_types::point* p2, vtzy_types::point* p3) {
    return (p3->x - p2->x) * (p2->x - p1->x) + (p3->y - p2->y) * (p2->y - p1->y) > 0.0;
}

void changeToNewGraph() {
    vtzy_types::initStart = new vtzy_types::point(vtzy_types::start->x, vtzy_types::start->y, nullptr);
    vtzy_types::initFinish = new vtzy_types::point(vtzy_types::finish->x, vtzy_types::finish->y, nullptr);
    float a = vtzy_types::finish->x - vtzy_types::start->x, b = vtzy_types::finish->y - vtzy_types::start->y;
    float cos = a / std::sqrt(a * a + b * b), sin = b / std::sqrt(a * a + b * b);
    for (int i = 0; i < vtzy_types::numObstacle; i++) {
        vtzy_types::point* p = vtzy_types::obstacles[i];
        while (p) {
            float x1 = cos * (p->x - vtzy_types::start->x) + sin * (p->y - vtzy_types::start->y);
            float y1 = cos * (p->y - vtzy_types::start->y) - sin * (p->x - vtzy_types::start->x);
            p->x = x1 + 150;
            p->y = y1 + 150;
            p = p->next;
        }
    }
    vtzy_types::finish->x = euclideanDistance(vtzy_types::start, vtzy_types::finish) + 150;
    vtzy_types::finish->y = 150;
    vtzy_types::start->x = 150;
    vtzy_types::start->y = 150;
}

void changeToInitGraph() {
    vtzy_types::start = vtzy_types::initStart;
    vtzy_types::finish = vtzy_types::initFinish;
    float a = vtzy_types::finish->x - vtzy_types::start->x, b = vtzy_types::finish->y - vtzy_types::start->y;
    float cos = a / std::sqrt(a * a + b * b), sin = b / std::sqrt(a * a + b * b);
    for (int i = 0; i < vtzy_types::numObstacle; i++) {
        vtzy_types::point* p = vtzy_types::obstacles[i];
        while (p) {
            p->x -= 150;
            p->y -= 150;
            float x1 = cos * p->x - sin * p->y;
            float y1 = cos * p->y + sin * p->x;
            p->x = x1 + vtzy_types::start->x;
            p->y = y1 + vtzy_types::start->y;
            p = p->next;
        }
    }
}

bool onMapSize(int i, int j) {
    if (i < 0 || j < 0 || i > vtzy_types::mapWidth || j > vtzy_types::mapHeight) return false;
    return true;
}

void markPointNotCome(float x, float y) {
    int x1 = std::max(1, (int)x), y1 = std::max(1, (int)y);
    vtzy_types::graphStatus[x1][y1] = 1000000;
    vtzy_types::graphStatus[x1 - 1][y1] = 1000000;
    vtzy_types::graphStatus[x1][y1 - 1] = 1000000;
    vtzy_types::graphStatus[x1 - 1][y1 - 1] = 1000000;
    vtzy_types::graphStatus[x1 + 1][y1 - 1] = 1000000;
    vtzy_types::graphStatus[x1 - 1][y1 + 1] = 1000000;
    vtzy_types::graphStatus[x1 + 1][y1] = 1000000;
    vtzy_types::graphStatus[x1][y1 + 1] = 1000000;
    vtzy_types::graphStatus[x1 + 1][y1 + 1] = 1000000;
}

void markPointNotCome2(float x, float y) {
    int x1 = std::max(1, (int)x), y1 = std::max(1, (int)y);
    vtzy_types::graphStatus[x1 - 2][y1] = 1000000;
    vtzy_types::graphStatus[x1][y1 - 2] = 1000000;
    vtzy_types::graphStatus[x1 - 2][y1 - 2] = 1000000;
    vtzy_types::graphStatus[x1 + 2][y1 - 2] = 1000000;
    vtzy_types::graphStatus[x1 - 2][y1 + 2] = 1000000;
    vtzy_types::graphStatus[x1 + 2][y1] = 1000000;
    vtzy_types::graphStatus[x1][y1 + 2] = 1000000;
    vtzy_types::graphStatus[x1 + 2][y1 + 2] = 1000000;
}

int reSizeX;
int convx(float a) {
    return (int)(a * reSizeX);
}

int reSizeY;
int convy(float a) {
    return 900 - (int)(a * reSizeY);
}
void markLineNotCome(vtzy_types::point* p, vtzy_types::point* q) {
    // cout << p->x << " " << p->y << " " << q->x << " " << q->y << endl;
    float xBegin = p->x, yBegin = p->y, dis = euclideanDistance(p, q);
    float cos = (q->x - xBegin) / dis, sin = (q->y - yBegin) / dis;
    for (float j = 0; j < dis + 1.0; ++j) {
        markPointNotCome(xBegin + j * cos, yBegin + j * sin);
    }
}

// int stopCome = 50000;
// void comePoint(int x, int y){
//     if(--stopCome < 0 || graphStatus[x][y] != 0) return;
//     graphStatus[x][y] = 1;
//     for(int i = 0; i < 8; ++i)
//         comePoint(x+nearPoint[i][0], y+nearPoint[i][1]);
// }

void smoothObstacle() {
    // comePoint((int)start->x, (int)start->y);
    std::queue<std::pair<int, int>> pq;
    pq.push(std::make_pair((int)vtzy_types::start->x, (int)vtzy_types::start->y));
    while (pq.empty() == false) {
        int x = pq.front().first, y = pq.front().second;
        pq.pop();
        for (int i = 0; i < 8; ++i) {
            if (vtzy_types::graphStatus[x + vtzy_types::nearPoint[i][0]][y + vtzy_types::nearPoint[i][1]] == 0) {
                pq.push(std::make_pair(x + vtzy_types::nearPoint[i][0], y + vtzy_types::nearPoint[i][1]));
                vtzy_types::graphStatus[x + vtzy_types::nearPoint[i][0]][y + vtzy_types::nearPoint[i][1]] = 1;
            }
        }
    }
}

void obstacleGradient() {
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i <= vtzy_types::mapHeight; i++)
        for (int j = 0; j <= vtzy_types::mapWidth; j++)
            if (vtzy_types::graphStatus[i][j] == 1000000) {
                q.push(std::make_pair(i, j));
                vtzy_types::graphStatus[i][j] = 1100100;
            }
    while (q.empty() == false) {
        int i = q.front().first, j = q.front().second;
        q.pop();
        for (int k = 0; k < 8; ++k) {
            int i1 = i + vtzy_types::nearPoint[k][0], j1 = j + vtzy_types::nearPoint[k][1], t = 1;
            if (onMapSize(i1, j1) == false) continue;
            if (vtzy_types::graphStatus[i1][j1] == 0)
                vtzy_types::graphStatus[i1][j1] = vtzy_types::graphStatus[i][j] + 100000;
            else if (vtzy_types::graphStatus[i1][j1] == 1)
                vtzy_types::graphStatus[i1][j1] = std::max(vtzy_types::graphStatus[i][j] - 100000, 10);
            else
                t = 0;
            if (t) q.push(std::make_pair(i1, j1));
        }
    }
}

void markObstacle() {
    reSizeX = 1000 / vtzy_types::mapWidth;
    reSizeY = 1000 / vtzy_types::mapHeight;
    for (int i = 0; i < vtzy_types::numObstacle; ++i) {
        vtzy_types::point *p = vtzy_types::obstacles[i], *q = p->next;
        while (q != nullptr) {
            // if(q->next != nullptr && vectorThreePoint(p, q, q->next) == false){
            //     markPointNotCome2(q->x, q->y);
            // }
            markLineNotCome(p, q);
            p = q;
            q = q->next;
        }
        q = vtzy_types::obstacles[i];
        markLineNotCome(p, q);
    }
    // for(int i = 0; i < 300; i++){
    //     for(int j = 0; j < 300; j++)
    //         cout << !graphStatus[i][j] << " ";
    //     cout << endl;
    // }
    vtzy_types::graphStatus[(int)vtzy_types::start->x][(int)vtzy_types::start->y] = 0;
    vtzy_types::graphStatus[(int)vtzy_types::finish->x][(int)vtzy_types::finish->y] = 0;
    smoothObstacle();

    obstacleGradient();
}

void resetGraphStatus() {
    for (int i = 0; i < 1000; ++i) {
        // rand();
        for (int j = 0; j < 1000; ++j)
            vtzy_types::graphStatus[i][j] = 0;
    }
    markObstacle();
}
}
