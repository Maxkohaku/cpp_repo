#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

void process(int arg)
{
   cout << "arg is " << arg << endl;
}

void process(const char* arg)
{
   cout << "arg is " << (arg ? arg : "nullptr") << endl;
}

void process(std::nullptr_t)
{
   cout << "arg is nullptr" << endl;
}

void funcCallA()
{
    process(0);
    //process(NULL); //err NULL本质是一个定义为(void*)0​的宏，从而导致函数重载时产生歧义
    process(nullptr);
}

int main(int argc, char *argv[])
{
    funcCallA();
    return 0;
}