/**
 * 可调用对象绑定器
 * 1、将可调用对象和其参数绑定成一个仿函数
 * 2、将多元(n>1)可调用对象转化为一元或(n-1)元可调用对象，即只绑定部分参数
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;
void show(string name, size_t age)
{
    cout << "[call_func]|show" << endl;
    cout << "name:" << name << "|age:" << age << endl;
}

class Person
{
public:
    Person() {}
    Person(string name, size_t age) : _name(name), _age(age) {}
    void show(string name, size_t age)
    {
        cout << "[call_func]|Shower::show" << endl;
        cout << "name:" << name << "|age:" << age << endl;
    }  
    size_t _age; 
private:
    string _name;
};

void funcCallA()
{
    //使用绑定器将可调用对象和其参数绑定成一个仿函数
    bind(show, "ynh", 28)();
    bind(show, placeholders::_1, 28)("kohaku");
    bind(show, placeholders::_1, placeholders::_2)("bmg", 27);
}

void funcCallB()
{
    //绑定非类成员函数/变量     auto f = bind(可调用对象地址, 绑定的参数/占位符)
    auto func1 = bind(show, "ynh", 28);
    func1();
    auto func2 =  bind(show, placeholders::_1, 28);
    func2("kohaku");
    auto func3 = bind(show, placeholders::_1, placeholders::_2);
    func3("bmg", 27);
}

void funcCallC()
{
    //绑定类成员函数/变量    auto f = bind(类函数/成员地址, 类实例对象地址, 绑定的参数/占位符)
    Person p;
    auto func1 = bind(&Person::show, &p, "ynh", 28);
    func1();
    auto func2 = bind(&Person::show, &p, placeholders::_1, 28);
    func2("kohaku");
    auto func3 = bind(&Person::show, &p, placeholders::_1, placeholders::_2);
    func3("bmg", 27);

    auto func4 = bind(&Person::_age, &p);
    cout << "func4() = " << func4() << endl;
    func4() = 10;
    function<size_t(void)> func44 = bind(&Person::_age, &p);
    cout << "func44() = " << func44() << endl;
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    funcCallC();
    return 0;
}