#pragma once
#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
using namespace std;
class ObserverAbstract {
public:
    ObserverAbstract(string observerName) : _observerName(observerName) {}
    virtual ~ObserverAbstract() = default;
    const string& getobserverName() const {
        return _observerName;
    }
    void setobserverName(const string& observerName) {
        _observerName = observerName;
    }
    virtual void update(const string& message) = 0;
private:
    string _observerName;
};
class Topic {
public:
    Topic(const string& topicName) : _topicName(topicName) {}
    ~Topic() = default;
    void attach(const shared_ptr<ObserverAbstract>& observer) {
        lock_guard<mutex> locker(_mutex);
        auto it = find(_observers.begin(), _observers.end(), observer);
        if (it == _observers.end())
        {
            _observers.push_back(observer);
            cout << observer->getobserverName() << " Subscribe: " << _topicName << endl;
        }
    }
    void detach(const shared_ptr<ObserverAbstract>& observer) {
        lock_guard<mutex> locker(_mutex);
        auto it = find(_observers.begin(), _observers.end(), observer);
        if (it != _observers.end())
        {
            _observers.erase(it);
            cout << observer->getobserverName() << " Unsubscribe: " << _topicName << endl;
        }
    }
    void notify(const string& message, const shared_ptr<ObserverAbstract>& observer) {
        lock_guard<mutex> locker(_mutex);
        for (const auto& _obs : _observers)
        {
            if (_obs != observer)
                _obs->update(message);
        }
    }
    void publish(const string& message, const shared_ptr<ObserverAbstract>& observer) {
        cout << observer->getobserverName() << " Send --->|" << message << endl;
        notify(message, observer);
    }
private:
    string _topicName;
    vector<shared_ptr<ObserverAbstract>> _observers;
    mutex _mutex;
};

class Observer : public ObserverAbstract, public enable_shared_from_this<Observer> {
public:
    Observer(const string& observerName) : ObserverAbstract(observerName) {}
    ~Observer() = default;
    void update(const string& message) override {
        cout << this->getobserverName() << " received <---|" << message << endl;
    }
    void subscribe(Topic& topic) {
        topic.attach(shared_from_this());
    }
    void Unsubscribe(Topic& topic) {
        topic.detach(shared_from_this());
    }
    void publish(Topic& topic, const string& message) {
        topic.publish(message, shared_from_this());
    }
};
void observer()
{
    Topic catAndMouse("Tom And Jerry");
    auto Tom = make_shared<Observer>("Tom"); 
    auto Jerry = make_shared<Observer>("Jerry"); 
    auto Spike = make_shared<Observer>("Spike"); 

    Tom->subscribe(catAndMouse);
    Jerry->subscribe(catAndMouse);
    Spike->subscribe(catAndMouse);

    Tom->publish(catAndMouse, "hey, what a nice day it is today !");
    Jerry->publish(catAndMouse, "let's go fishing !");
    Spike->publish(catAndMouse, "I am not free today, enjoy youself !");
    Spike->Unsubscribe(catAndMouse);
    Tom->publish(catAndMouse, "Okey !");
}
#endif /*_OBSERVER_HPP_*/