#include "ynhLog.h"

void Logger::setOutputFile(const std::string& filename)
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

void Logger::setLogLevel(LogLevel level)
{
    std::lock_guard<std::mutex> lock(mutex_);
    level_ = level;
}

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::LogStream Logger::operator()(LogLevel level)
{
    return LogStream(*this, level);
}

void Logger::log(LogLevel level, const std::string& message)
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

std::string Logger::getCurrentTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << millis.count();
    return oss.str();
}

std::string Logger::levelToString(LogLevel level) const
{
    static const std::map<LogLevel, std::string> levelMap = {
        {DEBUG, "DEBUG"}, 
        {INFO, "INFO"}, 
        {WARNING, "WARNING"}, 
        {ERROR, "ERROR"}};
    return levelMap.at(level);
}
