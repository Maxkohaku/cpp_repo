/**
 * for循环
 * for_each循环 for_each(容器.begin(), 容器.end(), 函数或函数对象);
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;
void funcCallA(const vector<int>& vec)
{
    // for循环-传统
    cout << "for循环-传统" << endl;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    
}
void funcCallB(const vector<int>& vec)
{
    //for循环-迭代器
    cout << "for循环-迭代器";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void funcCallC(const vector<int>& vec)
{
    //for循环-C++11
    cout << "for循环-C++11";
    for (const auto& num : vec)
    {
        cout << num << " ";
    }
    cout << endl;
}

void funcCallD(const vector<int>& vec)
{
    //for_each循环
    cout << "for_each循环";
    for_each(vec.begin(), vec.end(), [](int num) {
        cout << num << " ";
    });
    cout << endl;
}
int main(int argc, char *argv[])
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    funcCallA(vec);
    funcCallB(vec);
    funcCallC(vec);
    funcCallD(vec);
    return 0;
}