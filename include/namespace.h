#ifndef MY_PROJECT_H
#define MY_PROJECT_H

#include <iostream>

namespace MyProject {
    void greet();  // Function declaration
    class Logger {
    public:
        static void log(const std::string& message);
    };
}

#endif
