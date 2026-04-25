#pragma once
#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_
#include <iostream>
#include <memory>
#include <algorithm>
#include <optional>
#include "yLog.h"
#include <vector>
#include <queue>
namespace Structures {
template <typename T>
class Graph
{
private:
    struct Node
    {
    private:
        int _id;
        T _value;
        std::vector<int> _neighbors;
    public:
        Node(int id, const T& value) : _id(id), _value(value) {}

        int getId() const 
        { 
            return _id; 
        }

        const T& getValue() const 
        { 
            return _value; 
        }

        T& getValue() 
        { 
            return _value; 
        }

        const std::vector<int>& getNeighbors() const 
        { 
            return _neighbors; 
        }
        
        void setValue(const T& value) 
        { 
            _value = value;
        }

        void addNeighbor(int neighborId)
        {
            if (! hasNeighbor(neighborId) && neighborId != _id)
            {
                _neighbors.push_back(neighborId);
            }
        }

        void removeNeighbor(int neighborId)
        {
            auto it = std::find(_neighbors.begin(), _neighbors.end(), neighborId);
            if (it != _neighbors.end())
            {
                _neighbors.erase(it);
            }
        }

        bool hasNeighbor(int neighborId) const
        {
            return std::find(_neighbors.begin(), _neighbors.end(), neighborId) != _neighbors.end();
        }

        int getDegree() const
        {
            return static_cast<int>(_neighbors.size());
        }
    
        void show() const
        {
            std::cout << _id << "(" << _value << ") -> ";
            for (auto nid : _neighbors)
            {
                std::cout << nid << " ";
            }
            if (_neighbors.empty())
            {
                std::cout << "no neighbor";
            }
            std::cout << std::endl;
        }
    };

    std::vector<std::unique_ptr<Node>> _nodes;
    int _nextId = 0;
    
    std::optional<const Node&> _findNode(int id) const
    {
        for (const auto& node : _nodes)
        {
            if (node->getId() == id)
            {
                return *node;
            }
        }
        return std::nullopt;
    }

    std::optional<Node&> _findNode(int id)
    {
        for (auto& node : _nodes)
        {
            if (node->getId() == id)
            {
                return *node;
            }
        }
        return std::nullopt;
    }
    
    int generateId()
    {
        return _nextId++;
    }
    
public:
    Graph() = default;
    ~Graph() = default;
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;
    Graph(Graph&& other) noexcept = default;
    Graph& operator=(Graph&& other) = default;

    bool empty() const
    {
        return _nodes.empty();
    }

    int size() const
    {
        return static_cast<int>(_nodes.size());
    }

    void clear()
    {
        _nodes.clear();
        _nextId = 0;
    }

    int addNode(const T& value)
    {
        int id = generateId();
        _nodes.push_back(std::make_unique<Node>(id, value));
        return id;
    }

    bool removeNode(int id)
    {
        auto it = std::find_if(_nodes.begin(), _nodes.end(), 
                              [id](auto& node){ return node->getId() == id; });
        if (it == _nodes.end())
        {
            return false;
        }

        for (auto& node : _nodes)
        {
            if (node->getId() != id)
            {
                node->removeNeighbor(id);
            }
        }

        _nodes.erase(it);
        return true;
    }

    bool setValue(int id, const T& value)
    {
        auto node = _findNode(id);
        if (!node)
        {
            return false;
        }
        node->setValue(value); 
        return true;
    }

    std::optional<const T&> getValue(int id) const
    {
        auto node = _findNode(id);
        if (!node)
        {
            return std::nullopt;
        }
        return node->getValue(); 
    }

    bool addEdge(int fromId, int toId)
    {
        auto fromNode = _findNode(fromId);
        auto toNode = _findNode(toId);
        if (!fromNode || !toNode)
        {
            return false;
        }
        fromNode->addNeighbor(toId);
        return true;
    }

    bool removeEdge(int fromId, int toId)
    {
        auto fromNode = _findNode(fromId);
        if (!fromNode)
        {
            return false;
        }
        fromNode->removeNeighbor(toId);
        return true;
    }

    bool addUndirectedEdge(int a, int b)
    {
        return addEdge(a, b) && addEdge(b, a);
    }

    bool removeUndirectedEdge(int a, int b)
    {
        return removeEdge(a, b) && removeEdge(b, a);
    }

    bool hasEdge(int fromId, int toId) const
    {
        auto fromNode = _findNode(fromId);
        return fromNode ? fromNode->hasNeighbor(toId) : false;
    }

    int getDegree(int id) const
    {
        auto node = _findNode(id);
        return node ? node->getDegree() : -1;
    }

    std::optional<const std::vector<int>&> getNeighbors(int id) const
    {
        auto node = _findNode(id);
        if (node)
        {
            return node->getNeighbors();  
        }
        return std::nullopt;
    }

    bool contains(int id) const
    {
        return _findNode(id).has_value();  
    }

    void show() const
    {
        std::cout << "\n=== Graph (" << size() << " nodes) ===" << std::endl;
        for (const auto& node : _nodes) 
        {
            node->show();
        }
        if (empty()) 
        {
            std::cout << "(empty graph)" << std::endl;
        }
    }

    std::vector<int> bfs(int startId) const
    {
        std::vector<int> result;
        if (!contains(startId))
        {
            logger(WARNING) << "BFS失败：起始节点不存在 ID=" << startId;
            return result;
        }

        
    }
};
}
#endif /*_GRAPH_HPP_*/