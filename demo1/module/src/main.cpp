#include <chrono>
#include <thread>
#include "logger.h"

int main(int argc, char ** argv)
{
    Logger logger("./app.log");
    while (true)
    {
        logger.log("hello world!");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    return 0;
}