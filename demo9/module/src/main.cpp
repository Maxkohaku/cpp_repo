#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;

/**
 * @lambda表达式 
 * 1、表达式 [capture](params) opt -> ret {body;};
 * 2、捕获列表
 * [] - 不捕捉任何变量
 * [&] - 捕获外部作用域中所有变量, 并作为引用在函数体内使用 (按引用捕获)
 * [=] - 捕获外部作用域中所有变量, 并作为副本在函数体内使用 (按值捕获)
 * 拷贝的副本在匿名函数体内部是只读的
 * [=, &foo] - 按值捕获外部作用域中所有变量, 并按照引用捕获外部变量 foo 
 * [bar] - 按值捕获 bar 变量, 同时不捕获其他变量
 * [&bar] - 按引用捕获 bar 变量, 同时不捕获其他变量
 * [this] - 捕获当前类中的this指针
 * 让lambda表达式拥有和当前类成员函数同样的访问权限
 * 如果已经使用了 & 或者 =, 默认添加此选
 * 3、参数列表
 * 4、opt选项，可省略
 * mutable:可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）
 * exception:指定函数抛出的异常，如抛出整数类型的异常，可以使用throw();
 * 5、函数本质
 * lambda表达式的类型在C++11中会被看做是一个带operator()的类，即仿函数。
 * 按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。
 * mutable选项的作用就在于取消operator()的const属性。
 * 因为lambda表达式在C++中会被看做是一个仿函数，因此可以使用std::function和std::bind来存储和操作lambda表达式：
 * 对于没有捕获任何变量的lambda表达式，还可以转换成一个普通的函数指针：
 */

void funcT()
{
    int a = 10;
    cout << "before lambda a = " << a << endl;
    auto f = [&](int b) mutable {
        a *= 10;
        cout << "in lambda a = " << a << endl;
        return a + b;
    };
    f(1000);
    cout << "after lambda a = " << a << endl;
    
}

void funcT1()
{
    using ptr = void(*)(int);
    //对于没有捕获任何变量的lambda表达式，还可以转换成一个普通的函数指针：
    ptr p1 = [](int z) {
        cout << "z = " << z << endl;
    };
    p1(10);

    function<void(int)> f1 = [&](int z) {
        cout << "z = " << z << endl;
    };
    f1(100);

    function<void(int)> f2 = bind([=](int z) {
        cout << "z = " << z << endl;
    }, placeholders::_1);
    f2(1000);
    
}

int main(int argc, char * argv[])
{
    // funcT();
    funcT1();
    return 0;
}