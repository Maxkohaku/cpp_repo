#include <iostream>
#include <string>
#include <chrono>
#include <thread>
// const
/**
 * 1. 修饰普通变量 → 只读常量
 * 2. 修饰指针: 左定值，右定向
 * 3. 修饰函数形参: 不修改实参 + 避免拷贝
 * 4. 修饰成员函数（类里必用）承诺不修改成员变量
 */
void testFunc()
{
    int val1 = 10;
    int val2 = 20;
    const int* p1 = &val1;
    p1 = &val2;
    // *p1 = val2; 
    int* const p2 = &val1; 
    // p2 = &val2;
    *p2 = val2;
}

int main(int argc, char *argv[])
{
    testFunc();
    return 0;
}