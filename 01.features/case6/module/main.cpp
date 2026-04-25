/**
 * @lambda表达式
 * 1、表达式    [capture](params) opt -> ret {body;};
 * 2、捕获列表  [capture]
 * [ ] - 不捕获任何变量
 * [&] - 捕获外部作用域中所有变量，并作为引用在函数体内使用(按引用捕获)
 * [=] - 捕获外部作用域中所有变量，并作为副本在函数体内使用(按值捕获)
 *       拷贝的副本在匿名函数体内部是只读的
 * [=, &foo] - 按值捕获外部作用域中的所有变量，并按引用捕获外部变量 foo
 * [bar] - 按值捕获变量 bar，同时不捕获其它变量
 * [&bar] - 按引用捕获变量 bar，同时不捕获其它变量
 * [this] - 捕获当前类中的this指针
 *          让lambda表达式拥有和当前类成员函数相同的访问权限
 *          如果已经使用了 & 或者 = ，默认添加此项
 * 3、参数列表 (params)
 * 4、可选项 opt
 * mutable: 可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）
 * exception:指定函数抛出的异常，如抛出整数类型的异常，可以使用throw();
 * 5、函数本质
 * lambda表达式的类型在C++11中会被看做是一个带operator()的类，即仿函数。
 * 按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。
 * mutable选项的作用就在于取消operator()的const属性。
 * 因为lambda表达式在C++中会被看做是一个仿函数，因此可以使用std::function和std::bind来存储和操作lambda表达式：
 * 对于没有捕获任何变量的lambda表达式，还可以转换成一个普通的函数指针：
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;

class Person
{
public:
    Person(std::string name, size_t age) : _name(name), _age(age) {}

    void show()
    {
        [this]() {
            
            cout << "[showLambda]|name:" << _name << "|age:" << _age << endl;
        }();
    }

    void changAge(size_t age)
    {
        [this, age](){
            _age = age;
        }();
    }

    std::function<void()> showInLambda = [this]() {
        
        cout << "[showInLambda]|name:" << _name << "|age:" << _age << endl;
    };

private:
    std::string _name;
    size_t _age;
};

void funcCallA()
{
    //直接定义并调用
    std::string name("ynh");
    size_t age(28);

    [=]()mutable{
        age = 18;
        cout << "[= in lambda]|name:" << name << "|age:" << age << endl;
    }();
    cout << "[= after change ]name:" << name << "|age:" << age << endl;

    [&](){
        age = 10;
        cout << "[& in lambda]|name:" << name << "|age:" << age << endl;
    }();
    cout << "[& after change ]name:" << name << "|age:" << age << endl;
}

void funcCallB()
{
    //使用auto自动推导和函数包装器定义
    std::string name("ynh");
    size_t age(28);

    std::function<void()> func1 = [=]()mutable{
        age = 18;
        cout << "[= in lambda]|name:" << name << "|age:" << age << endl;
    };
    func1();
    cout << "[= after change ]name:" << name << "|age:" << age << endl;

    auto func2 = [&](){
        age = 10;
        cout << "[& in lambda]|name:" << name << "|age:" << age << endl;
    };
    func2();
    cout << "[& after change ]name:" << name << "|age:" << age << endl;
}

void funcCallC()
{
    //通过this捕获类成员
    Person p("ynh", 28);
    p.show();
    p.changAge(18);
    p.showInLambda();
}

void funcCallD()
{
    //对于没有捕获任何变量的lambda表达式，还可以转换成一个普通的函数指针,这种用法主要是为了兼容 C 风格 API 或旧接口
    using ptr = void(*)(int);
    ptr p1 = [](int a) {
        cout << "a=" << a << endl;
    };
    p1(100);
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    // funcCallC();
    funcCallD();
    return 0;
}