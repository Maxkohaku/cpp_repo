#pragma once
#ifndef _COMPLETE_BINARY_TREE_HPP_
#define _COMPLETE_BINARY_TREE_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
#include "Queue.hpp"
namespace Structures {
template <typename T>
class CompleteBinaryTree
{
private:
    struct  TreeNode
    {
        T _value;
        std::unique_ptr<TreeNode> _left;
        std::unique_ptr<TreeNode> _right;
        TreeNode(const T& value): _value(value), _left(nullptr), _right(nullptr) {}
    };
    std::unique_ptr<TreeNode> _root = nullptr;
    int _size = 0;
    bool searchRecursive(const std::unique_ptr<TreeNode>& node, const T& value) const;
    void preOrderRecursive(const std::unique_ptr<TreeNode>& node)  const;
    void inOrderRecursive(const std::unique_ptr<TreeNode>& node) const;
    void postOrderRecursive(const std::unique_ptr<TreeNode>& node) const;
public:
    CompleteBinaryTree() = default;
    ~CompleteBinaryTree() = default;
    CompleteBinaryTree(const CompleteBinaryTree&) = delete;
    CompleteBinaryTree& operator=(const CompleteBinaryTree&) = delete;
    CompleteBinaryTree(CompleteBinaryTree&& other) noexcept;
    CompleteBinaryTree& operator=(CompleteBinaryTree&& other) noexcept;

    bool empty() const;
    int size() const;
    int height() const;
    bool isComplete() const;
    void clear();

    void insert(const T& value);
    bool search(const T& value) const;
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
};
template <typename T>
CompleteBinaryTree<T>::CompleteBinaryTree(CompleteBinaryTree&& other) noexcept : _size(other._size), _root(std::move(other._root))
{
    logger(DEBUG) << "[call_func]|" << "CompleteBinaryTree(CompleteBinaryTree&& other) noexcept";
    other._size = 0;
}
template <typename T>
CompleteBinaryTree<T>& CompleteBinaryTree<T>::operator=(CompleteBinaryTree&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << " CompleteBinaryTree<T>::operator=(CompleteBinaryTree&& other) noexcept";
    if (this != &other)
    {
        _root = std::move(other._root);
        _size = other._size;
        other._size = 0;
    }
    return *this;
}
template <typename T>
bool CompleteBinaryTree<T>::empty() const
{
    logger(DEBUG) << "[call_func]|" << "empty()";
    return _size == 0;
}
template <typename T>
int CompleteBinaryTree<T>::size() const
{
    logger(DEBUG) << "[call_func]|" << "size()";
    return _size;
}
template <typename T>
int CompleteBinaryTree<T>::height() const
{
    logger(DEBUG) << "[call_func]|" << "height()";
    Queue<TreeNode*> q;
    if (!_root)
    {
        return 0;
    }
    q.enqueue(_root.get());
    int height = 0;
    while (!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i)
        {
            auto current = q.front();
            q.dequeue();
            if (current->_left)
            {
                q.enqueue(current->_left.get());
            }
            if (current->_right)
            {
                q.enqueue(current->_right.get());
            }
        }
        ++height;
    }
    return height;
}
template <typename T>
bool CompleteBinaryTree<T>::isComplete() const
{
    logger(DEBUG) << "[call_func]|" << "isComplete()";
    if (!_root)
    {
        return true;
    }
    Queue<TreeNode*> q;
    q.enqueue(_root.get());
    bool isNull = false;
    while (!q.empty())
    {
        auto current = q.front();
        q.dequeue();
        if (!current)
        {
            isNull = true;
        }
        else
        {
            if (isNull)
            {
                return false;
            }
            q.enqueue(current->_left.get());
            q.enqueue(current->_right.get());
        }
    }
    return true;
}
template <typename T>
void CompleteBinaryTree<T>::clear()
{
    logger(DEBUG) << "[call_func]|" << "clear()";
    _root.reset();
    _size = 0;
}
template <typename T>
void CompleteBinaryTree<T>::insert(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "insert()";
    if (!_root)
    {
        _root = std::make_unique<TreeNode>(value);
        ++_size;
        return;
    }
    Queue<TreeNode*> q;
    q.enqueue(_root.get());
    while (!q.empty())
    {
        auto current = q.front();
        q.dequeue();
        if (!current->_left)
        {
            current->_left = std::make_unique<TreeNode>(value);
            ++_size;
            return;
        }
        else
        {
            q.enqueue(current->_left.get());
        }
        if (!current->_right)
        {
            current->_right = std::make_unique<TreeNode>(value);
            ++_size;
            return; 
        }
        else
        {
            q.enqueue(current->_right.get());
        }
    }
}
template <typename T>
bool CompleteBinaryTree<T>::search(const T& value) const
{
    logger(DEBUG) << "[call_func]|" << "search()";
    return searchRecursives(_root, value);
}
template <typename T>
bool CompleteBinaryTree<T>::searchRecursive(const std::unique_ptr<TreeNode>& node, const T& value) const
{
    logger(DEBUG) << "[call_func]|" << "searchRecursive()";
    if (!node)
    {
        return false;
    }
    if (node->_value == value)
    {
        return true;
    }
    return searchRecursive(node->_left, value) || searchRecursive(node->_right, value);
}
template <typename T>
void CompleteBinaryTree<T>::preOrder() const
{
    logger(DEBUG) << "[call_func]|" << "preOrder()";
    preOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void CompleteBinaryTree<T>::inOrder() const
{
    logger(DEBUG) << "[call_func]|" << "inOrder()";
    inOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void CompleteBinaryTree<T>::postOrder() const
{
    logger(DEBUG) << "[call_func]|" << "postOrder()";
    postOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void CompleteBinaryTree<T>::preOrderRecursive(const std::unique_ptr<TreeNode>& node)  const
{
    logger(DEBUG) << "[call_func]|" << "preOrderRecursive()";
    if (!node)
    {
        return;
    }
    std::cout << node->_value << " ";
    preOrderRecursive(node->_left);
    preOrderRecursive(node->_right);
}
template <typename T>
void CompleteBinaryTree<T>::inOrderRecursive(const std::unique_ptr<TreeNode>& node) const
{
    logger(DEBUG) << "[call_func]|" << "inOrderRecursive()";
    if (!node)
    {
        return;
    }
    inOrderRecursive(node->_left);
    std::cout << node->_value << " ";
    inOrderRecursive(node->_right);
}
template <typename T>
void CompleteBinaryTree<T>::postOrderRecursive(const std::unique_ptr<TreeNode>& node) const
{
    logger(DEBUG) << "[call_func]|" << "postOrderRecursive()";
    if (!node)
    {
        return;
    }
    postOrderRecursive(node->_left);
    postOrderRecursive(node->_right);
    std::cout << node->_value << " ";
}
}
#endif /*_COMPLETE_BINARY_TREE_HPP_*/       