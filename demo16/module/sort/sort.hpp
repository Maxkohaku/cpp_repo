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
    private:
    std::shared_ptr<std::vector<T>> _vec;
    void bubble();
    void selection();
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
} // namespace VectorSort
void sort()
{
    VectorSort::SortTool<int> sortTool(std::make_shared<std::vector<int>> (std::vector<int>{3, 5, 9, 1, 4, 8, 7, 2, 6}));
    sortTool.show();
    // sortTool.bubbleSort();
    sortTool.selectionSort();
    sortTool.show();
}


#endif /*_SORT_HPP_*/