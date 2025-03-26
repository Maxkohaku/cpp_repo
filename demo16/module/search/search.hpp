#pragma once
#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
namespace VectorSearch{
template <typename T>
class SearchTool
{
public:   
    SearchTool(std::shared_ptr<std::vector<T>> vec) : _vec(vec) {}
    ~SearchTool() = default;
    void show() const
    {
        for (const auto& elem : *_vec)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    int binaryNorecursiveSearch(const T& target) const
    {
        return _binaryNorecursiveSearch(target);
    }
    int binaryRecursiveSearch(const T& target) const
    {
        return _binaryRecursiveSearch(target, 0, _vec->size() - 1);
    }
private:
    std::shared_ptr<std::vector<T>> _vec;
    int _binaryNorecursiveSearch(const T& target) const;
    int _binaryRecursiveSearch(const T& target, int left, int right) const;
};
template <typename T>
int SearchTool<T>::_binaryNorecursiveSearch(const T& target) const
{
    int left = 0;
    int right = _vec->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (target < (*_vec)[mid])
        {
            right = mid - 1;
        }
        else if (target > (*_vec)[mid])
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
template <typename T>
int SearchTool<T>::_binaryRecursiveSearch(const T& target, int left, int right) const
{
    if (left > right)
    {
        return -1;
    }
    int mid = left + (right - left) / 2;
    if (target < (*_vec)[mid])
    {
        return _binaryRecursiveSearch(target, left, mid - 1);
    }
    else if (target > (*_vec)[mid])
    {
        return _binaryRecursiveSearch(target, mid + 1, right);
    }
    else
    {
        return mid;
    }
}
}
void search()
{
    VectorSearch::SearchTool<int> searchTool(std::make_shared<std::vector<int>> (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
    searchTool.show();
    int target = 3;
    std::cout << "binaryNorecursiveSearch|pos of " << target << ": " << searchTool.binaryNorecursiveSearch(target) << std::endl;
    std::cout << "binaryRecursiveSearch|pos of " << target << ": " << searchTool.binaryRecursiveSearch(target) << std::endl;
}
#endif /*_SEARCH_HPP_*/