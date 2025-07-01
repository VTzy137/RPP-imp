
#pragma once
#include "geometry/path.hpp"
#include "geometry/point.hpp"
#include <vector>
class Log
{
  private:
    static std::ofstream logFile;
    static bool isInitialized;

  public:
    static void initialize(int numLogger);
    static void log(const std::string& message);
    static void logLine(const std::string& message);
    static void close();
    static void logBoth(const std::string& message);
    static void logBothLine(const std::string& message);
    static void logPopulation(const std::string& message);
};