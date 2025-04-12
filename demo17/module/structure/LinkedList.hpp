#pragma once
#ifndef _LINKEDLIST_HPP_
#define _LINKEDLIST_HPP_
#include <iostream>
#include <memory>
namespace Structure {
template <typename T>
struct Node
{
    T _value;
    std::unique_ptr<Node<T>> _next;
    Node(const T& value) : _value(value), _next(nullptr) {} 
    ~Node() = default;
};
template <typename T>
class LinkedList
{
private:
    std::unique_ptr<Node<T>> _head;
    size_t _size;
public:
    LinkedList() : _size(0), _head(nullptr) {} 
    ~LinkedList() = default;
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    LinkedList(LinkedList&&) = default;
    LinkedList& operator=(LinkedList&&) = default;
    size_t size() const;
    bool empty() const;
    bool search(const T& value) const;
    void show() const;
    bool insertHead(const T& value);
    bool insertTail(const T& value);
    bool insert(const T& value, size_t pos);
    bool deleteHead();
    bool deleteNode(const T& value);
    bool deleteByPos(size_t pos);
};
template <typename T>
size_t LinkedList<T>::size() const
{
    return _size;
}
template <typename T>
bool LinkedList<T>::empty() const
{
    return _size == 0;
}
template <typename T>
bool LinkedList<T>::search(const T& value) const
{
    Node<T>* current = _head.get();
    while (current)
    {
        if (current->_value == value)
        {
            return true;
        }
        current = current->_next;
    }
    return false;
}
template <typename T>
void LinkedList<T>::show() const
{
    auto current = _head.get();
    while (current)
    {
        std::cout << current->_value;
        if (current->_next)
        {
            std::cout << " ->";
        }
        current = current->_next.get();
    }
     std::cout << std::endl;
}
template <typename T>
bool LinkedList<T>::insertHead(const T& value)
{
    auto newNode = std::make_unique<Node<T>>(value);
    newNode->_next = std::move(_head);
    _head = std::move(newNode);
    ++_size;
    return true;
}
template <typename T>
bool LinkedList<T>::insertTail(const T& value)
{
    if (!_head)
    {
        return insertHead(value);
    }
    auto current = _head.get();
    auto newNode = std::make_unique<Node<T>>(value);
    while (current->_next)
    {
        current = current->_next.get();
    }
    current->_next = std::move(newNode);
    ++_size;
    return true;
}
template <typename T>
bool LinkedList<T>::insert(const T& value, size_t pos)
{
    if (pos > _size)
    {
        throw std::out_of_range("out of range for pos");
    }
    if(pos == 0)
    {
        return insertHead(value);
    }
    auto newNode = std::make_unique<Node<T>>(value);
    auto current = _head.get();
    for (size_t i = 0; i < pos - 1; ++i)
    {
        current = current->_next.get();
    }
    newNode->_next = std::move(current->_next);
    current->_next = std::move(newNode);
    ++_size;
    return true;
}
template <typename T>
bool LinkedList<T>::deleteHead()
{
    if (!_head)
    {
        return false;
    }
    _head = std::move(_head->_next);
    --_size;
    return true;
}
template <typename T>
bool LinkedList<T>::deleteNode(const T& value)
{
    if (!_head)
    {
        return false;
    }
    if (_head->_value == value)
    {
        return deleteHead(); 
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
bool LinkedList<T>::deleteByPos(size_t pos)
{
    if (pos >= _size)
    {
        throw std::out_of_range("out of range for pos");
    }
    if (pos == 0)
    {
        return deleteHead();
    }
    auto current = _head.get();
    for (size_t i = 0; i < pos - 1; ++i)
    {
    
        current = current->_next.get();
    }
    current->_next = std::move(current->_next->_next);
    --_size;
    return true;

}
}
void structureLinkedList()
{
    Structure::LinkedList<int> link;
    link.insertTail(1); 
    link.insertTail(2); 
    link.insertTail(3); 
    link.insertTail(4); 
    link.insertTail(5); 
    link.show(); 
    link.deleteHead(); 
    link.show(); 
    link.insertHead(1); 
    link.show(); 
    link.insert(100, 3); 
    link.show();
    link.deleteNode(100);
    link.show();
    link.deleteByPos(2);
    link.show();
}
#endif /*_LINKEDLIST_HPP_*/