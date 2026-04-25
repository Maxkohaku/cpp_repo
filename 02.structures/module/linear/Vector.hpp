#pragma once
#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
namespace Structures {
template <typename T>
class Vector
{
private:
    std::unique_ptr<T[]> _vec = nullptr;
    size_t _capacity;
    size_t _size;
    void resize(size_t newCapacity);
public:
    Vector() = default;
    explicit Vector(size_t capacity):_capacity(capacity), _size(0), _vec(std::make_unique<T[]>(_capacity)) {}
    ~Vector() = default;
    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;
    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    const T& operator[](size_t index) const;
    T& operator[](size_t index);
    void push_back(const T& value);
    void pop_back();
    void clear();
    void show() const;
};
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::Vector(Vector&& other) noexcept";
    _vec = std::move(other._vec);
    _capacity = other._capacity;
    other._capacity = 0;
    _size = other._size;
    other._size = 0;
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>& Vector<T>::operator=(Vector&& other) noexcept";
    if (this != &other)
    {
        logger(DEBUG) << "[call_func]|" << "Vector<T>::Vector(Vector&& other) noexcept";
        _vec = std::move(other._vec);
        _capacity = other._capacity;
        other._capacity = 0;
        _size = other._size;
        other._size = 0;
    }
    return *this;
}
template <typename T>
bool Vector<T>::empty() const
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::empty() const";
    return _size == 0;
}
template <typename T>
size_t Vector<T>::size() const
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::size() const";
    return _size;
}
template <typename T>
size_t Vector<T>::capacity() const
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::capacity() const";
    return _capacity;
}
template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::operator[](size_t index) const";
    return _vec[index];
}
template <typename T>
T& Vector<T>::operator[](size_t index)
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::operator[](size_t index)";
    return _vec[index];
}
template <typename T>
void Vector<T>::resize(size_t newCapacity)
{   logger(DEBUG) << "[call_func]|" << "Vector<T>::resize(size_t newCapacity)";
    auto newVec = std::make_unique<T[]>(newCapacity);
    std::move(_vec.get(), _vec.get() + _size, newVec.get());
    _vec = std::move(newVec);
    _capacity = newCapacity;
}
template <typename T>
void Vector<T>::push_back(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::push_back(const T& value)";
    if (_size >= _capacity)
    {
        size_t newCapacity = _capacity == 0 ? 1 : _capacity * 2;
        resize(newCapacity);
    }
    _vec[_size++] = value;
}
template <typename T>
void Vector<T>::pop_back()
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::pop_back()";
    if (_size == 0)
    {
        throw std::out_of_range("Vector<T>::pop_back(): Vector is Empty");
    }
    --_size;
}
template <typename T>
void Vector<T>::clear()
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::clear()";
    if (_size < _capacity)
    {
        resize(_size);
    }
    _size = 0;
}
template <typename T>
void Vector<T>::show() const
{
    logger(DEBUG) << "[call_func]|" << "Vector<T>::show() const";
    for (size_t i = 0; i < _size; ++i)
    {
        logger(INFO) << (*this)[i];
    }
}
}
#endif /*_VECTOR_HPP_*/