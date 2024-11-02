#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Vector.h"
#include "Search.h"
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

int main(int argc, char * argv[])
{
    test_search();
    return 0;
}