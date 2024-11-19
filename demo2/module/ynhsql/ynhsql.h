#ifndef _YNH_SQL_H_
#define _YNH_SQL_H_
#include <iostream>
#include "mysql/mysql.h"
#include <chrono>

class Ynhsql
{

public:
    //初始化数据库连接
    Ynhsql();
    //释放数据库连接
    ~Ynhsql();
    //连接数据库
    bool connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned int port = 3306);
    //更新数据库: insert update delete
    bool update(std::string sql);
    //查询数据库
    bool query(std::string sql);
    //便利查询的结果集
    bool next();
    //得到结果集中的字段
    std::string value(int index);
    //事务操作
    bool transaction();
    //事务提交
    bool commit();
    //事务回滚
    bool rollback();
    //刷新起始空闲时间点
    void refreshAliveTime();
    //计算连接存活总时长
    long long getAliveTime();
private:
    void freeRes();
    MYSQL* m_conn = nullptr;
    MYSQL_RES* m_res = nullptr;
    MYSQL_ROW m_row =nullptr;
    std::chrono::steady_clock::time_point m_alivetime;
};

#endif /*_YNH_SQL_H_*/