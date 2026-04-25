#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
// #include <stdexcept>

class MyException:public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Occurred My Exception!";
    }
};

int devideA(int a, int b)
{
    if (b == 0)
    {
        throw std::invalid_argument("Cannot be devideA by Zero !");
    }
    return a / b;
}

int devideB(int a, int b)
{
    if (b == 0)
    {
        throw MyException();
    }
    return a / b;
}

void funcCallA()
{
    //throw
   cout << devideA(100, 1) << endl;
   cout << devideA(100, 0) << endl;
}

void funcCallB()
{
    //try...catch标准异常捕获 
    try 
    {
       cout << devideA(100, 0);
    }
    catch (const std::invalid_argument& e)
    {
       cout << "标准异常捕获 invalid_argument:" << e.what() << endl;
    }
    catch(const MyException& e)
    {
       cout << "自定义标准异常捕获" << e.what() << '\n' << endl;
    }
    catch (const std::exception& e)
    {
       cout << "标准异常捕获 exception:" << e.what()  << endl;
    }
}

void funcCallC()
{
    //try...catch自定义异常捕获
    try
    {
       cout << devideB(100, 0);
    }
    catch(const MyException& e)
    {
       cout << "自定义异常捕获:" << e.what();
    }
    catch(const std::exception& e)
    {
       cout << "标准异常捕获:" << e.what();
    }
    
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    funcCallC();
    return 0;
}