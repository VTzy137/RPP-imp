#pragma once

namespace vtzy_types {
struct point {
    float x, y;
    point* next;
    point() : x(0), y(0), next(nullptr){};
    point(float x1, float y1, point* next1) : x(x1), y(y1), next(next1) {}
};
// int nearPoint[8][2] = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
// point *start, *finish, *obstacles[1000], *initStart, *initFinish;
// int mapHeight, mapWidth, numObstacle;
// int graphStatus[1000][1000] = {};

struct path {
    float distance = 10, angle = 10, safety;
    point* begin;
    path() : distance(1000000), angle(1000000), begin(nullptr) {}
    path(point* p1) : distance(1000000), angle(1000000), begin(p1) {}
    path(float distance1, float angle1, point* p1)
        : distance(distance1), angle(angle1), begin(p1) {}
};

// extern int nearPoint[8][2];
// extern point *start, *finish, *obstacles[1000], *initStart, *initFinish;
// extern int mapHeight, mapWidth, numObstacle;
// extern int graphStatus[1000][1000];

// extern point relative;

inline int nearPoint[8][2] = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
inline point *start, *finish, *obstacles[1000], *initStart, *initFinish;
inline int mapHeight = 0, mapWidth = 0, numObstacle = 0;
inline int graphStatus[1000][1000] = {};
inline point relative;
inline float gDistance[1000][1000] = {};
inline int visited[1000][1000] = {};
inline vtzy_types::path* astarRes;
inline vtzy_types::path *currPath, *gPath, *pPath[1000], *population[1000];
inline int numPopulations = 5, populationMax = 100, pathLen;
inline float w0PSO = 0.3, w1PSO = 0.2, w2PSO = 0.2, w3PSO = 0.1, v[1000][200][2] = {}, normalDirect[100];

} // namespace vtzy_types
