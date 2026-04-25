#pragma once
#ifndef _GENERAL_BINARY_TREE_HPP_
#define _GENERAL_BINARY_TREE_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
#include "Queue.hpp"
namespace Structures {
template <typename T>
class GeneralBinaryTree
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
    void insertRecursive(std::unique_ptr<TreeNode>& node, const T& value, bool toLeft);
    bool searchRecursive(const std::unique_ptr<TreeNode>& node, const T& value);
    void preOrderRecursive(const std::unique_ptr<TreeNode>& node) const;
    void inOrderRecursive(const std::unique_ptr<TreeNode>& node) const;
    void postOrderRecursive(const std::unique_ptr<TreeNode>& node) const;

public:
    GeneralBinaryTree() = default;
    ~GeneralBinaryTree() = default;
    GeneralBinaryTree(const GeneralBinaryTree&) = delete;
    GeneralBinaryTree& operator=(const GeneralBinaryTree&) = delete;
    GeneralBinaryTree(GeneralBinaryTree&& other) noexcept;
    GeneralBinaryTree& operator=(GeneralBinaryTree&& other) noexcept;

    bool empty() const;
    int size() const;
    int height() const;


    void insert(const T& value, bool toLeft = true);
    bool search(const T& value) const;
    void clear();

    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void levelOrder() const;
};  
template <typename T>
GeneralBinaryTree<T>::GeneralBinaryTree(GeneralBinaryTree<T>&& other) noexcept:_size(other._size), _root(std::move(other._root))
{
    logger(DEBUG) << "[call_func]|" << "GeneralBinaryTree(GeneralBinaryTree&& other) noexcept";
    _size = 0;
}
template <typename T>
GeneralBinaryTree<T>& GeneralBinaryTree<T>::operator=(GeneralBinaryTree&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "GeneralBinaryTree& operator=(GeneralBinaryTree&& other) noexcept";
    if (this != &other)
    {
        _size = other._size; 
        _size = 0;
        _root = std::move(other._root);
    }
    return *this;
    }
template <typename T>
bool GeneralBinaryTree<T>::empty() const
{
    logger(DEBUG) << "[call_func]|" << "empty()";
    return _size == 0;
}
template <typename T>
int GeneralBinaryTree<T>::size() const
{
    logger(DEBUG) << "[call_func]|" << "size()";
    return _size;
}
template <typename T>
int GeneralBinaryTree<T>::height() const
{
    logger(DEBUG) << "[call_func]|" << "height()";
    if (!_root)
    {
        return 0;
    }
    Queue<TreeNode*> q;
    q.enqueue(_root.get());
    int height = 0;
    while(!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i)
        {
            TreeNode* current = q.front();
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
void GeneralBinaryTree<T>::insert(const T& value, bool toLeft)
{
    logger(DEBUG) << "[call_func]|" << "insert()";
    if (!_root)
    {
        _root = std::make_unique<TreeNode>(value);
        _size = 1;
        return;
    }
    insertRecursive(_root, value, toLeft);
}
template <typename T>
void GeneralBinaryTree<T>::insertRecursive(std::unique_ptr<TreeNode>& node, const T& value, bool toLeft)
{
    logger(DEBUG) << "[call_func]|" << "insertRecursive()";
    if (!node)
    {
        node = std::make_unique<TreeNode>(value);
        _size++;
        return;
    }
    if (toLeft)
    {
        insertRecursive(node->_left, value, toLeft);
    }
    else
    {
        insertRecursive(node->_right, value, toLeft);
    }
}
template <typename T>
bool GeneralBinaryTree<T>::search(const T& value) const
{
    logger(DEBUG) << "[call_func]|" << "search()";
    return searchRecursive(_root, value);
    
}
template <typename T>
bool GeneralBinaryTree<T>::searchRecursive(const std::unique_ptr<TreeNode>& node, const T& value)
{
    logger(DEBUG) << "[call_func]|" << "searchRecursive()";
    if(!node)
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
void GeneralBinaryTree<T>::clear()
{
    logger(DEBUG) << "[call_func]|" << "clear()";
    _root.reset();
    _size = 0;
}
template <typename T>
void GeneralBinaryTree<T>::preOrder() const
{
    logger(DEBUG) << "[call_func]|" << "preOrder()";
    preOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void GeneralBinaryTree<T>::inOrder() const
{
    logger(DEBUG) << "[call_func]|" << "inOrder()";
    inOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void GeneralBinaryTree<T>::postOrder() const
{
    logger(DEBUG) << "[call_func]|" << "postOrder()";
    postOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void GeneralBinaryTree<T>::preOrderRecursive(const std::unique_ptr<TreeNode>& node) const
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
void GeneralBinaryTree<T>::inOrderRecursive(const std::unique_ptr<TreeNode>& node) const
{
    // logger(DEBUG) << "[call_func]|" << "inOrderRecursive()";
    if (!node)
    {
        return;
    }
    inOrderRecursive(node->_left);
    std::cout << node->_value << " ";
    inOrderRecursive(node->_right);
}
template <typename T>
void GeneralBinaryTree<T>::postOrderRecursive(const std::unique_ptr<TreeNode>& node) const
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
template <typename T>
void GeneralBinaryTree<T>::levelOrder() const
{
    logger(DEBUG) << "[call_func]|" << "levelOrder()";
    if (!_root)
    {
        return;
    }
    Queue<TreeNode*> q; //使用了unique_ptr，此处采用原始指针临时访问
    q.enqueue(_root.get());
    while (!q.empty())
    {
        auto current = q.front();
        q.dequeue();
        std::cout << current->_value << " ";
        if (current->_left)
        {
            q.enqueue(current->_left.get());
        }
        if (current->_right)
        {
            q.enqueue(current->_right.get());
        } 
    }
    std::cout << std::endl;
}
} // namespace Structures

#endif /*_GENERAL_BINARY_TREE_HPP_*/