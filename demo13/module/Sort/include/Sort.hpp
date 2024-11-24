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
    explicit VectorSorter<T>(std::shared_ptr<std::vector<T>> vec):m_vec(vec){}
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
        int left = 0;
        int right = m_vec->size() - 1;
        quick(left, right);
    }
    void mergeSort()
    {
        int left = 0;
        int right = m_vec->size() - 1;
        merge(left, right);
    }
    void heapSort()
    {
        heap();
    }

private:
    std::shared_ptr<std::vector<T>> m_vec;
    void bubble();
    void selection();
    void insertion();
    void shell();
    void quick(int left, int right);
    void merge(int left, int right);
    void heap();
    void heapfy(int len, int parent);
};

template <typename T>
void VectorSorter<T>::bubble()
{
    LOG_DEBUG("调用函数 VectorSorter<T>::bubble");
    int size = m_vec->size();
    LOG_DEBUG("size = ", size);
    for(int i = 0; i < size - 1; ++i)
    {
        bool swapped = false;
        for(int j = 0; j < size - 1 -i; ++j)
        {
            if((*m_vec)[j] > (*m_vec)[j+1])
            {
                std::swap((*m_vec)[j], (*m_vec)[j+1]);
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
    LOG_DEBUG("调用函数 VectorSorter<T>::selection");
    int size = m_vec->size();
    for(int i = 0; i < size; ++i)
    {
        int pos = i;
        for(int j = i + 1; j < size; ++j)
        {
            if((*m_vec)[j] < (*m_vec)[pos])
            {
                pos = j;
            }
        }
        if(pos != i)
        {
            std::swap((*m_vec)[i], (*m_vec)[pos]);
        }
    }
}

template <typename T>
void VectorSorter<T>::insertion()
{
    LOG_DEBUG("调用函数 VectorSorter<T>::insertion");
    int size = m_vec->size();
    for(int i = 1; i < size; ++i)
    {
        T target = (*m_vec)[i];
        int j = i - 1;
        while (j >= 0 && (*m_vec)[j] > target)
        {
            (*m_vec)[j+1] = (*m_vec)[j];
            j--;
        }
        (*m_vec)[j+1] = target;
    }
}

template <typename T>
void VectorSorter<T>::shell()
{
    LOG_DEBUG("调用函数 VectorSorter<T>::shell");
    int size = (*m_vec)->size();
    for(int gap = size / 2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < size; ++i)
        {
            T target = (*m_vec)[i];
            int j = i - gap;
            while (j >= 0 && (*m_vec)[j] > target)
            {
                (*m_vec)[j+gap] = (*m_vec)[j];
                j -= gap;
            }
            (*m_vec)[j+gap] = target;
        }
    }
}

template <typename T>
void VectorSorter<T>::quick(int left, int right)
{
    LOG_DEBUG("调用函数 VectorSorter<T>::quick");
    if(left > right)
    {
        return;
    }
    T pivot = (*m_vec)[left];
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && (*m_vec)[end] > pivot)
        {
            end--;
        }
        if(begin < end)
        {
            (*m_vec)[begin] = (*m_vec)[end];
            begin++;
        }
        while (begin < end && (*m_vec)[begin] < pivot)
        {
            begin++;
        }
        if(begin < end)
        {
            (*m_vec)[end] = (*m_vec)[begin];
            end--;
        }  
    }
    (*m_vec)[begin] = pivot;
    quick(left, begin - 1);
    quick(end + 1, right);
}

template <typename T>
void VectorSorter<T>::merge(int left, int right)
{
    LOG_DEBUG("调用函数 VectorSorter<T>::merge");
    if(left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    merge(left, mid);
    merge(mid + 1, right);
    int lPos = left;
    int rPos= mid + 1;
    std::vector<T> tmpVec;
    while(lPos <= mid && rPos <= right)
    {
        if((*m_vec)[lPos] < (*m_vec)[rPos])
        {
            tmpVec.push_back((*m_vec)[lPos++]);
        }
        else
        {
            tmpVec.push_back((*m_vec)[rPos++]);
        }
    }
    while(lPos <= mid)
    {
        tmpVec.push_back((*m_vec)[lPos++]);
    }
    while(rPos <= right)
    {
        tmpVec.push_back((*m_vec)[rPos++]);
    }
    for(int i = left, j =0; i <= right; ++i)
    {
        (*m_vec)[i] = tmpVec[j++];
    }
}

template <typename T>
void VectorSorter<T>::heap()
{
    LOG_DEBUG("调用函数 VectorSorter<T>::heap");
    int size = m_vec->size();
    for(int i = size / 2 - 1; i >= 0; --i)
    {
        heapfy(size, i);
    }
    for(int i = size - 1; i >= 0; --i)
    {
        std::swap((*m_vec)[0], (*m_vec)[i]);
        heapfy(i, 0);
    }
}

template <typename T>
void VectorSorter<T>::heapfy(int len, int parent)
{
    LOG_DEBUG("调用函数 VectorSorter<T>::heapfy");
    int largest = parent;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;
    if(left < len && (*m_vec)[left] > (*m_vec)[largest])
    {
        largest = left;
    }
    if(right < len && (*m_vec)[right] > (*m_vec)[largest])
    {
        largest = right;
    }
    if(largest != parent)
    {
        std::swap((*m_vec)[largest], (*m_vec)[parent]);
        heapfy(len, largest);
    }
}
}
#endif /*_SORT_HPP_*/