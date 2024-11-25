#ifndef _YNH_LOG_HPP
#define _YNH_LOG_HPP
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
    void setOutputFile(const std::string& filename)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (filename.empty())
        {
            fileStream_.reset();
        }
        else
        {
            fileStream_ = std::make_unique<std::ofstream>(filename, std::ios::app);
        }
    }

    void setLogLevel(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        level_ = level;
    }

    static Logger& instance()
    {
        static Logger logger;
        return logger;
    }

    class LogStream
    {
    public:
        LogStream(Logger& logger, LogLevel level):logger_(logger),level_(level) {}
        template <typename T>
        LogStream& operator<<(const T& value)
        {
            stream_ << value;
            return *this;
        }

        ~LogStream()
        {
            logger_.log(level_, stream_.str());
        }
    private:
        Logger& logger_;
        LogLevel level_;
        std::ostringstream stream_;
    };
    
    LogStream operator()(LogLevel level)
    {
        return LogStream(*this, level);
    }

private:
    LogLevel level_;
    std::unique_ptr<std::ofstream> fileStream_;
    std::mutex mutex_;

    Logger():level_(INFO) {}
    void log(LogLevel level, const std::string& message)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if(level >= level_)
        {
            const auto& timestamp = getCurrentTimestamp();
            const auto output = timestamp + " [" + levelToString(level) + "]|" + message + "\n";
            if (fileStream_ && fileStream_->is_open())
            {
                *fileStream_ << output;
                fileStream_->flush();
            }
            else
            {
                std::cout << output;
                std::cout.flush();
            }
        }
    }

    std::string getCurrentTimestamp() const
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << millis.count();
        return oss.str();
    }

    std::string levelToString(LogLevel level) const
    {
        static const std::map<LogLevel, std::string> levelMap = {{DEBUG, "DEBUG"}, {INFO, "INFO"}, {WARNING, "WARNING"}, {ERROR, "ERROR"}};
        return levelMap.at(level);
    }
};
#define logger(level) Logger::instance()(level)
#endif /*_YNH_LOG_HPP*/