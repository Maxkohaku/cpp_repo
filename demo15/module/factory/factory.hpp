#pragma once
#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <functional>
class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default; 
    virtual void draw() = 0;
};

class Circle : public Shape
{
public:
    Circle() = default;
    ~Circle() = default;
    void draw() override
    {
        std::cout << "draw shape: Circle" << std::endl;
    }
};
class Triangle : public Shape
{
public:
    void draw() override
    {
        std::cout << "draw shape: Triangle" << std::endl;
    }
};
class Rectangle : public Shape 
{
public:
    void draw() override 
    {
        std::cout << "draw shape: Rectangle" << std::endl;
    }
};
class ShapeFactory
{
public:
    using FactoryMethod = std::function<std::unique_ptr<Shape>()>;
    ShapeFactory() = default;
    ~ShapeFactory() = default;
    virtual std::unique_ptr<Shape> create() = 0;
};
class CircleFactory : public ShapeFactory
{
public:
    CircleFactory() = default;
    ~CircleFactory() = default;
    std::unique_ptr<Shape> create() override
    {
        return std::make_unique<Circle>();
    }
};
class TriangleFactory : public ShapeFactory
{
public:
    TriangleFactory() = default;
    ~TriangleFactory() = default;
    std::unique_ptr<Shape> create() override
    {
        return std::make_unique<Triangle>();
    }   
};
class RectangleFactory : public ShapeFactory
{
public:
    RectangleFactory() = default;
    ~RectangleFactory() = default;
    std::unique_ptr<Shape> create() override
    {
        return std::make_unique<Rectangle>();
    }   
};
class ShapeFactoryNew
{
public:
    using FactoryMethod = std::function<std::unique_ptr<Shape>()>;
    static ShapeFactoryNew& getInstance()
    {
        
        return _instance;
    }
    void registerFactory(const std::string& name, FactoryMethod method)
    {
        _factoryMap[name] = method;
    }
    std::unique_ptr<Shape> create(const std::string& name)
    {
        if(_factoryMap.find(name) != _factoryMap.end())
        {
            return _factoryMap[name]();
        }
        std::cerr << "not exsit name: " << name << std::endl;
        exit(-1);
        return nullptr;
    }
private:
    ShapeFactoryNew() = default;
    ~ShapeFactoryNew() = default;
    ShapeFactoryNew(const ShapeFactoryNew&) = delete;
    ShapeFactoryNew& operator=(const ShapeFactoryNew&) = delete;
    ShapeFactoryNew(ShapeFactoryNew&&) = delete;
    ShapeFactoryNew& operator=(ShapeFactoryNew&&) = delete;
    static ShapeFactoryNew _instance;
    std::unordered_map<std::string, FactoryMethod> _factoryMap;
};
ShapeFactoryNew ShapeFactoryNew::_instance;
void factory()
{
    std::unique_ptr<ShapeFactory> factory = std::make_unique<CircleFactory>();
    std::unique_ptr<Shape> shape = factory->create();
    shape->draw();

    factory = std::make_unique<TriangleFactory>();
    shape = factory->create();
    shape->draw();

    factory = std::make_unique<RectangleFactory>();
    shape = factory->create();
    shape->draw();
}
void registerFactories()
{
    ShapeFactoryNew::getInstance().registerFactory("Circle", [](){return std::make_unique<Circle>();});
    ShapeFactoryNew::getInstance().registerFactory("Triangle", [](){return std::make_unique<Triangle>();});
    ShapeFactoryNew::getInstance().registerFactory("Rectangle", [](){return std::make_unique<Rectangle>();});
}
void factoryNew()
{
    registerFactories();
    auto& factory = ShapeFactoryNew::getInstance();
    std::unique_ptr<Shape> shape;
    shape = factory.create("Circle");
    shape->draw();
    shape = factory.create("Triangle");
    shape->draw();
    shape = factory.create("Rectangle");
    shape->draw();
}
#endif // _FACTORY_HPP_