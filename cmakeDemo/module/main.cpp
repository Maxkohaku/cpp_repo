#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "yLog.h"

int main(int argc, char *argv[])
{
    // Logger::createInstance().initLogConfig(DEBUG);
    int count = 10;
    while (count > 0)
    {
        logger(LogLevel::INFO) << std::string("hello world!"); 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        -- count;
    }
    return 0;
}