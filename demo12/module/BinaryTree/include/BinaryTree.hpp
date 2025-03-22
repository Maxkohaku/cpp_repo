#pragma once
#include "Common.hpp"
#include <queue>
#include <memory>

template <typename T>
class BinaryTree
{
private:
    struct TreeNode
    {
        T value;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode(const T& val):value(val), left(nullptr), right(nullptr) {}
    };
    std::shared_ptr<TreeNode> root;

    void preOrderTraversalHelper(const std::shared_ptr<TreeNode>& node) const
    {
        if(!node)
        {
            return;
        }
        LOG_INFO("value:", node->value);
        preOrderTraversalHelper(node->left);
        preOrderTraversalHelper(node->right);
    }

    void inOrderTraversalHelper(const std::shared_ptr<TreeNode>& node) const
    {
        if(!node)
        {
            return;
        }
        inOrderTraversalHelper(node->left);
        LOG_INFO("value:", node->value);
        inOrderTraversalHelper(node->right);
    }

    void postOrderTraversalHelper(const std::shared_ptr<TreeNode>& node) const
    {
        if(!node)
        {
            return;
        }
        postOrderTraversalHelper(node->left);
        postOrderTraversalHelper(node->right);
        LOG_INFO("value:", node->value);
    }

public:
    BinaryTree():root(nullptr) {}
    void insert(const T& value)
    {
        LOG_DEBUG("调用函数 BinaryTree::insert");
        auto newNode = std::make_shared<TreeNode>(value);
        if(!root)
        {
            root = newNode;
            return;
        }
        auto current = root;
        while (true)
        {
            if(value < current->value)
            {
                if(!current->left)
                {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            }
            else
            {
                if(!current->right)
                {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
        }
    }

    bool search(const T& value) const
    {
        LOG_DEBUG("调用函数 BinaryTree::search");
        auto current = root;
        while(current) 
        {
            if(value < current->value)
            {
                current = current->left;
            }
            else if (value > current->value)
            {
                current = current->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    void preOrderTraversal() const
    {
        LOG_DEBUG("调用函数 BinaryTree::preOrderTraversal");
        preOrderTraversalHelper(root);
    }

    void inOrderTraversal() const
    {
        LOG_DEBUG("调用函数 BinaryTree::inOrderTraversal");
        inOrderTraversalHelper(root);
    }

    void postOrderTraversal() const
    {
        LOG_DEBUG("调用函数 BinaryTree::postOrderTraversal");
        postOrderTraversalHelper(root);
    }

    void levelOrderTraveral() const
    {
        LOG_DEBUG("调用函数 BinaryTree::levelOrderTraveral");
        if(!root)
        {
            LOG_INFO("root 为 nullptr");
        }
        std::queue<std::shared_ptr<TreeNode>> q;
        q.push(root);
        while (!q.empty())
        {
            auto current = q.front();
            q.pop();
            LOG_INFO("value:", current->value);
            if(current->left)
            {
                q.push(current->left);
            }
            if(current->right)
            {
                q.push(current->right);
            }
        }
    }
};