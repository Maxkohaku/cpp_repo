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
    void attach(ObserverAbstract* observer)
    {
        std::lock_guard<std::mutex> locker(_mutex);
        auto it = std::find(_observers.begin(), _observers.end(), observer);
        if (it == _observers.end())
        {
            _observers.push_back(observer);
        } 
    }
    void detach(ObserverAbstract* observer)
    {
        std::lock_guard<std::mutex> locker(_mutex);
        auto it = std::find(_observers.begin(), _observers.end(), observer);
        if (it != _observers.end())
        {
            _observers.erase(it);
        }
    }
    void notify(const std::string& message, ObserverAbstract* observer)
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
    void publish(const std::string& message, ObserverAbstract* observer)
    {
        std::cout << observer->name() << "|send:" << message << std::endl;
        notify(message, observer);
    }
private:
    std::string _topicName;
    std::vector<ObserverAbstract*> _observers;
    std::mutex _mutex;

};
class Observer : public ObserverAbstract
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
        topic.attach(this);
    }
    void unsubscribe(Topic& topic)
    {
        topic.detach(this);
    }
    void publish(Topic& topic, const std::string& message)
    {
        topic.publish(message, this);
    }
};

void observer()
{
    Topic topic("TomeAndJerry");
    Observer Tom("Tom");
    Observer Jerry("Jerry");
    Observer Spike("Spike");
    Tom.subscribe(topic);
    Jerry.subscribe(topic);
    Spike.subscribe(topic);
    Tom.publish(topic, "what a nice day is today");
    Spike.unsubscribe(topic);
    Jerry.publish(topic, "let's go!");
}

#endif