#include <fstream>
#include <iostream>
#include <string>
#include <utils/log.hpp>

std::ofstream Log::logFile;
bool Log::isInitialized = false;

void Log::initialize(int numLogger)
{
    const std::string configPath = std::string(ASSET_PATH) + "/";
    const std::string logFilePath = configPath + "log/log" + std::to_string(numLogger) + ".txt";

    Log::logBothLine("Log file: " + logFilePath);
    if (isInitialized)
    {
        logFile.close();
    }

    logFile.open(logFilePath);
    isInitialized = true;

    if (logFile.is_open())
    {
        logBothLine("Log initialized: " + logFilePath);
    }
    else
    {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
    }
}

void Log::log(const std::string& message)
{
    if (isInitialized && logFile.is_open())
    {
        logFile << message;
        logFile.flush();
    }
}

void Log::logLine(const std::string& message)
{
    log(message + "\n");
}

void Log::logBoth(const std::string& message)
{
    // std::cout << message;
    log(message);
}

void Log::logBothLine(const std::string& message)
{
    logBoth(message + "\n");
}

void Log::close()
{
    if (isInitialized && logFile.is_open())
    {
        logBothLine("Log closing...");
        logFile.close();
        isInitialized = false;
    }
}

void Log::logPopulation(const std::string& message)
{
    for (int individual = 0; individual < Path::population.size(); individual++)
    {
        if (individual != 0)
        {
            logLine("-1");
        }
        Point* tmp = Path::population[individual]->begin;
        while (tmp != nullptr)
        {
            logLine(std::to_string(tmp->x / 2) + " " + std::to_string(tmp->y / 2));
            tmp = tmp->nextPoint;
        }
    }
}