#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
using namespace std;
class Person
{
private:
    std::string _name;
    size_t _age;
    std::weak_ptr<Person> _bestFriend;
public:
    Person(std::string name, size_t age): _name(name), _age(age) 
    {
        cout << "Person Created" << endl;
    }
    ~Person()
    {
        cout << "Person Destroyed" << endl;
    }
    void show() const
    {
        cout << "name:" << _name << "|age:" << _age << endl;
    }
    void getBestFriend(const std::weak_ptr<Person>& person)
    {
        _bestFriend = person;
    }
    void showBestFriend() const
    {
        if (auto person = _bestFriend.lock())
        {
            cout << _name << "'s best friend is " << person->_name << endl;
            
        }
        else
        {
            cout << _name << "'s best friend is no longer exists" << endl;
        }
    }
};

class Friend
{
private:
    std::string _name;
    size_t _age;
    std::shared_ptr<Friend> _bestFriend;
public:
    Friend(std::string name, size_t age): _name(name), _age(age) 
    {
        cout << "Friend Created" << endl;
    }
    ~Friend()
    {
        cout << "Friend Destroyed" << endl;
    }
    void show() const
    {
        cout << "name:" << _name << "|age:" << _age << endl;
    }

    void getBestFriend(const std::shared_ptr<Friend>& person)
    {
        _bestFriend = person;
    }
    void showBestFriend() const
    {
        if (_bestFriend)
        {
            cout << _name << "'s best friend is " << _bestFriend->_name << endl;
        }
        else 
        {
            cout << _name << "'s best friend is no longer exists" << endl;
        }
    }
};

void funcCallA()
{
    //unique_ptr
    auto personUniquePtr1 = std::make_unique<Person>("ynh", 28);
    personUniquePtr1->show();

    // personUniquePtr1->show(); //personUniquePtr1转移资源后为空指针, 访问会coredump
    auto personUniquePtr2 = std::move(personUniquePtr1);
}

void funcCallB()
{
    //share_ptr
    auto personSharedPtr1 = std::make_shared<Person>("ynh", 28);
    personSharedPtr1->show();
    auto personSharedPtr2 = personSharedPtr1;
    cout << "shared count: " << personSharedPtr1.use_count();
    personSharedPtr1->show();
    personSharedPtr2->show();
}

void funcCallC()
{
    //shared_ptr循环引用
    auto ynh = std::make_shared<Friend>("ynh", 28);
    auto bmg = std::make_shared<Friend>("bmg", 18);
    ynh->getBestFriend(bmg); //ref(bmg) + 1 = 2
    bmg->getBestFriend(ynh); //ref(ynh) + 1 = 2
    ynh->showBestFriend();
    bmg->showBestFriend();
    cout << "count: " << ynh.use_count();

    //手动释放
    ynh.reset(); //ref(ynh) -1 = 1 > 0 不析构
    bmg.reset(); //ref(bmg) -1 = 1 > 0 不析构
}

void funcCallD()
{
    //weak_ptr
    auto ynh = std::make_shared<Person>("ynh", 28);
    auto bmg = std::make_shared<Person>("bmg", 18);
    ynh->getBestFriend(bmg); //不增加引用计数，ref(bmg) = 1
    bmg->getBestFriend(ynh); //不增加引用计数，ref(ynh) = 1
    ynh->showBestFriend();
    bmg->showBestFriend();
    cout << "count: " << ynh.use_count(); 

    //演示释放
    ynh.reset(); // ref(ynh) -1 = 0
    cout << "count: " << ynh.use_count(); 
    // ynh->showBestFriend();//对象均已释放，非法访问
}

int main(int argc, char *argv[])
{
    // funcCallA();
    // funcCallB();
    // funcCallC();
    funcCallD();
    return 0;
}