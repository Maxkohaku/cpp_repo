#include "Person.h"

Person::Person()
{
    cout << "call default constructor" << endl;
}

Person::Person(string name, string sex, int age)
{
    cout << "call param constructor" << endl;
    m_name = name;
    m_sex = sex;
    m_age = age;
}
Person::Person(const Person& obj)
{
    cout << "call copy constructor" << endl;
    m_name = obj.m_name;
    m_sex = obj.m_sex;
    m_age = obj.m_age; 
}
Person::Person(Person&& obj)
{
    cout << "call move constructor" << endl;
    m_name = move(obj.m_name);
    m_sex = move(obj.m_sex);
    m_age = obj.m_age; 
    obj.m_age = 0;
}
Person& Person::operator=(const Person& obj)
{
    cout << "call copy operator constructor" << endl;
    if(&obj != nullptr)
    {
        m_name = obj.m_name;
        m_sex = obj.m_sex;
        m_age = obj.m_age; 
    }
    return *this;

}
Person& Person::operator=(Person&& obj)
{
    cout << "call move operator constructor" << endl;
    if(&obj != nullptr)
    {
        m_name = move(obj.m_name);
        m_sex = move(obj.m_sex);
        m_age = obj.m_age; 
        obj.m_age = 0;
    }
    return *this;
}
Person::~Person()
{
    cout << "call destructor" << endl;
}
void Person::show()
{
    cout << "name:" << m_name << "|sex:" << m_sex << "|age:" << m_age << endl;
}