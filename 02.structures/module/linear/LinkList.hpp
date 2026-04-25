#pragma once
#ifndef _LINKLIST_HPP_
#define _LINKLIST_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
namespace Structures {
template <typename T>
struct Node
{
    T _value;
    std::unique_ptr<Node<T>> _next;
    Node(const T& value): _value(value), _next(nullptr) {}
};
template <typename T>
class LinkList
{
private:
    std::unique_ptr<Node<T>> _head;
    size_t _size = 0;
public:
    LinkList() = default;
    ~LinkList() = default;
    LinkList(const LinkList&) = delete;
    LinkList& operator=(const LinkList&) = delete;
    LinkList(LinkList&& other) noexcept;
    LinkList& operator=(LinkList&& other) noexcept;
    bool empty() const;
    size_t size() const;
    void insertHead(const T& value);
    void insertTail(const T& value);
    void insert(const T& value, size_t pos);
    bool deleteNode(const T& value);
    void deleteByPos(size_t pos);
    size_t searchNode(const T& value) const;
    const T& head() const;
    void show() const;
};
template <typename T>
LinkList<T>::LinkList(LinkList&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::LinkList(LinkList&& other) noexcept";
    _head = std::move(other._head);
    _size = other._size;
    other._size = 0;
}
template <typename T>
LinkList<T>& LinkList<T>::operator=(LinkList&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>& LinkList<T>::operator=(LinkList&& other) noexcept";
    if (this != &other)
    {
        _head = std::move(other._head);
        _size = other._size;
        other._size = 0;
    }
    return *this;
}
template <typename T>
bool LinkList<T>::empty() const
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::empty() const";
    return _size == 0;
}
template <typename T>
size_t LinkList<T>::size() const
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::empty() const";
    return _size;
}
template <typename T>
void LinkList<T>::insertHead(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::insertHead(const T& value)";
    auto newNode = std::make_unique<Node<T>>(value);
    newNode->_next = std::move(_head);
    _head = std::move(newNode);
    ++_size;
}
template <typename T>
void LinkList<T>::insertTail(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::insertTail(const T& value)";
    auto newNode = std::make_unique<Node<T>>(value);
    if (!_head)
    {
        _head = std::move(newNode);
    }
    else
    {
        auto current = _head.get();
        while(current->_next)
        {
            current = current->_next.get();
        }
        current->_next = std::move(newNode);
    }
    ++_size;
}
template <typename T>
void LinkList<T>::insert(const T& value, size_t pos)
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::insert(const T& value, size_t pos)";
    if (pos > _size)
    {
        throw std::out_of_range("Pos is Out of Range!");
    }
    if (pos == 0)
    {
        insertHead(value);
    }
    else
    {
        auto newNode = std::make_unique<Node<T>>(value);
        auto current = _head.get();
        for (size_t i = 0; i < pos - 1; ++i)
        {
            current = current->_next.get();
        }
        newNode->_next = std::move(current->_next);
        current->_next = std::move(newNode);
        ++_size;
    }
}
template <typename T>
bool LinkList<T>::deleteNode(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::deleteNode(const T& value))";
    if (!_head)
    {
        return false;
    }
    if (_head->_value == value)
    {
        _head = std::move(_head->_next);
        --_size;
        return true;
    }
    auto current = _head.get(); 
    while (current->_next)
    {
        if (current->_next->_value == value)
        {
            current->_next = std::move(current->_next->_next);
            --_size;
            return true;
        }
        current = current->_next.get();
    }
    return false;
}
template <typename T>
void  LinkList<T>::deleteByPos(size_t pos)
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::deleteByPos(size_t pos)";
    if (pos >= _size)
    {
        throw std::out_of_range("Pos is Out of Range!");
    }
    if (pos == 0)
    {
        _head = std::move(_head->_next);
        --_size;
        return;
    }
    auto current = _head.get();
    for (size_t i = 0; i < pos - 1; ++i)
    {
        current = current->_next.get();
    }
    current->_next= std::move(current->_next->_next);
    --_size;
}
template <typename T>
size_t LinkList<T>::searchNode(const T& value) const
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::searchNode(const T& value) const";
    auto current = _head.get();
    for (size_t i = 0; i < _size; ++i)
    {
        if(current->_value == value)
        {
            return i;
        }
        current = current->_next.get();
    }
    return static_cast<size_t>(-1);
}
template <typename T>
const T&  LinkList<T>::head() const
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::head() const";
    return _head->_value;
}
template <typename T>
void LinkList<T>::show() const
{
    logger(DEBUG) << "[call_func]|" << "LinkList<T>::show() const";
    auto current = _head.get();
    while (current)
    {
        std::cout << current->_value;
        if(current->_next)
        {
            std::cout << "-->";
        }
        current = current->_next.get();
    }
    std::cout << std::endl;
    
}
}
#endif /*_LINKLIST_HPP_*/