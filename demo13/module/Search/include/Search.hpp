#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_
#include "Common.hpp"
template <typename T>
int binarySearchNorecursive(const std::shared_ptr<std::vector<T>> vec, T target)
{
    LOG_DEBUG("调用函数 binarySearchNorecursive");
    int size = vec->size();
    int left = 0;
    int right = size - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if(target < (*vec)[mid])
        {
            right = mid - 1;
        }
        else if (target > (*vec)[mid])
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
int binarySearchRecursive(const std::shared_ptr<std::vector<T>> vec, int left, int right, T target)
{
    LOG_DEBUG("调用函数 binarySearchRecursive");
    int mid = (left + right) / 2;
    if(target < (*vec)[mid])
    {
        binarySearchRecursive(vec, left, mid - 1, target);
    }
    else if (target > (*vec)[mid])
    {
         binarySearchRecursive(vec, mid + 1, right, target);
    }
    else
    {
        return mid;
    }
    return -1;
}
#endif /*_SEARCH_HPP_*/