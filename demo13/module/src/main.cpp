#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Sort.hpp"
#include "Common.hpp"
using namespace VectorSort;

void sortTest()
{
    auto vecObj = std::make_shared<std::vector<int>>(std::initializer_list<int>{9, 7, 3, 5, 2, 8, 6, 4, 1});
    VectorSorter<int> vecSort(vecObj);
    // vecSort.bubbleSort();
    // vecSort.selectionSort();
    // vecSort.insertionSort();
    // vecSort.selectionSort();
    // vecSort.quickSort();
    // vecSort.mergeSort();
    vecSort.heapSort();
    for(const auto& val: *vecObj)
    {
        LOG_INFO(val);
    }
}


int main(int argc, char * argv[])
{
    sortTest();
    return 0;
}