/**
 * 1. unique_ptr：独占所有权，禁止拷贝、支持move，RAII自动释放，性能最优
 * 2. shared_ptr：双计数器(强计数/弱计数)，强计数管理对象生命周期，支持共享拷贝
 * 3. weak_ptr：弱引用，不增加强计数，用于观测对象、解决shared_ptr循环引用内存泄漏
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
using namespace std;
#include <iostream>
#include <memory>
using namespace std;

struct TestObj
{
    TestObj()  { cout << "TestObj 构造\n"; }
    ~TestObj() { cout << "TestObj 析构\n"; }
};

struct B;

struct A
{
    // shared_ptr 会增加强计数
    weak_ptr<B> b_ptr;
    ~A() { cout << "A 析构\n"; }
};

struct B
{
    // 弱引用：不增加强引用计数
    weak_ptr<A> a_ptr;
    ~B() { cout << "B 析构\n"; }
};

void funcCallA()
{
    // 独占式智能指针
    unique_ptr<TestObj> p1 = make_unique<TestObj>();

    // ❶ 禁止拷贝编译报错
    // unique_ptr<TestObj> p2 = p1;

    // ❷ 只允许 move 转移所有权
    unique_ptr<TestObj> p3 = move(p1);

    // p1 已悬空
    if (!p1)
    {
        cout << "p1 失去所有权\n";
    }

    // 出作用域 p3 自动析构释放对象
}

void funcCallB()
{
    // 强引用计数：strong_count
    shared_ptr<TestObj> s1 = make_shared<TestObj>();
    cout << "s1 计数: " << s1.use_count() << endl;

    // 拷贝共享，计数+1
    shared_ptr<TestObj> s2 = s1;
    cout << "s1 计数: " << s1.use_count() << endl;

    // 手动释放当前引用，计数-1
    s2.reset();
    cout << "s1 计数: " << s1.use_count() << endl;

    // ❶ 强计数为0 → 对象销毁
    // ❷ 强计数+弱计数都为0 → 控制块销毁
}

void funcCallC()
{
    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();

    // 互相弱引用，不会造成强计数循环卡死
    a->b_ptr = b;
    b->a_ptr = a;

    // lock()：安全提升为 shared_ptr
    if (auto tmp = a->b_ptr.lock())
    {
        cout << "对象有效\n";
    }

    // 出作用域：强引用全部销毁，无内存泄漏
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    // funcCallC();
    return 0;
}