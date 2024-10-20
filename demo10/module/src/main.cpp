#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
using namespace std;
/*
+-------------------------------+
|           Singleton            |
+-------------------------------+
| - m_singleton: _Singleton       |
| - m_mutex: std::mutex          |
+-------------------------------+
| + getInstance(): _Singleton     |
| + print(): void                |
| - Singleton()                  |
| - ~Singleton()                 |
+-------------------------------+
*/

//定义一个单例模式的任务队列
//饿汉模式 -> 定义类的时候创建单例对象, 多线程可以同时安全访问
#if 0
class Singleton
{
public:
    // Singleton() = delete;
    Singleton(const Singleton& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;
    static Singleton* getInstance()
    {
        return m_singleton;
    }
    void print()
    {
        cout << "m_singleton addr:" << m_singleton << endl;
        cout << "我是单例对象的一个成员函数" << endl;
    }
private:
    Singleton() = default;
    // Singleton(const Singleton& obj) = default;
    // Singleton& operator=(const Singleton& obj) = default;
    // 只能通过类名访问静态属性或方法
    static Singleton* m_singleton;
};

Singleton* Singleton::m_singleton = new Singleton;
#endif


//懒汉模式 -> 需要使用的时候才创建单例对象的实例，多线程可以同时安全访问需要加互斥锁
//使用 双重检查锁定 + 原子变量 解决线程安全问题
#if 0
class Singleton
{
public:
    // Singleton() = delete;
    Singleton(const Singleton& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;
    static Singleton* getInstance() 
    {   
        //双重检查锁定
        Singleton* singleton = m_singleton.load();
        if(singleton == nullptr)
        {
            lock_guard<mutex> locker(m_mutex);
            singleton = m_singleton.load();
            if(singleton == nullptr)
            {
                singleton = new Singleton;  //实际分三步，顺序可能重排。使用原子变量     
                m_singleton.store(singleton);
            }
        }
        return singleton;
    }
    void print()
    {
        cout << "m_singleton addr : " << m_singleton << endl;
        cout << "我是单例对象的一个成员函数" << endl;
    }
private:
    Singleton() = default;
    // Singleton(const Singleton& obj) = default;
    // Singleton& operator=(const Singleton& obj) = default;
    // 只能通过类名访问静态属性或方法
    //static Singleton* m_singleton;
    static mutex m_mutex;
    static atomic<Singleton*> m_singleton;
};
// Singleton* Singleton::m_singleton = nullptr;
mutex Singleton::m_mutex;
atomic<Singleton*> Singleton::m_singleton;
#endif

//懒汉模式 -> 需要使用的时候才创建单例对象的实例，多线程可以同时安全访问需要加互斥锁
//使用静态局部对象解决线程安全问题，要求编译器支持c++ 11
// 如果指令逻辑进入一个未被初始化的声明变量，所有并发执行应当等待该变量完成初始化。
#if 0
class Singleton
{
public:
    // Singleton() = delete;
    Singleton(const Singleton& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;
    static Singleton* getInstance() 
    {   
        static Singleton singleton;
        return &singleton;
    }
    void print()
    {
 
        cout << "我是单例对象的一个成员函数" << endl;
    }
private:
    Singleton() = default;
    // Singleton(const Singleton& obj) = default;
    // Singleton& operator=(const Singleton& obj) = default;
};
#endif

//实现任务队列
#if 1
class TaskQueue
{
public:
    // Singleton() = delete;
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        return m_taskQ;
    }

    //判断任务队列是否为空
    bool isEmpty()
    {
        lock_guard<mutex> locker(m_mutex);
        bool flag = m_data.empty();
        return flag;
    }
    //添加任务
    void addTask(int node)
    {
        lock_guard<mutex> locker(m_mutex);
        m_data.push(node);
    }
    //删除任务
    bool popTask()
    { 
        lock_guard<mutex> locker(m_mutex);
        if(m_data.empty())
            return false;
        m_data.pop();
        return true;
    }
    //取一个任务，不删除
    int takeTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if(m_data.empty())
            return -1; 
        return m_data.front();
    }
private:
    TaskQueue() = default;
    static TaskQueue* m_taskQ;
    //定义任务队列
    queue<int> m_data;
    mutex m_mutex;
};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

int main(int argc, char * argv[])
{

    TaskQueue* taskInstance = TaskQueue::getInstance();
    //生产者
    thread t1([&taskInstance](){
        for(int i = 0; i < 10 ; ++i)
        {
            taskInstance->addTask(i + 100);
            cout << "push data:" << i + 100 << ", threadId:" << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::microseconds(500));
        }
    });
    //消费者
    thread t2([&taskInstance](){
        this_thread::sleep_for(chrono::microseconds(100));
       while(!taskInstance->isEmpty())
        {
            int num = taskInstance->takeTask();
            cout << "take data:" << num << ", threadId:" << this_thread::get_id() << endl;
            taskInstance->popTask();
            this_thread::sleep_for(chrono::microseconds(1000));
        }
    });

    t1.join();
    t2.join();
    return 0;
}