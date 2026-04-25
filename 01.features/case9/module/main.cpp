/**
 * 类型推导
 * auto
 * decltype
 * decltype(auto)
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
template <typename T>
void printType(const T& arg)
{
    cout << "decltype(arg) is: " << typeid(decltype(arg)).name() << endl;
}

template <typename T>
void printType()
{
    cout << "T type is " << typeid(T).name() << endl;
}

void funcCallA()
{
    //decltype
    int a = 10; 
    printType(a);
    bool b = true; 
    printType(b);
    const char *c = "hello";
    printType(c);
    std::string d = "hello"; 
    printType(d);

}

void funcCallB()
{
    //auto
    auto a = 10;
    printType<decltype(a)>();
    auto b = "hello";
    printType<decltype(b)>();
    const auto c = true;
    printType<decltype(c)>();
}

void funcCallC()
{
    //decltype(auto)
    int a = 10;
    int& b = a;
    const int c = 20;
    int&& d = 10;

    decltype(auto) x1 = a;   // x1 是 _____ int
    decltype(auto) x2 = b;   // x2 是 _____ int&
    decltype(auto) x3 = c;   // x3 是 _____ const int
    decltype(auto) x4 = (a); // x4 是 _____ int&  (a)为左值表达式，返回其引用
}

int main(int argc, char *argv[])
{
    // funcCallA();
    //funcCallB();
    // funcCallC();
    return 0;
}