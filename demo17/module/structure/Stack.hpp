#pragma once
#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <iostream>
#include <memory>
namespace Structure {
template <typename T>
class Stack
{
private:
    std::unique_ptr<T[]> _stack;
    size_t _capacity;
    size_t _top;
public:
    explicit Stack(size_t capacity = 64) : _capacity(capacity), _top(0), _stack(std::make_unique<T[]>(_capacity)) {}
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) = default;
    Stack& operator= (Stack&&) = default;
    bool empty() const;
    bool full() const;
    void push(const T& value);
    void pop();
    const T& top() const;
};
template <typename T>
bool Stack<T>::empty() const
{
    return _top == 0;
}
template <typename T>
bool Stack<T>::full() const
{
    return _top == _capacity;
}
template <typename T>
void Stack<T>::push(const T& value)
{
    if (full())
    {
        throw std::out_of_range("stack is full");
    }
    _stack[_top++] = value;
}
template <typename T>
void Stack<T>:: pop()
{
    if (empty())
    {
        throw std::invalid_argument("stack is empty");
    }
    --_top ;
}
template <typename T>
const T& Stack<T>::top() const
{
    if (empty())
    {
        throw std::invalid_argument("stack is empty");
    }
    std::cout << _stack[_top - 1] << std::endl;
    return _stack[_top - 1];
}
}
void structureStack()
{
    Structure::Stack<int> stack;
    stack.push(1);
    stack.top();
    stack.push(2);
    stack.top();
    stack.push(3);
    stack.top();
    stack.push(4);
    stack.top();
    stack.push(5);
    stack.top();

    stack.pop();
    stack.top();
    stack.pop();
    stack.top();
    stack.pop();
    stack.top();
    stack.pop();
    stack.top();
    stack.pop();
    // stack.top();
}
#endif /*_STACK_HPP_*/