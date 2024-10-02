#include "logger.h"

Logger::Logger(const std::string& filename) 
    : logFile(filename, std::ios::app) {
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message) 
{
    std::lock_guard<std::mutex> lock(mutex_);
    logFile << getCurrentTime() << " " << message << std::endl;
}

std::string Logger::getCurrentTime() 
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    auto millis = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << millis.count();

    return oss.str();
}