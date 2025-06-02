#pragma once
#include <fstream>
#include <iostream>
#include <string>
class Input
{
  private:
    static std::ofstream logFile;
    static bool isInitialized;

  public:
    static void readMap(int numInput);
    static void initialize(int numLogger);
    static void log(const std::string& message);
    static void logLine(const std::string& message);
    static void close();
    static void logBoth(const std::string& message);
    static void logBothLine(const std::string& message);
};
