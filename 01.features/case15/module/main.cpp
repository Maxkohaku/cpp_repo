#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
//继承 + 多态 + 虚函数 + 虚析构 + 虚表(vtable) + 虚指针(vptr)
/**
 * 1. 继承：子类复用父类成员与方法
 * 2. 虚函数：基类加 virtual，运行时动态绑定，实现多态
 * 3. 多态三要素：公有继承 + 基类虚函数 + 父类指针/引用指向子类
 * 4. 虚析构：基类析构必须 virtual，delete基类指针时完整析构子类，避免内存泄漏
 * 5. 虚函数表(vtable)：拥有虚函数的类，全局只读结构体，存储虚函数地址
 * 6. 虚指针(vptr)：对象内存最开头隐藏指针，指向当前类的虚函数表
 * 7. 动态绑定和运行时多态 :加了 virtual 的函数会存入虚函数表；对象自带虚指针 (vptr)，运行时根据真实对象类型，通过 vptr 寻址、虚表偏移找到对应函数地址，
 *    完成动态绑定，从而实现运行时多态。基类析构函数加 virtual，是为了让析构也进入虚表，delete 基类指针时走动态绑定，先析子类、再析父类，
 *    实现完整安全销毁，避免内存泄漏。
 */
class Base
{
public:
    virtual void func1() { cout << "Base::func1\n"; }
    virtual void func2() { cout << "Base::func2\n"; }
    // 虚析构 必写
    virtual ~Base() { cout << "Base::~Base\n"; }
};

// 子类公有继承 + 重写虚函数
class Derived : public Base
{
public:
    // override 强制检查重写合法性
    void func1() override { cout << "Derived::func1\n"; }
    ~Derived() override { cout << "Derived::~Derived\n"; }
};

int main(int argc, char *argv[])
{
    return 0;
}