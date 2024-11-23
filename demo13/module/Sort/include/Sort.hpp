#ifndef _SORT_HPP_
#define _SORT_HPP_
#include <iostream>
#include <vector>
#include <memory>
#include "Common.hpp"

namespace VectorSort {
template <typename T>
class VectorSorter
{
public:
    explicit VectorSorter<T>(std::shared_ptr<std::vector<T>> vec):_vec(vec){}
    void bubbleSort()
    {
        bubble();
    }
    void selectionSort();
    void insertionSort();
    void shellSort();
    void quickSort();
    void mergeSort();
    void heapSort();

private:
    std::shared_ptr<std::vector<T>> _vec;
    void bubble();
    void selection();
    void insertion();
    void shell();
    void quick();
    void merge();
    void heap();
    void heapfy();
};

template <typename T>
void VectorSorter<T>::bubble()
{
    LOG_DEBUG("调用函数 VectorSorter<T>::bubble");
    int size = _vec->size();
    LOG_DEBUG("size = ", size);
    for(int i = 0; i < size - 1; ++i)
    {
        bool swapped = false;
        for(int j = 0; j < size - 1 -i; ++j)
        {
            if((*_vec)[j] > (*_vec)[j+1])
            {
                std::swap((*_vec)[j], (*_vec)[j+1]);
                swapped = true;
            }
        }
        if(!swapped)
        {
            break;
        }
    }
}

template <typename T>
void VectorSorter<T>::selection()
{

}

template <typename T>
void VectorSorter<T>::insertion()
{

}

template <typename T>
void VectorSorter<T>::shell()
{

}

template <typename T>
void VectorSorter<T>::quick()
{

}

template <typename T>
void VectorSorter<T>::merge()
{

}

template <typename T>
void VectorSorter<T>::heap()
{

}

template <typename T>
void VectorSorter<T>::heapfy()
{

}
}
#endif /*_SORT_HPP_*/