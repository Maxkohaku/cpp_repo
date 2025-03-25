#pragma once
#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <memory>
class ObserverAbstract;
class ObserverAbstract
{
public:
    ObserverAbstract(const std::string name) : _name(name) {}
    virtual ~ObserverAbstract() = default;
    virtual void update(const std::string& message) = 0;
    const std::string& name() const
    {
        return _name;
    }
protected:
    std::string _name;
};
class Topic
{
public:
    Topic(const std::string topicName) : _topicName(topicName) {}
    ~Topic() = default;
    void attach(const std::shared_ptr<ObserverAbstract>& observer)
    {
        std::lock_guard<std::mutex> locker(_mutex);
        auto it = std::find(_observers.begin(), _observers.end(), observer);
        if (it == _observers.end())
        {
            _observers.push_back(observer);
            std::cout << observer->name() << "|subscribe:" << _topicName << std::endl;
        } 
    }
    void detach(const std::shared_ptr<ObserverAbstract>& observer)
    {
        std::lock_guard<std::mutex> locker(_mutex);
        auto it = std::find(_observers.begin(), _observers.end(), observer);
        if (it != _observers.end())
        {
            _observers.erase(it);
            std::cout << observer->name() << "|unsubscribe:" << _topicName << std::endl;
        }
    }
    void notify(const std::string& message, const std::shared_ptr<ObserverAbstract>& observer)
    {   
        std::lock_guard<std::mutex> locker(_mutex);
        for (auto _obs : _observers)
        {
            if (_obs->name() != observer->name())
            {
                _obs->update(message);
            }
        }
    }
    void publish(const std::string& message, const std::shared_ptr<ObserverAbstract>& observer)
    {
        std::cout << observer->name() << "|send:" << message << std::endl;
        notify(message, observer);
    }
private:
    std::string _topicName;
    std::vector<std::shared_ptr<ObserverAbstract>> _observers;
    std::mutex _mutex;

};
class Observer : public ObserverAbstract, public std::enable_shared_from_this<Observer>
{
public:
    Observer(const std::string name) : ObserverAbstract(name) {}
    ~Observer() = default;
    void update(const std::string& message) override
    {
        std::cout << this->name() << "|recieved:" << message << std::endl;
    }
    void subscribe(Topic& topic)
    {
        topic.attach(shared_from_this());
    }
    void unsubscribe(Topic& topic)
    {
        topic.detach(shared_from_this());
    }
    void publish(Topic& topic, const std::string& message)
    {
        topic.publish(message, shared_from_this());
    }
};

void observer()
{
    Topic topic("TomAndJerry");
    auto Tom = std::make_shared<Observer>("Tom");
    auto Jerry = std::make_shared<Observer>("Jerry");
    auto Spike = std::make_shared<Observer>("Spike");
    Tom->subscribe(topic);
    Jerry->subscribe(topic);
    Spike->subscribe(topic);
    Tom->publish(topic, "what a nice day is today");
    Spike->unsubscribe(topic);
    Jerry->publish(topic, "let's go!");
}

#endif