#pragma once 
#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <mutex>
class SingletonEager
{
public:
    static SingletonEager& getInstance()
    {
        return _instance;
    }
    void show() const
    {
        std::cout << "call SingletonEager" << std::endl;
    }
private:
    SingletonEager() = default;
    ~SingletonEager() = default;
    SingletonEager(const SingletonEager&) = delete;
    SingletonEager& operator=(const SingletonEager&) = delete;
    SingletonEager(SingletonEager&&) = delete;
    SingletonEager& operator=(SingletonEager&&) = delete;
    static SingletonEager _instance;
};
SingletonEager SingletonEager::_instance;

class SingletonLazy
{
public:
    static SingletonLazy* getInstance()
    {
        if (!_instance)
        {
            std::lock_guard<std::mutex> lock(_mutex);  // 锁住互斥锁
            if (!_instance)  // 防止其他线程已创建实例
            {
                _instance = new SingletonLazy();
            }
        }
        return _instance;
    }
    void show() const
    {
        std::cout << "call SingletonLazy" << std::endl;
    }
private:
    SingletonLazy() = default;
    ~SingletonLazy() = default;
    SingletonLazy(const SingletonLazy&) = delete;
    SingletonLazy operator=(const SingletonLazy&) = delete;
    SingletonLazy(SingletonLazy&&) = delete;
    SingletonLazy& operator=(SingletonLazy&&) = delete;
    static SingletonLazy* _instance;
    static std::mutex _mutex; 
};
SingletonLazy* SingletonLazy::_instance = nullptr;
std::mutex SingletonLazy::_mutex;

void singleton()
{
    auto& instanceEager = SingletonEager::getInstance();
    instanceEager.show();
    auto instanceLazy = SingletonLazy::getInstance();
    instanceLazy->show();
}
#endif // _SINGLETON_HPP_