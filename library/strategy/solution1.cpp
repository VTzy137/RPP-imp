#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "UI/openGl.hpp"
#include "app.hpp"
#include "evolution/mutation.hpp"
#include "function/algorithm.hpp"
#include "function/graph.hpp"
#include "function/initPopulation.hpp"
#include "function/path.hpp"
#include "strategy/solution.hpp"
#include "types.hpp"
#include "utils/hyperparameter.hpp"
#include "utils/input.hpp"

void PSOES(float toiu, int loop) {
    int showloop = 20;
    for (int i = 0; i < loop; ++i) {
        Mutation::est = Mutation::est + 0.7 / loop;
        toiu += 30.0 / loop;
        // if(i < loop/10) ES(toiu/10);
        if (i < loop / 4)
            algorithm::PSOmigrate();
        else if (i == loop / 4) {
            algorithm::saveExe();
        } else {
            algorithm::ES(toiu);
            algorithm::PSO();
            algorithm::updateBestPath();
        }
    }
}

/**
 * @brief Initializes the application, reads the map, sets up populations, runs algorithms (A*,
 * PSOES), and visualizes results.
 */
void solution1() {

    graph::markObstacle();
    // freopen("output.txt", "w", stdout);
    for (int i = 0; i < vtzy_types::numObstacle; ++i) {
        vtzy_types::point *p = vtzy_types::obstacles[i], *q = p->next;
        while (q != nullptr) {
            std::cout << p->x << " " << p->y << std::endl;
            p = q;
            q = q->next;
        }
        std::cout << p->x << " " << p->y << std::endl;
        q = vtzy_types::obstacles[i];
        std::cout << q->x << " " << q->y << std::endl;
    }
    // for (int i = 0; i < 1000; i+=10) {
    //     for (int j = 0; j < 1000; j+=10) {
    //         if (vtzy_types::mapGradient[i][j] == 0) {
    //             std::cout << "0";
    //         }
    //         else {
    //             std::cout << "1";
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    // GLFWwindow* window = OpenGLUI::initOpenGL();
    // if (!window) return;

    std::vector<std::future<void>> init_futures;
    for (int i = 0; i < 30; i++) {
        init_futures.push_back(std::async(std::launch::async, [i]() {
            auto tmp = std::make_unique<vtzy_types::point>(vtzy_types::start->x,
                                                           vtzy_types::start->y, nullptr);
            auto tmp1 = std::make_unique<vtzy_types::point>(vtzy_types::finish->x,
                                                            vtzy_types::finish->y, nullptr);
            vtzy_types::normalDirect[i] = init_population::initRandPath(tmp.get(), tmp1.get());
            vtzy_types::population[i] = new vtzy_types::path(tmp.release());
            vtzy_types::point* tmp2 = vtzy_types::population[i]->begin;
        }));
    }

    std::cout << "Initializing populations..." << std::endl;
    for (auto& f : init_futures)
        f.get();
    vtzy_types::numPopulations = 30;

    algorithm::aStar();
    vtzy_types::gPath = vtzy_types::astarRes;

    std::cout << "PSOES start" << std::endl;
    PSOES(60.0, 10000);
    std::cout << "PSOES done" << std::endl;
    algorithm::lastSocial();
    for (int i = 0; i < vtzy_types::numPopulations; i++) {
        if (i != 0) std::cout << -1 << std::endl;
        vtzy_types::point* tmp = vtzy_types::population[i]->begin;
        while (tmp != nullptr) {
            std::cout << tmp->x / 2 << " " << tmp->y / 2 << std::endl;
            tmp = tmp->next;
        }
    }
    std::cout << -2 << std::endl;
    std::cout << std::endl
              << "MOPSOES angle: " << vtzy_types::gPath->angle
              << " \t,distance: " << vtzy_types::gPath->distance << std::endl;
    path::pathFunc(vtzy_types::astarRes);

    // OpenGLUI::drawPathStrip(vtzy_types::gPath, line);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
}