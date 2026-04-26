/**
 * 左右值及左右值引用
 * 左值(locator value):存储在内存中、有明确存储地址（可取地址）的数据
 * 右值(read value):可以提供数据值的数据（不可取地址）,右值又可分为纯右值和将亡值
 * 纯右值:非引用返回的临时变量、运算表达式产生的临时变量、原始字面量和 lambda 表达式等
 * 将亡值:与右值引用相关的表达式，比如，T&&类型函数的返回值、 move 的返回值等。
 * 右值引用:对一个右值进行引用的类型。因为右值是匿名的，所以我们只能通过引用的方式找到它。
 *      无论声明左值引用还是右值引用都必须立即进行初始化，因为引用类型本身并不拥有所绑定对象的内存，只是该对象的一个别名。
 *      通过右值引用的声明，该右值又“重获新生”，其生命周期与右值引用类型变量的生命周期一样，只要该变量还活着，该右值临时量将会一直存活下去。
 * T&&:三种含义
 *  ​右值引用​: T&&在非模板中 → 严格绑定右值
 *  万能引用: T&&在模板推导中 → 自动适配左值引用/右值引用
 *  转发引用​: 万能引用 + forward→ 完美转发。
 * move: 无条件返回右值引用,进而移动语义（转移资源所有权）
 * forward: 完美转发（泛型编程中的参数传递）, 保留实参原本的左值/右值类型，实现完美转发
 * 引用折叠（只记2条）：
 *  传左值 → T=int&  → T&& = int& && → 折叠为 int&
 *  传右值 → T=int   → T&& = int&&   → 保持右值引用
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;
template<typename T>
void target(T&& arg) {
    if constexpr (is_lvalue_reference_v<T>) {
        cout << "Lvalue: " << arg << endl;
    } else {
        cout << "Rvalue: " << arg << endl;
    }
}

template<typename T>
void relay(T&& arg)
{
    target(forward<T>(arg));
}

void funcCallA()
{
    //左值|右值|左值引用|右值引用
    int a = 10; // a为左值，10为右值
    int b = a; // a,b均为左值
    const char* c = "hello"; // c 和 "hello"均为左值，c++中字符串字面量有持久的内存存储且可以取地址
    int& d = a;
    // int& e = 10; //err
    int &&f = 10;
    // const char (&&g)[6] = "hello"; //err "hello"为左值 
}

void funcCallB()
{
    //万能引用​：T&&在模板推导中 → 自动适配左值引用/右值引用
    int a = 10;
    target(a);
    int& b = a;
    target(b);
    target(move(a));
    target(100);
    int&& c = 100;
    target(c); //c为具名变量
    const int d = 1000;
    target(d);
    const int& e = d;
    target(e);
    target(move(d));
}

void funcCallC()
{
    //move
    auto vec1 = make_unique<vector<int>>(initializer_list<int>{1, 2, 3});
    cout << "vec1 initial address: " << vec1.get() << endl; 
    auto vec2 = move(vec1);
    cout << "vec2 initial address: " << vec2.get() << endl; 
    if (vec1.get() == nullptr)
    {
        cout << "vec1 is nullptr, and vec1 address: " << vec1.get() << endl;

    }
    for (const auto& elem: *vec2)
    {
        cout << elem;
    }
}

void funcCallD()
{
    //forward
    relay(10);
    string a = "hello";
    relay(a);
    relay(move(a));
    const string b = "world";
    relay(b);
    const string&& c = move(b);
    relay(c);
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    // funcCallC();
    funcCallD();
    return 0;
}