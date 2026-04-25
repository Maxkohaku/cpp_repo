#pragma once
#ifndef _DECORATOR_HPP_
#define _DECORATOR_HPP_
#include <iostream>
#include <string>
#include <memory>
class Coffee
{
public:
    Coffee() = default;
    virtual ~Coffee() = default; 
    virtual const std::string description() const = 0;
    virtual const double cost() const = 0;
};
class Latte : public Coffee
{
public:
    Latte() = default;
    ~Latte() = default;
    const std::string description() const override
    {
        return "Latte";
    }
    const double cost() const override
    {
        return 20;
    }
};
class Espresso : public Coffee
{
public:
    Espresso() = default;
    ~Espresso() = default;
    const std::string description() const override
    {
        return "Espresso";
    }
    const double cost() const override
    {
        return 15;
    }
};
class CondimentDecorator : public Coffee
{
public:
    CondimentDecorator(std::unique_ptr<Coffee> coffee) : _coffee(std::move(coffee)) {}
    ~CondimentDecorator() = default;
    const std::string description() const override
    {
        return _coffee->description();
    }
    const double cost() const override
    {
        return _coffee->cost();
    }
protected:  
    std::unique_ptr<Coffee> _coffee;
};
class Milk : public CondimentDecorator
{   
public:
    Milk(std::unique_ptr<Coffee> coffee) : CondimentDecorator(std::move(coffee)) {}
    ~Milk() = default;
    const std::string description() const override
    {
        return _coffee->description() + " + Milk";
    }
    const double cost() const override
    {
        return _coffee->cost() + 5;
    }
};
class Sugar : public CondimentDecorator
{
public:
    Sugar(std::unique_ptr<Coffee> coffee) : CondimentDecorator(std::move(coffee)) {}
    ~Sugar() = default;
    const std::string description() const override
    {
        return _coffee->description() + " + Sugar";
    }
    const double cost() const override
    {
        return _coffee->cost() + 2;
    }
};
void decorator()
{
    auto coffeeWithMilkAndSugar = std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<Latte>()));
    std::cout << coffeeWithMilkAndSugar->description() << " : " << coffeeWithMilkAndSugar->cost() << std::endl;
}

#endif /*_DECORATOR_HPP_*/