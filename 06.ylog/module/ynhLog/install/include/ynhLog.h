#ifndef _YNH_LOG_H_
#define _YNH_LOG_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <map>
#include <memory>
#include <chrono>
#include <iomanip>
#include <ctime>

enum LogLevel
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:
    void setOutputFile(const std::string& filename);
    void setLogLevel(LogLevel level);
    static Logger& instance();

    class LogStream
    {
    public:
        LogStream(Logger& logger, LogLevel level):logger_(logger),level_(level) {}
        template <typename T>
        LogStream& operator<<(const T& value);

        ~LogStream()
        {
            logger_.log(level_, stream_.str());
        }
    private:
        Logger& logger_;
        LogLevel level_;
        std::ostringstream stream_;
    };
    
    LogStream operator()(LogLevel level);

private:
    LogLevel level_;
    std::unique_ptr<std::ofstream> fileStream_;
    std::mutex mutex_;

    Logger():level_(INFO) {}
    void log(LogLevel level, const std::string& message);
    std::string getCurrentTimestamp() const;
    std::string levelToString(LogLevel level) const;
};
template <typename T>
Logger::LogStream& Logger::LogStream::operator<<(const T& value)
{
    stream_ << value;
    return *this;
}
#define logger(level) Logger::instance()(level)
#endif /*_YNH_LOG_H_*/