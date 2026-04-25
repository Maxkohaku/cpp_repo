#pragma once
#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
#include "LinkList.hpp"
namespace Structures {
template <typename T>
class Queue
{
private:
    std::unique_ptr<LinkList<T>> _queue = std::make_unique<LinkList<T>>();
    size_t _size = 0;
public:
    Queue() = default;
    ~Queue() = default;
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(Queue&& other) noexcept;
    Queue& operator=(Queue&& other) noexcept;
    bool empty() const;
    size_t size() const;
    void enqueue(const T& value);
    void dequeue();
    // T& front();
    const T& front() const;
    void show() const;
};
template <typename T>
Queue<T>::Queue(Queue&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::Queue(Queue&& other) noexcept";
    _queue = std::move(other._queue);
    _size = other._size;
    other._size = 0;
}
template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::operator=(Queue&& other) noexcept";
    if (this != &other)
    {
        _queue = std::move(other._queue);
        _size = other._size;
        other._size = 0;
    }
    return *this;
}
template <typename T>
bool Queue<T>::empty() const
{
    logger(DEBUG) << "[call_func]|" <<  "Queue<T>::empty() const";
    return _size == 0;
}
template <typename T>
size_t Queue<T>::size() const
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::size() const";
    return _size;
}
template <typename T>
void Queue<T>::enqueue(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::enqueue(const T& value)";
    _queue->insertTail(value);
    ++_size;
}
template <typename T>
void Queue<T>::dequeue()
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::dequeue()";
    if (empty())
    {
        throw std::out_of_range("Queue is Empty!");
    }
    _queue->deleteByPos(0);
    --_size;
}
template <typename T>
const T& Queue<T>::front() const
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::front() const";
    // logger(INFO) << _queue->head();
    return _queue->head();
}
template <typename T>
void Queue<T>::show() const
{
    logger(DEBUG) << "[call_func]|" << "Queue<T>::show() const";
}
}
#endif /*_QUEUE_HPP_*/