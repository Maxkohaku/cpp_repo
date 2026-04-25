#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "ynhLog.h"
using namespace std;


int main(int argc, char * argv[])
{
    Logger::instance().setLogLevel(INFO);
    size_t  counter = 10;
    while (counter--){
        logger(INFO) << string("hello wolrd!");
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return 0;
}