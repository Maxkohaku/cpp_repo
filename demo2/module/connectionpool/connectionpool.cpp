#include "connectionpool.h"
#include "jsoncpp/json/json.h"
#include "fstream"
#include <thread>
#include <chrono>

ConnectionPool* ConnectionPool::getConnectionPool()
{
    static ConnectionPool pool;
    return &pool;
}

bool ConnectionPool::parseJsonFile()
{
    std::ifstream ifs("dbcfg.json");
    Json::Reader rd;
    Json::Value root;
    rd.parse(ifs, root);
    if(root.isObject())
    {
        m_ip = root["ip"].asString();
        m_user = root["user"].asString();;
        m_passwd = root["passwd"].asString();;
        m_dbBase = root["dbBase"].asString();;
        m_port = root["port"].asUInt();
        m_minSize = root["minSize"].asInt();
        m_maxSize = root["maxSize"].asInt();
        m_timeout = root["timeout"].asInt();
        m_maxIdleTime = root["maxIdleTime"].asInt();
        return true;
    }
    return false;
}

ConnectionPool::~ConnectionPool()
{
    while(!m_connectionQ.empty())
    {
        Ynhsql* conn = m_connectionQ.front();
        m_connectionQ.pop();
        delete conn;
    }
}

void ConnectionPool::addConnection()
{
    Ynhsql* conn = new Ynhsql;
    conn->connect(m_user, m_passwd, m_dbBase, m_ip, m_port); 
    conn->refreshAliveTime();
    m_connectionQ.push(conn);
}

ConnectionPool::ConnectionPool()
{
    //加载json配置文件，初始化成员
    if(!parseJsonFile())
    {
        return;
    }

    for(int i = 0; i < m_minSize; ++i)
    {
        addConnection();
    }
    std::thread producer(&ConnectionPool::produceConnection, this);
    std::thread recycler(&ConnectionPool::recycleConnection, this);
    producer.detach();
    recycler.detach();
}

void ConnectionPool::produceConnection()
{
    while(true)
    {   
        std::unique_lock<std::mutex> locker(m_mutexQ);
        while(m_connectionQ.size() >= m_minSize)
        {
            m_cond.wait(locker);
        }
        addConnection();
        m_cond.notify_all();
    }
    
}

void ConnectionPool::recycleConnection()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> locker(m_mutexQ);
        while(m_connectionQ.size() > m_minSize)
        {
            Ynhsql* conn = m_connectionQ.front();
            if( conn->getAliveTime() >= m_maxSize)
            {
                m_connectionQ.pop();
                delete conn;
            }
            else
            {
                break;
            }
        }  
    }  
}

std::shared_ptr<Ynhsql> ConnectionPool::getConnection()
{
    std::unique_lock<std::mutex> locker(m_mutexQ);
    while(m_connectionQ.empty())
    {
        if(std::cv_status::timeout == m_cond.wait_for(locker, std::chrono::milliseconds(m_timeout)))
        {
            if(m_connectionQ.empty())
            {
                //return nullptr;
                continue;
            }
        }
    }
    std::shared_ptr<Ynhsql> connptr(m_connectionQ.front(), [this](Ynhsql* conn) {
        std::lock_guard<std::mutex> locker(m_mutexQ);
        conn->refreshAliveTime();
        m_connectionQ.push(conn);
    });
    m_connectionQ.pop();
    m_cond.notify_all();
    return connptr;
}