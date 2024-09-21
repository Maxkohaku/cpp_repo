#ifndef _PERSON_H_
#define _PERSON_H_
#include <iostream>
using namespace std;
class Person
{
public:
    Person();
    Person(string name, string sex, int age);
    Person(const Person& obj);
    Person(Person&& obj);
    Person& operator=(const Person& obj);
    Person& operator=(Person&& obj);
    ~Person();
    void show();
private:
    string m_name;
    string m_sex;
    int m_age;
};
#endif /*_PERSON_H_*/