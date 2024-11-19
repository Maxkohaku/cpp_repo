#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <string>
#include <mutex>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    // Log a message with timestamp
    void log(const std::string& message);
private:
    std::ofstream logFile;
    std::mutex mutex_;
    // Get current timestamp in the format YYYY-MM-DD-HH:MM:SS:SSS
    std::string getCurrentTime();
};

#endif /*_LOGGER_H_*/
