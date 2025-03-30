
#ifndef TYPES_H
#define TYPES_H

struct point{
    double x, y;
    point *next;    
    point() : x(0), y(0), next(nullptr) {};
    point(double x1, double y1, point *next1) : x(x1), y(y1), next(next1) {}
};
int nearPoint[8][2] = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
point *start, *finish, *obstacles[1000], *initStart, *initFinish;
int mapHeight, mapWidth, numObstacle;
int graphStatus[1000][1000] = {};

struct path {
    double distance=10, angle=10, safety;
    point *begin;
    path() : distance(1000000), angle(1000000), begin(nullptr) {}
    path(point *p1) : distance(1000000), angle(1000000), begin(p1) {}
    path(double distance1, double angle1, point *p1) : distance(distance1), angle(angle1), begin(p1) {}
};

point relative;

using Index = int;

#endif