#include "utils/logger.hpp"

std::ofstream Logger::logFile;
bool Logger::isInitialized = false;

void Logger::initialize(const std::string& logFilePath)
{
    if (isInitialized)
    {
        logFile.close();
    }

    logFile.open(logFilePath);
    isInitialized = true;

    if (logFile.is_open())
    {
        logBothLine("Logger initialized: " + logFilePath);
    }
    else
    {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
    }
}

void Logger::log(const std::string& message)
{
    if (isInitialized && logFile.is_open())
    {
        logFile << message;
        logFile.flush();
    }
}

void Logger::logLine(const std::string& message)
{
    log(message + "\n");
}

void Logger::logBoth(const std::string& message)
{
    // std::cout << message;
    log(message);
}

void Logger::logBothLine(const std::string& message)
{
    logBoth(message + "\n");
}

void Logger::close()
{
    if (isInitialized && logFile.is_open())
    {
        logBothLine("Logger closing...");
        logFile.close();
        isInitialized = false;
    }
}