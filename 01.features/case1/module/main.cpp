#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
class Person
{
private:
    string _name;
    string _sex;
    size_t _age;
public:
    Person();
    Person(string name, string sex, size_t age);
    Person(const Person& other);
    Person& operator=(const Person& other);
    Person(Person && other) noexcept;
    Person& operator=(Person && other) noexcept;
    Person* operator&() noexcept;
    const Person* operator&() const noexcept;
    void show(string person) const;
    ~Person();
};
Person::Person(): _name("null"), _sex("unknow"), _age(0)
{
    cout << "[call_func on Person]|default constructor function" << endl;
}

Person::Person(string name, string sex, size_t age) : _name(name), _sex(sex), _age(age)
{
    cout << "[call_func on Person]|parameters constructor function" << endl;
}

Person::Person(const Person& other) : _name(other._name), _sex(other._sex), _age(other._age)
{
    cout << "[call_func on Person]|copy constructor function" << endl;
}

Person& Person::operator=(const Person& other)
{
    cout << "[call_func on Person]|copy operator function" << endl;
    if (&other != this) 
    {
        _name = other._name;
        _sex = other._sex;
        _age = other._age;
    }
    return *this;
}

Person::Person(Person&& other) noexcept : _name(move(other._name)), _sex(move(other._sex)), _age(other._age)
{
    cout << "[call_func on Person]|move constructor function" << endl;
    other._age = 0;
}

Person& Person::operator=(Person&& other) noexcept
{
    cout << "[call_func on Person]|move operator function" << endl;
    if(&other != this)
    {
        _name = move(other._name);
        _sex = move(other._sex);
        _age = other._age;
        other._age = 0;
    }
    return *this;
}

Person::~Person()
{
    cout << "[call_func on Person]|destructor function" << endl;
}

Person* Person::operator&() noexcept
{
    cout << "[call_func on Person]|operator&()" << endl;
    return this;
}

const Person* Person::operator&() const noexcept
{
    cout << "[call_func on Person]|operator&() const" << endl;
    return this;
}

void Person::show(string person) const
{
    cout << "[call_func on Person]|show" << endl;
    cout << "person:" << person << "|name:" <<_name <<"|sex:" <<_sex << "|age:" << _age;
}

void testFunc()
{
    Person p1;
    Person p2("ynh", "man", 28); 
    p1 = p2;
    p1.show("p1");
    Person p3 = move(p1);
    p1.show("p1");
    p3.show("p3");
    Person p4;
    p4 = move(p2);
    p4.show("p4");
    p2.show("p2");

    cout << "p4 address:" << &p4;
    const Person p5("ynh", "man", 28);
    const Person* p6 = &p5;
    cout << "p6 address:" << &p6;
}

int main(int argc, char *argv[])
{
    testFunc();
    return 0;
}