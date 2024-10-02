#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "logger.h"
using namespace std;
using callbackptr = void(*)(size_t);
Logger logger("./app.log");
class EventHandler
{
public: 
    EventHandler(size_t counter = 10):m_counter(counter){;}
    ~EventHandler() = default;
    void register_callback(callbackptr cb)
    {
        logger.log("register_callback");
        m_callback = cb;
    }
    void trigger_event()
    {
        logger.log("trigger cb");
        if(m_callback)
        {
            logger.log("m_callback");
            m_callback(m_counter);
        }
    }
    static EventHandler& getEventHandler();
private:
    callbackptr m_callback;
    size_t m_counter;
};
EventHandler& EventHandler::getEventHandler()
{
    static EventHandler m_eventHandler;
    return  m_eventHandler;
}
void my_callback(size_t counter)
{
    while (counter--){
        logger.log(string("hello wolrd!")); 
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}
int main(int argc, char * argv[])
{

    auto instance = EventHandler().getEventHandler();
    instance.register_callback(my_callback);
    int time = 3;
    logger.log("wait for cb");
    while(time--)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    thread th(&EventHandler::trigger_event, &instance);
    th.join();
}