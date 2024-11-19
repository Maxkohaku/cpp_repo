#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Vector.hpp"
#include "Search.h"
#include "Sort.hpp"
#include "Stack.hpp"
#include "Point.hpp"
using namespace std;
void test_vec()
{
    Vector<int> vec;
    for(int i = 0; i < 30; ++i)
    {
        vec.append(i);
    }
    vec.show();
    cout << "Vec size = " << vec.size() << endl;
    cout << "find pos = " << vec.find(15) << endl;
}

void test_search()
{
    Vector<int> vec;
    for(int i = 0; i < 100; ++i)
    {
        vec.append(i);
    }
    int pos = binarySearchNorecursive(vec, 66);
    cout << "Norecursive vec[" << pos << "] = " << vec[pos] << endl;
    pos = binarySearchRecursive(vec, 0, vec.size() - 1, 66);
    cout << "Recursive vec[" << pos << "] = " << vec[pos] << endl;
}

void test_sort()
{
    Vector<Point> vec;
    Point p1(5,5);
    Point p2(3,7);
    Point p3(4,6);
    Point p4(9,1);
    Point p5(2,8);
    Point p6(3,6);
    Point p7(4,5);
    Point p8(2,11);
    vec.append(p1);
    vec.append(p2);
    vec.append(p3);
    vec.append(p4);
    vec.append(p5);
    vec.append(p6);
    vec.append(p7);
    vec.append(p8);
    cout << "排序前:" << endl;
    for(int i = 0; i < vec.size(); ++i)
    {
        vec[i].show();
    }
    // auto pointCom = function<bool(const Point& a, const Point& b)>([](const Point& a, const Point& b){
    //     return (a.m_x * a.m_y >= b.m_x * b.m_y);
    // });
    bubbleSort(vec);
    // selectionSort(vec);
    // insertionSort(vec);
    // shellSort(vec);
    // quickSort(vec, 0, vec.size() - 1);
    // mergeSort(vec, 0, vec.size() - 1);
    // heapSort(vec);
    cout << "排序后:" << endl;
    for(int i = 0; i < vec.size(); ++i)
    {
        vec[i].show();
    }
}

void test_stack()
{
    Stack<int> stack;
    for(int i = 0; i < 10; ++i)
    {
        stack.push(i);
    }
    for(int i = 0; i < 10; ++i)
    {
        cout  << stack.peek() << " ";
    }
    cout << endl;
    for(int i = 0; i < 10; ++i)
    {
        cout << stack.pop() << " ";
    }
    cout << endl;
}

int main(int argc, char * argv[])
{
    test_sort();
    return 0;
}