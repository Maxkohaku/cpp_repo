#pragma once
#ifndef _SORT_HPP_
#define _SORT_HPP_
#include <iostream>
#include <vector>
#include <memory>
namespace VectorSort
{
template <typename T>
class SortTool
{
public:
    SortTool(std::shared_ptr<std::vector<T>> vec) : _vec(vec) {}
    ~SortTool() = default;
    void show() const
    {
        for (const auto& elem : *_vec)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    void bubbleSort()
    {
        bubble();
    }
    void selectionSort()
    {
        selection();
    }
    void insertionSort()
    {
        insertion();
    }
    void shellSort()
    {
        shell();
    }
    void quickSort()
    {
        quick(0, _vec->size() - 1);
    }
    private:
    std::shared_ptr<std::vector<T>> _vec;
    void bubble();
    void selection();
    void insertion();
    void shell();
    void quick(int left, int right);
};
template <typename T>
void SortTool<T>::bubble()
{
    int size = _vec->size();
    for (int i = 0; i < size - 1; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; ++j)
        {
            if ((*_vec)[j] > (*_vec)[j+1])
            {
                std::swap((*_vec)[j], (*_vec)[j+1]);
                swapped = true;
            }
        }
        if (swapped = false)
        {
            break;
        }
    }
}
template <typename T>
void SortTool<T>::selection()
{
    int size = _vec->size();
    for (int i = 0; i < size; ++i)
    {
        int pos = i;
        for (int j = i; j < size; ++j)
        {
            if ((*_vec)[j] < (*_vec)[pos])
            {
                pos = j;
            }
        }
        if (i != pos)
        {
            std::swap((*_vec)[i], (*_vec)[pos]);
        }
    }
}
template <typename T>
void SortTool<T>::insertion()
{
    int size = _vec->size();
    for (int i = 1; i < size; ++i)
    {
        T target = (*_vec)[i];
        int j = i - 1;
        while (j >= 0 && (*_vec)[j] > target)
        {
            (*_vec)[j+1] = (*_vec)[j];
            j--;
        }
        (*_vec)[j+1] = target;
    }
}
template <typename T>
void SortTool<T>::shell()
{
    int size = _vec->size();
    for (int gap = size / 2; gap > 0; gap /= 2)
    {   
        for (int i = gap; i < size; ++i)
        {
            T target = (*_vec)[i];
            int j = i - gap;
            while (j >= 0 && (*_vec)[j] > target)
            {
                (*_vec)[j+gap] = (*_vec)[j];
                j -= gap; 
            }
            (*_vec)[j+gap] = target;
        }
    }
}
template <typename T>
void SortTool<T>::quick(int left, int right)
{
    if(left > right)
    {
        return;
    }
    T pivot = (*_vec)[left];
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && (*_vec)[end] > pivot)
        {
            end--;
        }
        if (begin < end)
        {
            (*_vec)[begin] = (*_vec)[end];
            begin++;
        }
        while (begin < end && (*_vec)[begin] < pivot)
        {
            begin++;
        }
        if (begin < end)
        {
            (*_vec)[end] = (*_vec)[begin];
            end--;
        }
        (*_vec)[begin] = pivot;
    }
    quick(left, begin - 1);
    quick(end + 1, right);
}
} // namespace VectorSort
void sort()
{
    VectorSort::SortTool<int> sortTool(std::make_shared<std::vector<int>> (std::vector<int>{3, 5, 9, 1, 4, 8, 7, 2, 6}));
    sortTool.show();
    // sortTool.bubbleSort();
    // sortTool.selectionSort();
    // sortTool.insertionSort();
    // sortTool.shellSort();
    sortTool.quickSort();
    sortTool.show();
}


#endif /*_SORT_HPP_*/