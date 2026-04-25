#pragma once
#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
namespace Structures {
template <typename T>
class Stack
{
private:
    std::unique_ptr<T[]> _stack = nullptr;
    size_t _capacity = 0;
    size_t _top = 0;
public:
    Stack() = default;
    explicit Stack(size_t capacity):_capacity(capacity),_stack(std::make_unique<T[]>(_capacity)) {}
    ~Stack() = default;
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;
    bool empty() const;
    bool full() const;
    void push(const T& value);
    void pop();
    const T& top() const;
};
template <typename T>
Stack<T>::Stack(Stack&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>::Stack(Stack&& other) noexcept";
    _stack = std::move(other._stack);
    _capacity = other._capacity;
    other._capacity = 0;
    _top = other._top;
    other._top = 0;
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>& Stack<T>::operator=(Stack&& other) noexcept";
    if (this != &other)
    {
        _stack = std::move(other._stack);
        _capacity = other._capacity;
        other._capacity = 0;
        _top = other._top;
        other._top = 0;
    }
    return *this;
}
template <typename T>
bool Stack<T>::empty() const
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>::empty() const";
    return _top == 0;
}
template <typename T>
bool Stack<T>::full() const
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>::full() const";
    return _top == _capacity;
}
template <typename T>
void Stack<T>::push(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>::push(const T& value)";
    if (full())
    {
        throw std::out_of_range("Stack is Full!");
    }
    _stack[_top++] = value;
}
template <typename T>
void Stack<T>::pop()
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>::pop";
    if (empty())
    {
        throw std::out_of_range("Stack is Empty!");
    }
    --_top;
}   
template <typename T>
const T& Stack<T>::top() const
{
    logger(DEBUG) << "[call_func]|" << "Stack<T>::pop";
    if (empty())
    {
        throw std::out_of_range("Stack is Empty!");
    }
    logger(INFO) << _stack[_top - 1];
    return _stack[_top - 1];
}
} // namespace Structures
#endif /*_STACK_HPP_*/