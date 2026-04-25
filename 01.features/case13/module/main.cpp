#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
using str = std::string;

enum class Sex
{
    MAN,
    WOMAN,
    UNKNOWN
};

class Person
{
protected:
    str _name;
    Sex _sex;
    size_t _age;
public:
    Person() = delete;
    Person(const str name, const Sex sex, const size_t age): _name(name), _sex(sex), _age(age) {}
    virtual ~Person() = default;
    virtual void showPhone() const = 0 ;
    
};

class Chinese final: public Person
{
private:
    str _province;
public:
    Chinese() = delete;
    Chinese(const str name, const Sex sex, const size_t age, const str province): Person(name, sex, age), _province(province) {}
    ~Chinese() = default;
    void showPhone()const override
    {
        cout << "Chinese use huawei phone" << endl;
    }
};

void funcCallA()
{
    Chinese yuchengdong("yuchengdong", Sex::MAN, 55, "Guangdong");
    yuchengdong.showPhone();
}

int main(int argc, char *argv[])
{
    funcCallA();
    return 0;
}