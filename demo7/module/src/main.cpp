#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;
/*
*   可调用对象包装器
*   1、包装普通函数
*   2、包装普通静态函数
*   3、包装仿函数
*   4、包装转换为函数指针的对象
*/

void print(int num, string name)
{
    cout << "id:" << num <<  ", name:" << name << endl;
}
//函数指针
using funcptr = void(*)(int, string);

class Test
{
public:
    //重载仿函数
    void operator()(int id, string msg)
    {
        cout << "仿函数: " << "id:" << id << ", name" << msg << endl;    
    }
    //将类对象转换为函数指针
    operator funcptr()
    {
        cout << "operator funcptr" << endl;
        return print; 
    }

    static void print(int id, string name)
    {
        cout << "static void print" << endl;
        cout << "id:" << id <<  ", name:" << name << endl;
    }

    void msg(int id, string name)
    {
        cout << "id:" << id <<  ", name:" << name << endl;
    }
    int m_age = 30;
private:
};

class A
{
public:
    //构造函数时一个包装器对象
    A(const function<void(int, string)> & f):callback(f){}
    void notify(int id, string name)
    {
        callback(id, name);
    }
private:
    function<void(int, string)> callback;
};

int main(int argc, char * argv[])
{
    //1、包装普通函数
    std::function<void(int, string)> f1 = print;
    f1(27, "ynh");
    // 2、包装普通静态函数
    std::function<void(int, string)> f2 = Test::print;
    f2(28, "bmg");
    // 3、包装仿函数
    std::function<void(int, string)> f3 = Test();
    f3(29, "young");
    // 4、包装转换为函数指针的对象
    std::function<void(int, string)> f4 = Test();
    f2(30, "kohaku");
    cout << "---------回调--------" << endl;
    A(print).notify(27, "ynh");
    A(Test::print).notify(28, "bmg");
    A(Test()).notify(29, "young");
    A(Test()).notify(30, "kohaku");

    return 0;
}