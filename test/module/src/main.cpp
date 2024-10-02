#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
int main(int argc, char * argv[])
{
    size_t  counter = 10;
    while (counter--){
        cout << string("hello wolrd!") << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}