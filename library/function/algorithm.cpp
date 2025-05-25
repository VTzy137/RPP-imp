#include "function/algorithm.hpp"
#include "evolution/mutation.hpp"
#include "function/graph.hpp"
#include "function/path.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <utility>

namespace algorithm {
typedef std::pair<float, std::pair<int, int>> pairDistance;
vtzy_types::path* aStar() {
    std::set<pairDistance> aStar;
    int xStart = (int)vtzy_types::start->x, yStart = (int)vtzy_types::start->y,
        xFinish = (int)vtzy_types::finish->x, yFinish = (int)vtzy_types::finish->y;
    aStar.insert(std::make_pair(0.0, std::make_pair(xStart, yStart)));
    while (aStar.empty() == false) {
        pairDistance newPoint = *aStar.begin();
        aStar.erase(aStar.begin());
        int x = newPoint.second.first, y = newPoint.second.second, past = x * 1000 + y;
        for (int i = 0; i < 8; ++i) {
            int x1 = x + vtzy_types::nearPoint[i][0];
            int y1 = y + vtzy_types::nearPoint[i][1];
            if (vtzy_types::visited[x1][y1] == 0 && path::checkValidPoint(x1, y1)) {
                vtzy_types::visited[x1][y1] = past;
                vtzy_types::gDistance[x1][y1] =
                    vtzy_types::gDistance[x][y] +
                    sqrt(abs(vtzy_types::nearPoint[i][0]) + abs(vtzy_types::nearPoint[i][1]));
                aStar.insert(
                    std::make_pair(vtzy_types::gDistance[x1][y1] + path::distanceToFinish(x1, y1),
                                   std::make_pair(x1, y1)));
                if (x1 == xFinish && y1 == yFinish) goto findSolution;
            } else if (path::checkValidPoint(x1, y1)) {
                vtzy_types::gDistance[x1][y1] =
                    std::min((float)vtzy_types::gDistance[x1][y1],
                             (float)vtzy_types::gDistance[x][y] +
                                 (float)sqrt((abs(vtzy_types::nearPoint[i][0]) +
                                              abs(vtzy_types::nearPoint[i][1]))));
            }
        }
    }

findSolution:
    vtzy_types::path* res =
        new vtzy_types::path(vtzy_types::gDistance[xFinish][yFinish], 0, nullptr);
    vtzy_types::point* p = new vtzy_types::point((float)xFinish, (float)yFinish, nullptr);
    int stop = 1000;
    while (--stop > 0) {
        int tmp = vtzy_types::visited[xFinish][yFinish];
        xFinish = tmp / 1000;
        yFinish = tmp % 1000;
        p = new vtzy_types::point((float)xFinish, (float)yFinish, p);
        if (xFinish == xStart && yFinish == yStart) break;
    }

    res->begin = p;
    vtzy_types::astarRes = res;
    return res;
}

void decreaseDimension() {
    for (int i = 0; i < vtzy_types::numPopulations; ++i) {
        vtzy_types::point* p = vtzy_types::population[i]->begin->next;
        while (p->next != nullptr && p->next->next != nullptr) {
            float eDis = graph::euclideanDistance(p, p->next),
                  angle = path::turnAngle(p, p->next, p->next->next);
            if (eDis < 15 && eDis > 3 && angle < 0.003) p->next = p->next->next;
            p = p->next;
        }
    }
}

vtzy_types::path* makeCopyPath(vtzy_types::path* p) {
    vtzy_types::point *p1 = p->begin, *q1 = new vtzy_types::point(p1->x, p1->y, nullptr);
    vtzy_types::path* q = new vtzy_types::path(q1);
    p1 = p1->next;
    while (p1 != nullptr) {
        q1->next = new vtzy_types::point(p1->x, p1->y, nullptr);
        q1 = q1->next;
        p1 = p1->next;
    }
    path::pathFunc(q);
    return q;
}

void setPathFromAstar() {
    vtzy_types::point* p = vtzy_types::astarRes->begin;
    for (int i = 0; i <= vtzy_types::populationMax; ++i) {
        vtzy_types::point *q = p, *tmp = new vtzy_types::point();
        vtzy_types::population[i] = new vtzy_types::path(tmp);
        while (q != nullptr) {
            tmp->next = new vtzy_types::point(q->x, q->y, nullptr);
            tmp = tmp->next;
            q = q->next;
        }
        vtzy_types::population[i]->begin = vtzy_types::population[i]->begin->next;
        path::pathFunc(vtzy_types::population[i]);
        vtzy_types::pPath[i] = vtzy_types::population[i];
    }
    vtzy_types::gPath = vtzy_types::pPath[vtzy_types::populationMax];
}

void updateBestPath() {
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        if (path::compareTwoPath(vtzy_types::population[i], vtzy_types::pPath[i]) > 0)
            vtzy_types::pPath[i] = makeCopyPath(vtzy_types::population[i]);
        if (path::compareTwoPath(vtzy_types::population[i], vtzy_types::gPath) > 0) {
            vtzy_types::gPath = vtzy_types::population[i];
        }
    }
}

void updateV(int i) {
    int j = 1;
    vtzy_types::point *p = vtzy_types::population[i]->begin->next,
                      *pp = vtzy_types::pPath[i]->begin->next;
    while (p->next != nullptr) {
        vtzy_types::v[i][j][0] =
            vtzy_types::w0PSO * vtzy_types::v[i][j][0] + vtzy_types::w1PSO * (pp->x - p->x);
        vtzy_types::v[i][j][1] =
            vtzy_types::w0PSO * vtzy_types::v[i][j][1] + vtzy_types::w1PSO * (pp->y - p->y);
        ++j;
        p = p->next;
        pp = pp->next;
    }
}

void PSOmigrate() {
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        vtzy_types::point *p1 = vtzy_types::population[i]->begin, *p = p1->next;
        std::pair<float, float> q;

        while (p != nullptr && p->next != nullptr) {
            int x = (int)p->x, y = (int)p->y;
            p->x = p->x * 0.8 + (p->next->x + p1->x) * 10 / 100;
            p->y = p->y * 0.8 + (p->next->y + p1->y) * 10 / 100;
            q = path::gradientPoint(p->x, p->y);
            p->x = p->x * 0.7 + q.first * 0.3;
            p->y = p->y * 0.7 + q.second * 0.3;
            if (graph::onMapSize((int)p->x, (int)p->y) == false) {
                vtzy_types::normalDirect[i] = 1 - vtzy_types::normalDirect[i];
            };
            if (path::checkValidPoint(p) == false)
                if (vtzy_types::normalDirect[i])
                    path::smallerAngle(p1, p, p->next);
                else
                    path::smallerAngle(p->next, p, p1);

            if (graph::euclideanDistance(p, p1) > 7) {
                p1->next = new vtzy_types::point((p->x + p1->x) / 2, (p->y + p1->y) / 2, p1->next);
                p1 = p1->next;
            } else if (graph::euclideanDistance(p, p1) < 3 &&
                       path::turnAngle(p1, p, p->next) < 0.2) {
                p1->next = p->next;
                p = p1->next;
            } else {
                p = p->next;
                p1 = p1->next;
            }
        }
    }
}

float wVPSO = 0.1;
void PSO() {
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        updateV(i);
        vtzy_types::point* p = vtzy_types::population[i]->begin->next;
        vtzy_types::pathLen = path::pathLength(vtzy_types::population[i]);
        for (int j = 1; j < vtzy_types::pathLen - 1; ++j) {
            p->x += vtzy_types::v[i][j][0] * wVPSO;
            p->y += vtzy_types::v[i][j][1] * wVPSO;
            p = p->next;
        }
    }
}

vtzy_types::path* combination1(vtzy_types::path* p, vtzy_types::path* q) {
    if (q == nullptr) return nullptr;
    vtzy_types::point *p1 = p->begin, *q1 = q->begin->next,
                      *tmp1 = new vtzy_types::point(p1->x, p1->y, nullptr);
    p1 = p1->next;
    vtzy_types::path* tmp = new vtzy_types::path(tmp1);
    while (p1->next != nullptr) {
        tmp1->next = new vtzy_types::point((p1->x + q1->x) / 2, (p1->y + q1->y) / 2, nullptr);
        tmp1 = tmp1->next;
        p1 = p1->next;
        q1 = q1->next;
    }
    tmp1->next = new vtzy_types::point(p1->x, p1->y, nullptr);
    // tmp->begin = tmp->begin->next;
    path::pathFunc(tmp);
    return tmp;
}

int chooseCombine = 52465, modCombine = 9383761;
vtzy_types::path* combination2(vtzy_types::path* p, vtzy_types::path* q) {
    if (q == nullptr) return nullptr;
    vtzy_types::point *p1 = p->begin, *q1 = q->begin->next,
                      *tmp1 = new vtzy_types::point(p1->x, p1->y, nullptr);
    p1 = p1->next;
    vtzy_types::path* tmp = new vtzy_types::path(tmp1);
    while (p1->next != nullptr) {
        chooseCombine = (chooseCombine * 6) % modCombine;
        if ((chooseCombine & 1) == 1)
            tmp1->next = new vtzy_types::point(p1->x, p1->y, nullptr);
        else
            tmp1->next = new vtzy_types::point(q1->x, q1->y, nullptr);
        tmp1 = tmp1->next;
        p1 = p1->next;
        q1 = q1->next;
    }
    tmp1->next = new vtzy_types::point(p1->x, p1->y, nullptr);
    path::pathFunc(tmp);
    return tmp;
}

void ES(float toiu) {
    for (int i = 0; i < vtzy_types::numPopulations; ++i) {
        vtzy_types::pathLen = path::pathLength(vtzy_types::population[i]);
        vtzy_types::path* tmp = Mutation::mutation(vtzy_types::population[i], toiu);
        if (path::compareTwoPath(tmp, vtzy_types::population[i]) > 0) {
            // if(tightlyDominantPath(tmp, population[i])){
            vtzy_types::population[i] = combination1(tmp, vtzy_types::pPath[i]);
            // population[i] = tmp;
        }
        // population[i] = combination1(population[i], gPath);
    }
}

void lastSocial() {
    for (int i = 0; i < vtzy_types::numPopulations; ++i) {
        for (int j = 0; j < vtzy_types::numPopulations; ++j) {
            if (vtzy_types::population[i] == nullptr || vtzy_types::population[j] == nullptr)
                continue;
            int tmp =
                path::tightlyDominantPath(vtzy_types::population[i], vtzy_types::population[j]);
            if (tmp == 1)
                vtzy_types::population[i] = nullptr;
            else if (tmp == -1)
                vtzy_types::population[j] = nullptr;
        }
    }
    int numPopu = 0;
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        if (vtzy_types::population[i] == nullptr) continue;
        vtzy_types::pPath[numPopu] = makeCopyPath(vtzy_types::population[i]);
        vtzy_types::population[numPopu] = makeCopyPath(vtzy_types::population[i]);
        if (path::compareTwoPath(vtzy_types::pPath[numPopu], vtzy_types::gPath) > 0)
            vtzy_types::gPath = makeCopyPath(vtzy_types::pPath[numPopu]);
        numPopu++;
    }
    vtzy_types::numPopulations = numPopu;
}

void saveExe() {
    decreaseDimension();
    vtzy_types::gPath = makeCopyPath(vtzy_types::population[0]);
    for (int i = 0; i < vtzy_types::numPopulations; ++i) {
        path::pathFunc(vtzy_types::population[i]);
        for (int j = 0; j < i; ++j) {
            if (vtzy_types::population[i] == nullptr || vtzy_types::population[j] == nullptr)
                continue;
            int tmp = path::compareBadPath(vtzy_types::population[i], vtzy_types::population[j]);
            // int tmp = path::tightlyDominantPath(population[j], population[i]);
            if (tmp == 1)
                vtzy_types::population[j] = nullptr;
            else if (tmp == -1)
                vtzy_types::population[i] = nullptr;
        }
    }
    int numPopu = 0;
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        if (vtzy_types::population[i] == nullptr) continue;
        // cout << i << " " << endl;
        vtzy_types::pPath[numPopu] = makeCopyPath(vtzy_types::population[i]);
        vtzy_types::population[numPopu] = makeCopyPath(vtzy_types::population[i]);
        if (path::compareTwoPath(vtzy_types::pPath[numPopu], vtzy_types::gPath) > 0)
            vtzy_types::gPath = makeCopyPath(vtzy_types::pPath[numPopu]);
        numPopu++;
    }
    // if(numPopu > 5)
    vtzy_types::numPopulations = numPopu;
    // cout << "Number of " << numPopulations << endl;
}

} // namespace algorithm