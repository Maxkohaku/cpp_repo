#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Sort.hpp"
#include "Common.hpp"
using namespace VectorSort;
int main(int argc, char * argv[])
{
    auto vecObj = std::make_shared<std::vector<int>>(std::initializer_list<int>{3, 5, 8, 6, 4, 1});
    VectorSorter<int> vecSort(vecObj);
    vecSort.bubbleSort();
    for(const auto& val: *vecObj)
    {
        LOG_INFO(val);
    }
    return 0;
}