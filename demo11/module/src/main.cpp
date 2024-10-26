#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

#if 0
//产品父类
class AbstractSmile
{
public:
    virtual void tansform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile()
    {
        cout << "析构 AbstractSmile" << endl;
    }
};

class GoatSmile:public AbstractSmile
{
public:
    void tansform() override
    {
        cout << "变身 -- 山羊人形态..." << endl;
    }
    void ability() override
    {
        cout << "能力 -- 冲撞..." << endl;
    }
    ~GoatSmile()
    {
        cout << "析构 GoatSmile" << endl;
    }
};

class LionSmile:public AbstractSmile
{
public:
    void tansform() override
    {
        cout << "变身 -- 狮子人形态..." << endl;
    }
    void ability() override
    {
        cout << "能力 -- 狮搏..." << endl;
    }
    ~LionSmile()
    {
        cout << "析构 LionSmile" << endl;
    }
};

class BatSmile:public AbstractSmile
{
public:
    void tansform() override
    {
        cout << "变身 -- 蝙蝠人形态..." << endl;
    }
    void ability() override
    {
        cout << "能力 -- 声波..." << endl;
    }
    ~BatSmile()
    {
        cout << "析构 BatSmile" << endl;
    }
};

//定义工厂类
enum class SmileType:char{Goat, Lion, Bat};
class SmileFactory
{
public:
    AbstractSmile* createSmile(SmileType SmileType)
    {
        AbstractSmile* ptr = nullptr;
        switch (SmileType)
        {
        case SmileType::Goat:
            ptr = new GoatSmile;
            break;
        case SmileType::Lion:
            ptr = new LionSmile;
            break;
        case SmileType::Bat:
            ptr = new BatSmile; 
            break;
        default:
            break;
        }
        return ptr;
    }
};

//定义抽象工厂类
class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~AbstractFactory()
    {
        cout << "析构 AbstractFactory" << endl;
    }
};

class GoatFactory:public AbstractFactory
{
public:
    AbstractSmile* createSmile()
    {
        return new GoatSmile;
    }
    ~GoatFactory()
    {
        cout << "析构 GoatFactory" <<endl;
    }
};

class LionFactory:public AbstractFactory
{
public:
    AbstractSmile* createSmile()
    {
        return new LionSmile;
    }
    ~LionFactory()
    {
        cout << "析构 LionFactory" <<endl;
    }
};

class BatFactory:public AbstractFactory
{
public:
    AbstractSmile* createSmile()
    {
        return new BatSmile;
    }
    ~BatFactory()
    {
        cout << "析构 BatFactory" <<endl;
    }
};

void simple_factory_test()
{
    SmileFactory* fac = new SmileFactory;
    auto s1 = fac->createSmile(SmileType::Goat);
    s1->tansform();
    s1->ability();

    auto s2 = fac->createSmile(SmileType::Lion);
    s2->tansform();
    s2->ability();

    auto s3 = fac->createSmile(SmileType::Bat);
    s3->tansform();
    s3->ability();

    delete s1;
    delete s2;
    delete s3;
    delete fac;
}

void factory_test()
{
    AbstractFactory* fac = nullptr;
    fac = new GoatFactory;
    auto s1 = fac->createSmile();
    s1->tansform();
    s1->ability();

    fac = new LionFactory;
    auto s2 = fac->createSmile();
    s2->tansform();
    s2->ability();

    fac = new BatFactory;
    auto s3 = fac->createSmile();
    s3->tansform();
    s3->ability();

    delete s1;
    delete s2;
    delete s3;
    delete fac;
}
#endif

//船体
class ShipBody
{
public:
    virtual string getBody() = 0;
    virtual ~ShipBody() {}
};

class WoodBody:public ShipBody
{
public:
    string getBody() override
    {
        return string("木制船体");
    }
};

class IronBody:public ShipBody
{
public:
    string getBody() override
    {
        return string("钢制船体");
    }
};

class MetalBody:public ShipBody
{
public:
    string getBody() override
    {
        return string("合金船体");
    }
};

//引擎
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine() {}
};

class Manual:public Engine
{
public:
    string getEngine() override
    {
        return string("人工动力");
    }
};

class Diesel:public Engine
{
public:
    string getEngine() override
    {
        return string("内燃机动力");
    }
};


class Neclear:public Engine
{
public:
    string getEngine() override
    {
        return string("核动力");
    }
};
//武器
class Weapon
{
public:
    virtual string getWeapon() = 0;
    virtual ~Weapon() {}
};

class Gun:public Weapon
{
    string getWeapon()
    {
        return string("枪");
    }
};

class Cannon:public Weapon
{
    string getWeapon()
    {
        return string("炮");
    }
};

class Laser:public Weapon
{
    string getWeapon()
    {
        return string("激光");
    }
};

//船
class Ship
{
public:
    Ship(ShipBody* shipBody, Engine* engine, Weapon* weapon):m_shipBody(shipBody), m_engine(engine), m_weapon(weapon){}
    ~Ship()
    {
        delete m_shipBody;
        delete m_engine;
        delete m_weapon;
    }
    string getProperty()
    {
        string info = m_shipBody->getBody() + m_engine->getEngine() + m_weapon->getWeapon();
        cout << "船的属性:" << info << endl;
        return info;
    }
private:
    ShipBody* m_shipBody;
    Engine* m_engine;
    Weapon* m_weapon; 
};

//工厂类
class AbstractFactory
{
public:
    virtual Ship* creatShip() = 0;
    virtual ~AbstractFactory() {}
};

class BasicFactory:public AbstractFactory
{
public:
    Ship* creatShip() override
    {   
        Ship* ship = new Ship(new WoodBody, new Manual, new Gun); 
        cout << "基础型船已创建" << endl;
        return ship;
    }
};

class StandardFactory:public AbstractFactory
{
public:
    Ship* creatShip() override
    {   
        Ship* ship = new Ship(new IronBody, new Diesel, new Cannon); 
        cout << "标准型船已创建" << endl;
        return ship;
    }
};

class UltimateFactory:public AbstractFactory
{
public:
    Ship* creatShip() override
    {   
        Ship* ship = new Ship(new MetalBody, new Neclear, new Laser); 
        cout << "旗舰型船已创建" << endl;
        return ship;
    }
};


void abstract_test()
{
    AbstractFactory* fac = nullptr;
    fac = new BasicFactory;
    auto s1 = fac->creatShip();
    s1->getProperty();

    fac = new StandardFactory;
    auto s2 = fac->creatShip();
    s2->getProperty();

    fac = new UltimateFactory;
    auto s3 = fac->creatShip();
    s3->getProperty();

    delete s1;
    delete s2;
    delete s3;
    delete fac;

}

int main(int argc, char * argv[])
{
    //simple_factory_test();
    //factory_test();
    abstract_test();
    return 0;
}