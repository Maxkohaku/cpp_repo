#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Vector.h"
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
int main(int argc, char * argv[])
{
    test_vec();
    return 0;
}