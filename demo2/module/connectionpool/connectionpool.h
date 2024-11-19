#ifndef _CONNETION_POOL_H_
#define _CONNETION_POOL_H_
#include <iostream>
#include <queue>
#include "ynhsql.h"
#include <mutex>
#include <condition_variable>
class ConnectionPool
{
public:
    static ConnectionPool* getConnectionPool();
    ConnectionPool(const ConnectionPool& obj) = delete;
    ConnectionPool& operator=(const ConnectionPool& obj) = delete;
    std::shared_ptr<Ynhsql> getConnection();
private:
    ConnectionPool();
    bool parseJsonFile();
    void produceConnection();
    void recycleConnection();
    void addConnection();

    std::string m_ip;
    std::string m_user;
    std::string m_passwd;
    std::string m_dbBase;
    unsigned int m_port;
    int m_minSize;
    int m_maxSize;
    int m_timeout;
    int m_maxIdleTime;
    std::mutex m_mutexQ;
    std::condition_variable m_cond;
    std::queue<Ynhsql*> m_connectionQ;
};

#endif /* _CONNETION_POOL_H_*/