#pragma once
#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_
#include <iostream>
#include <memory>
#include "yLog.h"
#include "Queue.hpp"
namespace Structures {
template <typename T>
class AVLTree
{
private:
    struct AVLNode
    {
    public:
        T _value;
        int _height;
        std::unique_ptr<AVLNode> _left;
        std::unique_ptr<AVLNode> _right;

        AVLNode(const T& value):_value(value), _height(1), _left(nullptr), _right(nullptr) {}
        int getBalanceFactor() const;
        void updateHeight();
    private:
        int getHeight(const std::unique_ptr<AVLNode>& node) const;
    };
    std::unique_ptr<AVLNode> _root = nullptr;
    int _size = 0;

    std::unique_ptr<AVLNode> rotateLeft(std::unique_ptr<AVLNode> node);
    std::unique_ptr<AVLNode> rotateRight(std::unique_ptr<AVLNode> node);
    std::unique_ptr<AVLNode> rotateLeftRight(std::unique_ptr<AVLNode> node);
    std::unique_ptr<AVLNode> rotateRightLeft(std::unique_ptr<AVLNode> node);
    std::unique_ptr<AVLNode> balance(std::unique_ptr<AVLNode> node);
    std::unique_ptr<AVLNode> insertRecursive(std::unique_ptr<AVLNode> node, const T& value);
    std::unique_ptr<AVLNode> removeRecursive(std::unique_ptr<AVLNode> node, const T& value);
    bool searchRecursive(const std::unique_ptr<AVLNode>& node, const T& value) const;
    std::unique_ptr<AVLNode> minNode(const std::unique_ptr<AVLNode>& node);

    bool isBalancedRecursive(const std::unique_ptr<AVLNode>& node) const;


    void preOrderRecursive(const std::unique_ptr<AVLNode>& node) const;
    void inOrderRecursive(const std::unique_ptr<AVLNode>& node) const;
    void postOrderRecursive(const std::unique_ptr<AVLNode>& node) const;

public:
    AVLTree() = default;
    ~AVLTree() = default;
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree(AVLTree&& other) noexcept;
    AVLTree& operator=(AVLTree&& other) noexcept;

    bool empty() const { return _size == 0; }
    int size() const { return _size; }
    int height() const;
    void clear();
    bool isBalanced() const;

    void insert(const T& value);
    bool remove(const T& value);
    bool search(const T& value) const;

    void inOrder() const;
    void preOrder() const; 
    void postOrder() const;
    void levelOrder() const;
};
template <typename T>
int AVLTree<T>::AVLNode::getBalanceFactor() const
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::AVLNode::getBalanceFactor()";
    return getHeight(_left) - getHeight(_right);
}
template <typename T>
void AVLTree<T>::AVLNode::updateHeight()
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::AVLNode::updateHeight()";
    _height = 1 + std::max(getHeight(_left), getHeight(_right));
}
template <typename T>
int AVLTree<T>::AVLNode::getHeight(const std::unique_ptr<AVLNode>& node) const
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::AVLNode::getHeight()";
    return node ? node->_height : 0;
}
template <typename T>
AVLTree<T>::AVLTree(AVLTree&& other) noexcept : _root(std::move(other._root)), _size(other._size)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree(AVLTree&& other)";
    other._size = 0;
}
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree&& other) noexcept
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::operator=(AVLTree&& other) ";
    if (this != &other)
    {
        _root = std::move(other._root);
        _size = other._size;
        other._size = 0;
    }
    return *this;
}
// 见到 Class<T>::Something 时：
// 1. 是类型？ → 加 typename
// 2. 是模板？ → 加 template  
// 3. 是变量？ → 直接使用
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode>  AVLTree<T>::rotateLeft(std::unique_ptr<AVLNode> node)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::rotateLeft()";
    auto newNode = std::move(node->_right);
    node->_right = std::move(newNode->_left);
    newNode->_left = std::move(node);
    if (newNode->_left)
    {
        newNode->_left->updateHeight();
    }
    newNode->updateHeight();
    return newNode;
}
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode>  AVLTree<T>::rotateRight(std::unique_ptr<AVLNode> node)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::rotateRight()";
    auto newNode = std::move(node->_left);
    node->_left = std::move(newNode->_right);
    newNode->_right = std::move(node);
    if (newNode->_right)
    {
        newNode->_right->updateHeight();
    }
    newNode->updateHeight();
    return newNode;
}
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode>  AVLTree<T>::rotateLeftRight(std::unique_ptr<AVLNode> node)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::rotateLeftRight()";
    node->_left = rotateLeft(std::move(node->_left));
    return rotateRight(std::move(node));
}
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode>  AVLTree<T>::rotateRightLeft(std::unique_ptr<AVLNode> node)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::rotateRightLeft()";
    node->_right = rotateRight(std::move(node->_right));
    return rotateLeft(std::move(node));
}
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode> AVLTree<T>::balance(std::unique_ptr<AVLNode> node)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::balance()";
    if (!node)
    {
        logger(WARNING) << "Node is Null !";
        return node;
    }
    node->updateHeight();
    int currentBalanceFactor = node->getBalanceFactor();
    if (currentBalanceFactor > 1)
    {
        int leftBalanceFactor = node->_left->getBalanceFactor();
        if (leftBalanceFactor >= 0)
        {
            return std::move(rotateRight(std::move(node)));
        }
        else
        {
            return std::move(rotateLeftRight(std::move(node)));
        }
    }
    if (currentBalanceFactor < -1)
    {
        int rightBalanceFactor = node->_right->getBalanceFactor();
        if (rightBalanceFactor <= 0)
        {
            return std::move(rotateLeft((std::move(node))));       
        }
        else
        {
            return std::move(rotateRightLeft(std::move(node)));
        }
    }
    return node;
}
template <typename T>
bool AVLTree<T>::isBalanced() const
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::isBalanced()";
    return isBalancedRecursive(_root);
}
template <typename T>
bool AVLTree<T>::isBalancedRecursive(const std::unique_ptr<AVLNode>& node) const
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::isBalancedRecursive()";
    if (!node)
    {
        return true;
    }
    int balanceFactor = node->getBalanceFactor();
    if (balanceFactor < -1 || balanceFactor > 1)
    {
        logger(INFO) << "[node]|" << node->_value << "is Unbalanced !";
        return false;
    }
    return isBalancedRecursive(node->_left) && isBalancedRecursive(node->_right);
}

template <typename T>
void AVLTree<T>::insert(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::insert()";
    _root = std::move(insertRecursive(std::move(_root), value));
    ++_size;
}
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode> AVLTree<T>::insertRecursive(std::unique_ptr<AVLNode> node, const T& value)
{
        
    if (!node)
    {
        return std::make_unique<AVLNode>(value);
    }

    if (value < node->_value)
    {
        node->_left = insertRecursive(std::move(node->_left), value);
    }
    else if(value > node->_value)
    {
        node->_right = insertRecursive(std::move(node->_right), value);
    }
    else
    {
        logger(INFO) << value << " already exists";
        return node;
    }
    return balance(std::move(node));
}
template <typename T>
bool AVLTree<T>::remove(const T& value)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::insertRecursive()";
    int oldSize = _size;
    _root = removeRecursive(std::move(_root), value);
    return _size < oldSize; 
}
template <typename T>
std::unique_ptr<typename AVLTree<T>::AVLNode> AVLTree<T>::removeRecursive(std::unique_ptr<AVLNode> node, const T& value)
{
    logger(DEBUG) << "[call_func]|" << "AVLTree<T>::removeRecursive()";
    if (!node)
    {
        return nullptr;
    }

    if (value < node->_value)
    {
        node->_left = removeRecursive(std::move(node->_left), value);
    }
    else if (value > node->_value)
    {
        node->_right = removeRecursive(std::move(node->_right), value);
    }
    else
    {
        if (!node->_left|| node->_right)
        {
            auto tempNode = std::move(node->_left ? node->_left : node->_right);
            if (!tempNode)
            {
                node = nullptr;
            }
            else
            {
                node = std::move(tempNode);
            }
        }
        else
        {
            auto successor = node->_right.get();
            while (successor->_left)
            {
                successor = successor->_left.get();
            }
            node->_value = successor->_value;
            node->_right = removeRecursive(std::move(node->_right), successor->_value);
        }
    }
    if (!node)
    {
        return nullptr;
    }
    return balance(std::move(node));
}
template <typename T>
bool AVLTree<T>::search(const T& value) const
{
    logger(DEBUG) << "[call_func]|" << "search()";
    return searchRecursive(_root, value);
    
}
template <typename T>
bool AVLTree<T>::searchRecursive(const std::unique_ptr<AVLNode>& node, const T& value) const
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
void AVLTree<T>::preOrder() const
{
    logger(DEBUG) << "[call_func]|" << "preOrder()";
    preOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void AVLTree<T>::inOrder() const
{
    logger(DEBUG) << "[call_func]|" << "inOrder()";
    inOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void AVLTree<T>::postOrder() const
{
    logger(DEBUG) << "[call_func]|" << "postOrder()";
    postOrderRecursive(_root);
    std::cout << std::endl;
}
template <typename T>
void AVLTree<T>::preOrderRecursive(const std::unique_ptr<AVLNode>& node) const
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
void AVLTree<T>::inOrderRecursive(const std::unique_ptr<AVLNode>& node) const
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
void AVLTree<T>::postOrderRecursive(const std::unique_ptr<AVLNode>& node) const
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
void AVLTree<T>::levelOrder() const
{
    logger(DEBUG) << "[call_func]|" << "levelOrder()";
    if (!_root)
    {
        return;
    }
    Queue<AVLNode*> q; //使用了unique_ptr，此处采用原始指针临时访问
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
}
#endif /*_AVL_TREE_HPP_*/