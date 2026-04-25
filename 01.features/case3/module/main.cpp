/**
 *  可调用对象
 *  1、函数指针
 *  2、具有operator()成员函数的类对象(仿函数)
 *  3、可被转换为函数指针的类对象
 *  4、类成员函数指针或类成员指针
 */
#include <iostream>
#include <string>
using namespace std;

using funcptr = void(*)(std::string, size_t);
void show(std::string name, size_t age)
{
    cout << "name:" << name << "|age:" << age << endl;
}

class Person
{
private:
    std::string _name;
    size_t _age;
public:
    Person() {}
    Person(std::string name, size_t age) : _name(name), _age(age) {}
    const std::string name() const
    {
        return _name;
    }
    const size_t age() const
    {
        return _age;
    }
    //重载仿函数
    void operator()()
    {
        cout << "[call_func]| Person::operator() << endl";
        cout << "name:" << _name << "|age:" << _age << endl;
    }
    //将类对象转化为函数指针
    operator funcptr()
    {
        cout << "[call_func]| Person::operator funcptr()" << endl;
        return static_show;
    }
    static void static_show(std::string name, size_t age)
    {
        cout << "[call_func]| Person::static static_show" << endl;
        cout << "name:" << name << "|age:" << age << endl;  
    }
    void show(std::string name, size_t age)
    {
        cout << "[call_func]| Person:: show" << endl;
        cout << "name:" << name << "|age:" << age << endl;  
    }
    friend void funcCallE();
};

//1、函数指针
void funcCallA()
{
    funcptr funcA = show;
    funcA("ynh", 28);
}

//2、具有operator()成员函数的类对象(仿函数)
void funcCallB()
{
    Person p("ynh", 28);
    p();
}

//3、可被转换为函数指针的类对象
void funcCallC()
{
    Person p("ynh", 28);
    funcptr fp = static_cast<funcptr>(p);
    fp(p.name(), p.age());
}

//4、类成员函数指针
void funcCallD()
{
    funcptr func1 = &Person::static_show;
    (*func1)("ynh", 28);

    using funcptrTest = void(Person::*)(std::string, size_t);
    Person p;
    funcptrTest func2 = &Person::show;
    (p.*func2)("ynh", 28);
}

//类成员指针
void funcCallE()
{
    using argptr1 = std::string Person::*;
    using argptr2 = size_t Person::*;
    argptr1 p1 = &Person::_name;
    argptr2 p2 = &Person::_age;
    Person p("ynh", 28);
    cout << "name:" << p.*p1 << "|age:" << p.*p2  << endl;
}

int main(int argc, char *argv[])
{
    funcCallA();
    funcCallB();
    funcCallC();
    funcCallD();
    funcCallE();
    return 0;
}