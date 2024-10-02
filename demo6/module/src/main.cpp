#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
/*
*   可调用对象
*   1、函数指针
*   2、具有operator()成员函数的类对象(仿函数)
*   3、可被转换为函数指针的类对象
*   4、类成员函数指针或类成员指针
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
    void operator()(string msg)
    {
        cout << "仿函数: " << msg << endl;    
    }
    //将类对象转换为函数指针
    operator funcptr()
    {
        cout << "operator funcptr" << endl;
        return print; 
    }

    static void print(int id, string name)
    {
        cout << "id:" << id <<  ", name:" << name << endl;
    }

    void msg(int id, string name)
    {
        cout << "id:" << id <<  ", name:" << name << endl;
    }
    int m_age = 30;
private:
};

int main(int argc, char * argv[])
{
    Test()("ynh");      //仿函数
    Test()(27, "ynh");  //将类对象转换为函数指针
    //类的函数指针
    funcptr f1 = &Test::print;
    (*f1)(28, "kohaku");
    using testFuncptr = void(Test::*)(int, string);
    testFuncptr f2 = &Test::msg;
    //类的成员指针
    using ptr1 = int Test::*;
    ptr1 p1 = &Test::m_age;
    (Test().*f2)(27, "ynh");
    cout << "p1.id:" << (Test().*p1) << endl;
    return 0;
}