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
void quickSort(Vector<T>& vec, int left, int right, function<bool(const T& a, const T& b)> comFuncAoverB)
{
    if(left > right)
    {
        return;
    }
    T pivot = vec[left];
    int begin = left;
    int end = right;
    while(begin < end)
    {
        while(begin < end && comFuncAoverB(vec[end],pivot))
        {
            end--;
        }
        if(begin < end)
        {
            vec[begin] = vec[end];
            begin++;
        }
        while(begin < end && comFuncAoverB(pivot, vec[begin]))
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
    quickSort(vec, left, begin - 1, comFuncAoverB);
    quickSort(vec, begin + 1, right, comFuncAoverB);
}

template <typename T>
void mergeSort(Vector<T>& vec, int left, int right, function<bool(const T& a, const T& b)> comFuncAoverB)
{
    if(left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(vec, left, mid, comFuncAoverB);
    mergeSort(vec, mid + 1, right, comFuncAoverB);
    int leftHead = left;
    int rightHead = mid + 1;
    Vector<T> tmp;
    while(leftHead <= mid && rightHead <= right)
    {
        if(comFuncAoverB(vec[rightHead], vec[leftHead]))
        {
            tmp.append(vec[leftHead++]);
        }
        else
        {
            tmp.append(vec[rightHead++]);
        }
    }
    while(leftHead <= mid)
    {
        tmp.append(vec[leftHead++]);
    }
    while (rightHead <= right)
    {
        tmp.append(vec[rightHead++]);
    }
    for(int i = left, index = 0; i <= right; ++i)
    {
        vec[i] = tmp[index++];
    }
}

template <typename T>
void heapfy(Vector<T>& vec, int len, int parent, function<bool(const T& a, const T& b)> comFuncAoverB)
{
    int largest = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;
    if(left < len && comFuncAoverB(vec[left], vec[largest]))
    {
        largest = left;
    }
    if(right < len && comFuncAoverB(vec[right], vec[largest]))
    {
        largest = right;
    }
    if(largest != parent)
    {
        swap(vec[largest], vec[parent]);
        heapfy(vec, len, largest, comFuncAoverB);
    }
}

template <typename T>
void heapSort(Vector<T>& vec, function<bool(const T& a, const T& b)> comFuncAoverB)
{
    int size = vec.size();
    for(int i = size / 2 - 1; i >= 0; --i)
    {
        heapfy(vec, size, i, comFuncAoverB);
    }
    for(int i = size - 1; i > 0; --i)
    {
        swap(vec[i], vec[0]);
        heapfy(vec, i, 0, comFuncAoverB);
    }
}

#endif /*_SORT_HPP_*/