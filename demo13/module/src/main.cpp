#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Sort.hpp"
#include "Search.hpp"
#include "Common.hpp"
using namespace VectorSort;

void test()
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

    int target = 5;
    // int pos = binarySearchNorecursive<int>(vecObj, target);
    int pos = binarySearchRecursive(vecObj, 0, vecObj->size() - 1, target);
    LOG_INFO(target ,"对应的下标为:", pos);
}


int main(int argc, char * argv[])
{
    test();
    return 0;
}