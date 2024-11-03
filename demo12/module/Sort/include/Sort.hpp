#ifndef _SORT_HPP_
#define _SORT_HPP_
#include <iostream>
#include "Vector.hpp"
#include <functional>
#if DEBUG
    #define DEBUG_LOG(msg) std::cout << msg << std::endl;
#else
    #define DEBUG_LOG(msg)
#endif
using namespace std;

template <typename T>
void bubbleSort(Vector<T>& vec, function<bool(const T& a, const T& b)> compFunc)
{
    DEBUG_LOG("call bubbleSort");
    int size = vec.size();
    for(int i = 0; i < size - 1; ++i)
    {
        bool swapped = false;
        for(int j = 0; j < size - i -1; ++j)
        {
            if(compFunc(vec[j], vec[j+1]))
            {
                swap(vec[j], vec[j+1]);
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
void selectionSort(Vector<T>& vec, function<bool(const T& a, const T& b)> comFunc)
{
    int size = vec.size();
    for(int i = 0; i < size - 1; ++ i)
    {
        int minPos = i;
        for(int j = i + 1; j < size; ++j)
        {
            if(comFunc(vec[minPos], vec[j]))
            {
                minPos = j;
            }
        }
        if(minPos != i)
        {
            swap(vec[minPos], vec[i]);
        }
    }
}

template <typename T>
void insertionSort(Vector<T>& vec, function<bool(const T& a, const T& b)> comFunc)
{
    int size = vec.size();
    for(int i = 1; i < size; ++i)
    {
        T key = vec[i];
        int j = i - 1;
        while (j >= 0 && comFunc(vec[j], key))
        {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = key;
    }
}

template <typename T>
void shellSort(Vector<T>& vec, function<bool(const T& a, const T& b)> comFunc)
{
    int size = vec.size();
    for(int gap = size / 2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < size; ++i)
        {
            T temp = vec[i];
            int j = i - gap;
            while(j >= 0 && comFunc(vec[j], temp))
            {
                vec[j+gap] = vec[j];
                j -= gap;
            }
            vec[j+gap] = temp;
        }
    }
}

template <typename T>
void quickSort(Vector<T>& vec, int left, int right, function<bool(const T& a, const T& b)> comFunc)
{
    if(left > right)
    {
        return;
    }
    T pivot = vec[left];
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && comFunc(vec[end], pivot))
        {
            end--;
        }
        if(begin < end)
        {
            vec[begin] = vec[end];
            begin++;
        }
        while (begin < end && comFunc(pivot, vec[begin]))
        {
            begin++;
        }
        if(begin < end)
        {
            vec[end] = vec[begin];
            end--;
        }
    }
    vec[begin] = pivot;
    quickSort(vec, left, end - 1, comFunc);
    quickSort(vec, end + 1, right, comFunc);
}

#endif /*_SORT_HPP_*/