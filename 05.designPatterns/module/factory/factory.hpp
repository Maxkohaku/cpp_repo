#pragma once
#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_
#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
using namespace std;
class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual void draw() = 0;
private:
    string _name = "none";
};
class Circle : public Shape {
public:
    void draw() override {
        cout << "draw a shape : " << _name <<endl;
    }
private:
    string _name = "Circle";
};
class Triangle : public Shape {
public:
    void draw() override {
        cout << "draw a shape : " << _name <<endl;
    }
private:
    string _name = "Triangle";
};
class Rectangle : public Shape {
public:
    void draw() override {
        cout << "draw a shape : " << _name <<endl;
    }
private:
    string _name = "Rectangle";
};
class ShapeFactory {
public:
    using FactoryMethod = function<unique_ptr<Shape>()>;
    static ShapeFactory& getInstance() {
        static ShapeFactory instance;
        return instance;
    }
    void registerFactory(const string& name , FactoryMethod method) {
        cout << "_factoryMap register : " << name << endl;
        _factoryMap[name] = method;
    }
    void unregisterFactory(const string& name) {
        auto it =_factoryMap.find(name);
        if (it != _factoryMap.end())
        {
            _factoryMap.erase(it);
            cout << "_factoryMap unregister : " << name << endl;
        }
    }
    unique_ptr<Shape> ceate(const std::string& name) {
        auto it =_factoryMap.find(name);
        if (it == _factoryMap.end())
            throw invalid_argument("factory no registered type: " + name);
        return it->second();
    }
private:
    ShapeFactory() = default;
    ~ShapeFactory() = default;
    ShapeFactory(const ShapeFactory&) = delete;
    ShapeFactory& operator=(const ShapeFactory&) = delete;
    ShapeFactory(ShapeFactory&&) = delete;
    ShapeFactory& operator=(ShapeFactory&&) = delete;
    unordered_map<string, FactoryMethod> _factoryMap;
};



void factory() {
    auto& instance = ShapeFactory::getInstance();
    instance.registerFactory("Circle", [](){return make_unique<Circle>();});
    instance.registerFactory("Triangle", [](){return make_unique<Triangle>();});
    instance.registerFactory("Rectangle", [](){return make_unique<Rectangle>();});
    instance.ceate("Circle")->draw();
    instance.ceate("Triangle")->draw();
    instance.ceate("Rectangle")->draw();
    instance.unregisterFactory("Circle");
    instance.ceate("Circle")->draw();
}
#endif /*_FACTORY_HPP_*/