#pragma once
#ifndef _DECORATOR_HPP_
#define _DECORATOR_HPP_
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class Coffee {
public:
    Coffee() = default;  
    virtual ~Coffee() = default;
    virtual string describe() const = 0;
    virtual double cost() const = 0;
private:
    string _name = "none";
    double _price = 0;
};
class Latte : public Coffee {
    string describe() const override {
        return _name;
    }
    double cost() const override {
        return _price;
    }
private:
    string _name = "Latte";
    double _price = 15;
};
class Espresso : public Coffee {
    string describe() const override {
        return _name;
    }
    double cost() const override {
        return _price;
    }
private:
    string _name = "Espresso";
    double _price = 20;
};
class CondimentDecorator : public Coffee {
public:
    explicit CondimentDecorator(unique_ptr<Coffee> coffee) : _coffee(move(coffee)) {}
    string describe() const override {
        return _coffee->describe();
    }
    double cost() const override {
        return _coffee->cost();
    }
protected:
    unique_ptr<Coffee> _coffee;
};
class Milk : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;
    string describe() const override {
        return CondimentDecorator::describe() + " + " + _name;
    }
    double cost() const override {
        return CondimentDecorator::cost() + _price;
    }
private:
    string _name = "Milk";
    double _price = 5;
};
class Sugar : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;
    string describe() const override {
        return CondimentDecorator::describe() + " + " + _name;
    }
    double cost() const override {
        return CondimentDecorator::cost() + _price;
    }
private:
    string _name = "Sugar";
    double _price = 2;
};
void decorator() {
    auto latteMilkSugar = make_unique<Sugar>(make_unique<Milk>(make_unique<Latte>()));
    cout << latteMilkSugar->describe() << " cost " << latteMilkSugar->cost() << endl;

    auto espressoMilkSugar = make_unique<Sugar>(make_unique<Milk>(make_unique<Espresso>()));
    cout << espressoMilkSugar->describe() << " cost " << espressoMilkSugar->cost() << endl;
}
#endif /*_DECORATOR_HPP_*/