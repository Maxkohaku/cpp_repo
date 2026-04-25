/**
 * 可调用对象包装器
 * 1、包装普通函数
 * 2、包装静态函数
 * 3、包装仿函数
 * 4、包装转换为函数指针的对象
 */
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using funcptr = void(*)(std::string, size_t);
void show(std::string name, size_t age)
{
    cout << "name:" << name << "|age:" << age;
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
        cout << "[call_func]| Person::operator()" << endl;
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
void funcCallA()
{
    //包装普通函数
    std::function<void(std::string, size_t)> func = show;
    func("ynh", 28);
}

void funcCallB()
{
    //包装静态函数
    std::function<void(std::string, size_t)> func = Person::static_show;
    func("ynh", 28);
}

void funcCallC()
{
    //包装仿函数
    std::function<void()> func = Person("ynh", 28);
    func();
}

void funcCallD()
{
    //包装转换为函数指针的对象
    std::function<void(std::string, size_t)> func = static_cast<funcptr>(Person("ynh", 28));
    func("ynh", 28);
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    // funcCallC();
    funcCallD();
    return 0;
}
