#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;
/*
*   可调用对象绑定器
*   1、将可调用对象和其参数绑定成一个仿函数
*   2、将多元（n>1）可调用对象转换为一元或(n-1)元可调用对象，即只绑定部分参数
*   绑定非类成员函数/变量
*   auto f = std::bind(可调用对象地址, 绑定的参数/占位符)
*   绑定类成员函数/变量
*   auto f = std::bind(类函数/成员地址, 类实例对象地址, 绑定的参数/占位符)
*/

void testFunc(int x, int y, const function<void(int, int)>& func)
{
    func(x, y);
  
}

void output(int x, int y)
{
    cout << "x + y = " << (x + y) << endl;
}

class Test
{
public:
    void output(int x, int y)
    {
        cout << "x = " << x  << ", y = " << y << endl;
    }
    int m_num = 100;
};

int main(int argc, char * argv[])
{   
    //使用绑定器将可调用对象和其参数绑定成一个仿函数
    cout << "----------绑定非类成员函数/变量----------" << endl;
    
    bind(output, 1, 1)();
    bind(output, placeholders::_1, 1)(2);
    auto f1 = bind(output, placeholders::_1, placeholders::_2);
    f1(3, 1);
    cout << "--------------------" << endl;
    for(int i = 0; i < 10; ++i)
    {
        testFunc(i, i, f1);
    }
    cout << "--------------------" << endl;
    for(int i = 0; i < 10; ++i)
    {
        auto f2 = bind(output, i + 100, i);
        testFunc(i, i, f2);
    }

    cout << "----------绑定类成员函数/变量----------" << endl;
    Test t;
    auto f3 = bind(&Test::output, &t, placeholders::_1, placeholders::_2);
    function<void(int, int)> f33 = bind(&Test::output, &t, placeholders::_1, placeholders::_2);
    f3(1, 2);
    f33(2, 1);

    auto f4 = bind(&Test::m_num, &t);
    //function<const int&(void)> f44 = bind(&Test::m_num, &t);
    function<int&(void)> f44 = bind(&Test::m_num, &t);
    f4() = 666;
    cout << "f4()=" << f4() << endl;
    cout << "f44()=" << f44() << endl;
    f44() = 999;
    cout << "f4()=" << f4() << endl;
    cout << "f44()=" << f44() << endl;
    return 0;
}