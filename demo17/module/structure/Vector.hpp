#pragma once
#ifndef _STRUCTURE_HPP_
#define _STRUCTURE_HPP_
#include <iostream>
#include <memory>
namespace Structure
{
template <typename T>
class Vector
{
private:
    std::unique_ptr<T[]> _vec;
    size_t _size;
    size_t _capacity;
    void resize(size_t newCapacity);
public:
    Vector() : _size(0), _capacity(0), _vec(nullptr) {}
    explicit Vector(size_t initialCapacity) : _size(0), _capacity(initialCapacity), _vec(std::make_unique<T[]>(_capacity)) {}
    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;
    Vector(Vector&&) = delete;
    Vector& operator=(Vector&&) = delete;
    ~Vector() = default;
    T& operator[](const size_t index);
    const T& operator[](const size_t index) const;
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
    void show() const;
    void push_back(const T& value);
    void pop_back();
};
template <typename T>
void Vector<T>::resize(size_t newCapacity)
{
    auto _newVec = std::make_unique<T[]>(newCapacity);
    for (size_t i = 0; i < _size; ++i)
    {
        _newVec[i] = std::move(_vec[i]);
    }
    _vec = std::move(_newVec);
    _capacity = newCapacity;
}
template <typename T>
T& Vector<T>::operator[](const size_t index)
{
    if (!_vec)
    {
        throw std::invalid_argument("_vec is a nullptr");
    }
    if (index >= _size)
    {
        throw std::out_of_range("index out of range");
    }
    return _vec[index];
}
template <typename T>
const T& Vector<T>::operator[](const size_t index) const
{
    if (!_vec)
    {
        throw std::invalid_argument("_vec is a nullptr");
    }
    if (index >= _size)
    {
        throw std::out_of_range("index out of range");
    }
    return _vec[index];
}
template <typename T>
size_t Vector<T>::size() const
{
    return _size;
}
template <typename T>
size_t Vector<T>::capacity() const
{
    return _capacity;
}
template <typename T>
bool Vector<T>::empty() const
{
    return _size == 0;
}
template <typename T>
void Vector<T>::clear()
{
    _size = 0;
}
template <typename T>
void Vector<T>::show() const
{
    for (size_t i = 0; i < _size; ++i)
    {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;
}
template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (_size >= _capacity)
    {
        size_t newCapacity = _capacity == 0? 1 : _capacity * 2;
        resize(newCapacity);
    }
    _vec[_size++] = value;
}
template <typename T>
void Vector<T>::pop_back()
{
    if ( _size == 0)
    {
        throw std::underflow_error("cannot pop_back, _vec is empty");
    }
    --_size;
}
}

void structureVector()
{
    Structure::Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.show();
    vec.pop_back();
    vec.push_back(4);    
    vec.push_back(5);
    vec.show();
}
#endif /*_STRUCTURE_HPP_*/