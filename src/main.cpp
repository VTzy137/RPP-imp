#include <iostream>
#include <utility>
#include <vector>

#include "UI/openGl.h"
#include "app.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    runApp();
    std::vector<std::pair<int, int>> line = {
        {50, 50}, {100, 150}, {200, 100}, {300, 300}, {400, 250}};
    OpenGLUI::drawLineStrip(line, 640, 480);
    return 0;
}