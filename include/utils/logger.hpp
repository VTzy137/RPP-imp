#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Logger
{
  private:
    static std::ofstream logFile;
    static bool isInitialized;

  public:
    static void initialize(const std::string& logFilePath);
    static void log(const std::string& message);
    static void logLine(const std::string& message);
    static void close();

    // Convenience function to log to both console and file
    static void logBoth(const std::string& message);
    static void logBothLine(const std::string& message);
};